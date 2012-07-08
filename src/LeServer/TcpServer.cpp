#include "TcpServer.h"
#include "SettingsManager.h"
#include "NetworkTask.h"

TcpServer::TcpServer(Hive* hive) : Acceptor(hive)
{
    Listen(GetConfig("server.bindIp", std::string), GetConfig("server.port", int));
}

bool TcpServer::OnAccept(Connection* connection, const std::string& host, uint16 port)
{
    std::cout << "[" << __FUNCTION__ << "] " << host << ":" << port << std::endl;

    NetworkTask::Get().NewSession();

    return true;
}

void TcpServer::OnTimer(const boost::posix_time::time_duration& delta)
{
    std::cout << "[" << __FUNCTION__ << "] " << delta << std::endl;
}

void TcpServer::OnError(const boost::system::error_code& error)
{
    std::cout << "[" << __FUNCTION__ << "] " << error << std::endl;
}
