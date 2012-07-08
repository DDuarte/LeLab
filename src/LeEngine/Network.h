#ifndef NETWORK_H
#define NETWORK_H

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/interprocess/detail/atomic.hpp>
#include <boost/bind.hpp>
#include <string>
#include <vector>
#include <list>
#include "Defines.h"

class Hive;
class Acceptor;
class Connection;

class Connection
{
    friend class Acceptor;
    friend class Hive;

private:
    Hive* _hive;
    boost::asio::ip::tcp::socket _socket;
    boost::asio::strand _ioStrand;
    boost::asio::deadline_timer _timer;
    boost::posix_time::ptime _lastTime;
    std::vector<uint8> _recvBuffer;
    std::list<int> _pendingRecvs;
    std::list< std::vector<uint8> > _pendingSends;
    int _receiveBufferSize;
    int _timerInterval;
    volatile uint32 _errorState;

protected:
    Connection(Hive* hive);
    virtual ~Connection() {}

private:
    Connection(const Connection& other);
    Connection& operator =(const Connection& other);
    void StartSend();
    void StartRecv(int totalBytes);
    void StartTimer();
    void StartError(const boost::system::error_code& error);
    void DispatchSend(std::vector<uint8> buffer);
    void DispatchRecv(int totalBytes);
    void DispatchTimer(const boost::system::error_code& error) { _ioStrand.post(boost::bind(&Connection::HandleTimer, this, error)); }
    void HandleConnect(const boost::system::error_code& error);
    void HandleSend(const boost::system::error_code& error, std::list< std::vector<uint8> >::iterator itr);
    void HandleRecv(const boost::system::error_code& error, int32 actualBytes);
    void HandleTimer(const boost::system::error_code& error);

private:
    //! Called when the connection has successfully connected to the local host
    virtual void OnAccept(const std::string& host, uint16 port) = 0;

    //! Called when the connection has successfully connected to the remove host
    virtual void OnConnect(const std::string& host, uint16 port) = 0;

    //! Called when data has been sent by the connection
    virtual void OnSend(const std::vector<uint8>& buffer) = 0;

    //! Called when data has been received by the connection
    virtual void OnRecv(std::vector<uint8>& buffer) = 0;

    //! Called on each timer event
    virtual void OnTimer(const boost::posix_time::time_duration& delta) = 0;

    //! Called when an error is encountered
    virtual void OnError(const boost::system::error_code& error) = 0;

public:
    //! Returns the Hive object
    Hive* GetHive() { return _hive; }
    //! Returns the socket object
    boost::asio::ip::tcp::socket& GetSocket() { return _socket; }
    //! Returns the strand object
    boost::asio::strand& GetStrand() { return _ioStrand; }

    //! Sets the application specific receive buffer size used (default: 4KB)
    void SetReceiveBufferSize(int size) { _receiveBufferSize = size; }

    //! Returns the size of the receive buffer size
    int GetReceiveBufferSize() const { return _receiveBufferSize; }

    //! Set the timer interval (ms)
    void SetTimerInterval(int timerInterval) { _timerInterval = timerInterval; }

    //! Returns the timer interval
    int GetTimerInterval() const { return _timerInterval; }

    //! Returns true if this object has an error associated with it
    bool HasError() { return boost::interprocess::ipcdetail::atomic_cas32(&_errorState, 1, 1) == 1; }

    //! Binds the socket to the specified interface
    void Bind(const std::string& ip, uint16 port);

    //! starts an a/synchronous connect
    void Connect(const std::string& host, uint16 port);

    //! Posts a recv for the connection to process.
    /*! If total_bytes is 0, then as many bytes as possible up t
    GetReceiveBufferSize() will be waited for.
    If Recv is not 0, then the connection will wait for exactly
    total_bytes before invoking OnRecv */
    void Recv(int totalBytes = 0) { _ioStrand.post(boost::bind(&Connection::DispatchRecv, this, totalBytes)); }

    //! Posts an async disconnect event for the object to process
    void Disconnect() { _ioStrand.post(boost::bind(&Connection::HandleTimer, this, boost::asio::error::connection_reset)); }

protected:
    //! Posts data to be sent to the connection
    void Send(const std::vector<uint8>& buffer) { _ioStrand.post(boost::bind(&Connection::DispatchSend, this, buffer)); }

};

class Acceptor
{
    friend class Hive;

private:
    Hive* _hive;
    boost::asio::ip::tcp::acceptor _acceptor;
    boost::asio::strand _ioStrand;
    boost::asio::deadline_timer _timer;
    boost::posix_time::ptime _lastTime;
    int _timerInterval;
    volatile uint32 _errorState;

private:
    Acceptor(const Acceptor& other);
    Acceptor& operator =(const Acceptor& other);
    void StartTimer();
    void StartError(const boost::system::error_code& error);
    void DispatchAccept(Connection* connection)
    {
        _acceptor.async_accept(connection->GetSocket(), connection->GetStrand().wrap(
            boost::bind(&Acceptor::HandleAccept, this, _1, connection)));
    }
    void HandleTimer(const boost::system::error_code& error);
    void HandleAccept(const boost::system::error_code& error, Connection* connection);

protected:
    Acceptor(Hive* hive);

    virtual ~Acceptor() {}

private:
    //! Called when a connection has connected to the server.
    /*! This function should return true to invoke the connection's OnAccept
    function if the connection will be kept. If the connection will not be
    kept, the connection's Disconnect function should be called and the
    function should return false. */
    virtual bool OnAccept(Connection* conenction, const std::string& host, uint16 port) = 0;

    //! Called on each timer event
    virtual void OnTimer(const boost::posix_time::time_duration& delta) = 0;

    //! Called when an error is encountered
    virtual void OnError(const boost::system::error_code& error) = 0;

public:
    //! Returns the Hive object
    Hive* GetHive() { return _hive; }

    //! Returns the acceptor object
    boost::asio::ip::tcp::acceptor& GetAcceptor() { return _acceptor; }

    //! Returns the strand object
    boost::asio::strand& GetStrand() { return _ioStrand; }

    //! Sets the timer interval (ms) (default: 1000)
    void SetTimerInterval(int timerInterval) { _timerInterval = timerInterval; }

    //! Returns the timer interval
    int GetTimerInterval() const { return _timerInterval; }

    //! Returns true if this object has an error associated with it
    bool HasError() { return boost::interprocess::ipcdetail::atomic_cas32(&_errorState, 1, 1) == 1; }

public:
    //! Begin listening on the specific network interface
    void Listen(const std::string& host, const uint16& port);

    //! Posts the connection to the listening interface.
    /*! The next client that connections will be given this connection.
    If multiple calls to Accept are called at a time, then they are
    accepted in a FIFO order. */
    void Accept(Connection* connection) { _ioStrand.post(boost::bind(&Acceptor::DispatchAccept, this, connection)); }

    //! Stop the Acceptor from listening
    void Stop() { _ioStrand.post(boost::bind(&Acceptor::HandleTimer, this, boost::asio::error::connection_reset)); }
};

class Hive
{
private:
    boost::asio::io_service _ioService;
    boost::asio::io_service::work* _work;
    volatile uint32 _shutdown;

private:
    Hive(const Hive& other);
    Hive& operator =(const Hive& other);

public:
    Hive() : _work(new boost::asio::io_service::work(_ioService)), _shutdown(0) {}
    virtual ~Hive() {}

    //! Returns the io_service
    boost::asio::io_service& GetService() { return _ioService; }

    //! Returns true if the Stop function has been called
    bool HasStopped() { return boost::interprocess::ipcdetail::atomic_cas32(&_shutdown, 1, 1) == 1; }

    //! Polls the networking subsystem once from the current thread and returns
    void Poll() { _ioService.poll(); }

    //! Runs the networking system on the current thread.
    /*! This function blocks until the networking system is stopped,
    so do not call on a single threaded application with no other
    means of being able to call Stop */
    void Run() { _ioService.run(); }

    //! Stops the networking system
    /*! All work is finished and no more networking interactions will
    be possible afterwards until Reset is called. */
    void Stop();

    //! Restarts the networking system after Stop as been called.
    /*! A new work object is created ad the shutdown flag is cleared. */
    void Reset();
};

#endif // NETWORK_H
