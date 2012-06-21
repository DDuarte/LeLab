#include <iostream>
#include <string>
#include <boost/asio.hpp>

#include "TcpServer.h"

int main(int argc, char* argv[])
{
    const int PORT = 35430;
    const std::string NAME = "Server1";

    boost::asio::io_service io;
    TcpServer server(&io, PORT, NAME);

    return 0;
}