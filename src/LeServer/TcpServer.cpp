#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <string>

#include "Session.h"
#include "TcpServer.h"

using boost::asio::ip::tcp;

TcpServer::TcpServer(boost::asio::io_service* ioService, int port, std::string name)
    : _io(ioService), _name(name), _acceptor(*ioService, tcp::endpoint(tcp::v4(), port))
{
    StartAccept();
}

void TcpServer::StartAccept()
{
    boost::shared_ptr<Session> session(new Session(*_io));
    _acceptor.async_accept(session->GetSocket(),
        boost::bind(&TcpServer::HandleAccept, this, session,
        boost::asio::placeholders::error));
}

void TcpServer::HandleAccept(boost::shared_ptr<Session> session, const boost::system::error_code& error)
{
    if (!error)
        session->Start();

    StartAccept();
}
