#include "Network.h"
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/interprocess/detail/atomic.hpp>

void Hive::Stop()
{
    if (boost::interprocess::ipcdetail::atomic_cas32(&_shutdown, 1, 0) == 0)
    {
        delete _work;
        _ioService.run();
        _ioService.stop();
    }
}

void Hive::Reset()
{
    if (boost::interprocess::ipcdetail::atomic_cas32(&_shutdown, 0, 1) == 1)
    {
        _ioService.reset();
        _work = new boost::asio::io_service::work(_ioService);
    }
}

void Acceptor::StartTimer()
{
    _lastTime = boost::posix_time::microsec_clock::local_time();
    _timer.expires_from_now(boost::posix_time::milliseconds(_timerInterval));
    _timer.async_wait(_ioStrand.wrap(boost::bind(&Acceptor::HandleTimer, this, _1)));
}

void Acceptor::StartError(const boost::system::error_code& error)
{
    if (boost::interprocess::ipcdetail::atomic_cas32(&_errorState, 1, 0) == 0)
    {
        boost::system::error_code ec;
        _acceptor.cancel(ec);
        _acceptor.close(ec);
        _timer.cancel(ec);
        OnError(ec);
    }
}

void Acceptor::HandleTimer(const boost::system::error_code& error)
{
    if (error || HasError() || _hive->HasStopped())
        StartError(error);
    else
    {
        OnTimer(boost::posix_time::microsec_clock::local_time() - _lastTime);
        StartTimer();
    }
}

void Acceptor::HandleAccept(const boost::system::error_code& error, Connection* connection)
{
    if (error || HasError() || _hive->HasStopped())
        connection->StartError(error);
    else
    {
        if (connection->GetSocket().is_open())
        {
            connection->StartTimer();
            if (OnAccept(connection, connection->GetSocket().remote_endpoint().address().to_string(), connection->GetSocket().remote_endpoint().port()))
                connection->OnAccept(_acceptor.local_endpoint().address().to_string(), _acceptor.local_endpoint().port());
        }
        else
            StartError(error);
    }
}

void Acceptor::Listen(const std::string& host, const uint16& port)
{
    boost::asio::ip::tcp::resolver resolver(_hive->GetService());
    boost::asio::ip::tcp::resolver::query query(host, boost::lexical_cast<std::string>(port));
    boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
    _acceptor.open(endpoint.protocol());
    _acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(false));
    _acceptor.bind(endpoint);
    _acceptor.listen(boost::asio::socket_base::max_connections);
    StartTimer();
}

Acceptor::Acceptor(Hive* hive) : _hive(hive), _acceptor(hive->GetService()),
    _ioStrand(hive->GetService()), _timer(hive->GetService()), 
    _timerInterval(1000), _errorState(0)
{

}

void Connection::Bind(const std::string& ip, uint16 port)
{
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(ip), port);
    _socket.open(endpoint.protocol());
    _socket.set_option(boost::asio::ip::tcp::acceptor::reuse_address(false));
    _socket.bind(endpoint);
}

void Connection::StartSend()
{
    if (!_pendingSends.empty())
        boost::asio::async_write(_socket, boost::asio::buffer(_pendingSends.front()),
        _ioStrand.wrap(boost::bind(&Connection::HandleSend, this /*this*/,
        boost::asio::placeholders::error, _pendingSends.begin())));
}

void Connection::StartRecv(int totalBytes)
{
    if (totalBytes > 0)
    {
        _recvBuffer.resize(totalBytes);
        boost::asio::async_read(_socket, boost::asio::buffer(_recvBuffer),
            _ioStrand.wrap(boost::bind(&Connection::HandleRecv,
            this,  _1, _2)));
    }
    else
    {
        _recvBuffer.resize(_receiveBufferSize);
        _socket.async_read_some(boost::asio::buffer(_recvBuffer),
            _ioStrand.wrap(boost::bind(&Connection::HandleRecv,
            this, _1, _2)));
    }
}

void Connection::StartTimer()
{
    _lastTime = boost::posix_time::microsec_clock::local_time();
    _timer.expires_from_now(boost::posix_time::milliseconds(_timerInterval));
    _timer.async_wait(_ioStrand.wrap(boost::bind(&Connection::DispatchTimer, this /*this*/, _1)));

}

void Connection::StartError(const boost::system::error_code& error)
{
    if (boost::interprocess::ipcdetail::atomic_cas32(&_errorState, 1, 0) == 0)
    {
        boost::system::error_code ec;
        _socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
        _socket.close(ec);
        _timer.cancel(ec);
        OnError(error);
    }
}

void Connection::HandleConnect(const boost::system::error_code& error)
{
    if (error || HasError() || _hive->HasStopped())
        StartError(error);
    else
    {
        if (_socket.is_open())
            OnConnect(_socket.remote_endpoint().address().to_string(), _socket.remote_endpoint().port());
        else
            StartError(error);
    }
}

void Connection::HandleSend(const boost::system::error_code& error, std::list< std::vector<uint8> >::iterator itr)
{
    if (error || HasError() || _hive->HasStopped())
        StartError(error);
    else
    {
        OnSend(*itr);
        _pendingSends.erase(itr);
        StartSend();
    }

}

void Connection::HandleRecv(const boost::system::error_code& error, int32 actualBytes)
{
    if (error || HasError() || _hive->HasStopped())
        StartError(error);
    else
    {
        _recvBuffer.resize(actualBytes);
        OnRecv(_recvBuffer);
        _pendingRecvs.pop_front();
        if (!_pendingRecvs.empty())
            StartRecv(_pendingRecvs.front());
    }

}

void Connection::HandleTimer(const boost::system::error_code& error)
{
    if (error || HasError() || _hive->HasStopped())
        StartError(error);
    else
    {
        OnTimer(boost::posix_time::microsec_clock::local_time() - _lastTime);
        StartTimer();
    }

}

void Connection::DispatchSend(std::vector<uint8> buffer)
{
    bool shouldStartSend = _pendingSends.empty();
    _pendingSends.push_back(buffer);
    if (shouldStartSend)
        StartSend();
}

void Connection::DispatchRecv(int totalBytes)
{
    bool shouldStartReceive = _pendingRecvs.empty();
    _pendingRecvs.push_back(totalBytes);
    if (shouldStartReceive)
        StartRecv(totalBytes);
}

void Connection::Connect(const std::string& host, uint16 port)
{
    boost::system::error_code ec;
    boost::asio::ip::tcp::resolver resolver(_hive->GetService());
    boost::asio::ip::tcp::resolver::query query(host, boost::lexical_cast<std::string>(port));
    boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);
    _socket.async_connect(*iterator, _ioStrand.wrap(boost::bind(&Connection::HandleConnect, this /*this*/, _1)));
    StartTimer();
}

Connection::Connection(Hive* hive) : _hive(hive), _socket(hive->GetService()), _ioStrand(hive->GetService()), _timer(hive->GetService()),
    _receiveBufferSize(4096), _timerInterval(1000), _errorState(0)
{

}
