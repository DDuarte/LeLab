#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <LeEngine/Network.h>

class TcpServer : public Acceptor
{
private:
    bool OnAccept(Connection* connection, const std::string& host, uint16 port);
    void OnTimer(const boost::posix_time::time_duration& delta);
    void OnError(const boost::system::error_code& error);

public:
    TcpServer(Hive* hive);
    ~TcpServer() {}
};

#endif // TCPSERVER_H
