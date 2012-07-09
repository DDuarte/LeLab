#include "Session.h"
#include "Packet.h"

void Session::OnAccept(const std::string& host, uint16 port)
{
    std::cout << "[" << __FUNCTION__ << "] " << host << ":" << port << std::endl;

    // Start the next receive
    Recv();

    Packet packet(1, 10);
    std::string hi = "Hello World";
    packet << hi;
    Send(&packet);
}

void Session::OnConnect(const std::string& host, uint16 port)
{
    std::cout << "[" << __FUNCTION__ << "] " << host << ":" << port << std::endl;

    // Start the next receive
    Recv();
}

void Session::OnSend(const std::vector<uint8>& buffer)
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

void Session::OnRecv(std::vector<uint8>& buffer)
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
    Connection::Send(buffer);
}

void Session::OnTimer(const boost::posix_time::time_duration& delta)
{
    std::cout << "[" << __FUNCTION__ << "] " << delta << std::endl;
}

void Session::OnError(const boost::system::error_code& error)
{
    std::cout << "[" << __FUNCTION__ << "] " << error << std::endl;
}
