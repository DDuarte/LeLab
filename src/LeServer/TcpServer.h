#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <string>
#include <boost/asio.hpp>
#include "Session.h"

using boost::asio::ip::tcp;

class TcpServer
{
public:
    TcpServer(boost::asio::io_service* ioService, int port, std::string name);

    std::string GetName() const { return _name; }
    void SetName(std::string name) { _name = name; }

    int GetPort() const { return _acceptor.local_endpoint().port(); }

    void StartAccept();

    void HandleAccept(boost::shared_ptr<Session> session,
        const boost::system::error_code& error);

private:
    std::string _name;
    boost::asio::io_service* _io;
    tcp::acceptor _acceptor;
};

#endif // TCPSERVER_H
