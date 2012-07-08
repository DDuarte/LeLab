#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "Network.h"

class TcpConnection : public Connection
{
private:
    void OnAccept(const std::string& host, uint16 port);
    void OnConnect(const std::string& host, uint16 port);
    void OnSend(const std::vector<uint8>& buffer);
    void OnRecv(std::vector<uint8>& buffer);
    void OnTimer(const boost::posix_time::time_duration& delta);
    void OnError(const boost::system::error_code& error);

public:
    TcpConnection(Hive* hive) : Connection(hive) {}
    ~TcpConnection() {}
};

class TcpAcceptor : public Acceptor
{
private:
    bool OnAccept(Connection* connection, const std::string& host, uint16 port);
    void OnTimer(const boost::posix_time::time_duration& delta);
    void OnError(const boost::system::error_code& error);

public:
    TcpAcceptor(Hive* hive);
    ~TcpAcceptor() {}
};

#endif // TCPSERVER_H
