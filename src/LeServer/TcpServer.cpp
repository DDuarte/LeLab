#include "TcpServer.h"
#include <string>
#include <iomanip>
#include "SettingsManager.h"

void TcpConnection::OnAccept(const std::string& host, uint16 port)
{
    std::cout << "[" << __FUNCTION__ << "] " << host << ":" << port << std::endl;

    // Start the next receive
    Recv();
}

void TcpConnection::OnConnect(const std::string& host, uint16 port)
{
    std::cout << "[" << __FUNCTION__ << "] " << host << ":" << port << std::endl;

    // Start the next receive
    Recv();
}

void TcpConnection::OnSend(const std::vector<uint8>& buffer)
{
    std::cout << "[" << __FUNCTION__ << "] " << buffer.size() << " bytes" << std::endl;
    for(size_t x = 0; x < buffer.size(); ++x)
    {
        std::cout << std::hex << std::setfill('0') << std::setw(2) << (int)buffer[x] << " ";
        if((x + 1) % 16 == 0)
            std::cout << std::endl;
    }
    std::cout << std::endl;
}

void TcpConnection::OnRecv(std::vector<uint8>& buffer)
{
    std::cout << "[" << __FUNCTION__ << "] " << buffer.size() << " bytes" << std::endl;
    for (size_t x = 0; x < buffer.size(); ++x)
    {
        std::cout << std::hex << std::setfill('0') << std::setw(2) << (int)buffer[x] << " ";
        if ((x + 1) % 16 == 0)
            std::cout << std::endl;
    }
    std::cout << std::endl;

    // Start the next receive
    Recv();

    // Echo the data back
    Send(buffer);
}

void TcpConnection::OnTimer(const boost::posix_time::time_duration& delta)
{
    std::cout << "[" << __FUNCTION__ << "] " << delta << std::endl;
}

void TcpConnection::OnError(const boost::system::error_code& error)
{
    std::cout << "[" << __FUNCTION__ << "] " << error << std::endl;
}


bool TcpAcceptor::OnAccept(Connection* connection, const std::string& host, uint16 port)
{
    std::cout << "[" << __FUNCTION__ << "] " << host << ":" << port << std::endl;

    // accept a new connection
    TcpConnection* newConnection = new TcpConnection(GetHive());
    Accept(newConnection);

    return true;
}

void TcpAcceptor::OnTimer(const boost::posix_time::time_duration& delta)
{
    std::cout << "[" << __FUNCTION__ << "] " << delta << std::endl;
}

void TcpAcceptor::OnError(const boost::system::error_code& error)
{
    std::cout << "[" << __FUNCTION__ << "] " << error << std::endl;
}

TcpAcceptor::TcpAcceptor(Hive* hive) : Acceptor(hive)
{
    Listen(GetConfig("server.bindIp", std::string), GetConfig("server.port", int));
}
