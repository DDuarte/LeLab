#include "Session.h"
#include <LeEngine/Packet.h>
#include "NetworkTask.h"
#include <ctime>
#include <vector>
#include <cstring>

void Session::OnAccept(const std::string& host, uint16 port)
{
    std::cout << "[" << __FUNCTION__ << "] " << host << ":" << port << std::endl;

    // Start the next receive
    Recv();

    NetworkTask::Get().AddSession(this);

    Packet packet(1, 10);
    packet << "Hello World";
    Send(&packet);
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

    NetworkTask::Get().AddPacket(this, Packet(buffer));
}

void Session::OnTimer(const boost::posix_time::time_duration& delta)
{
    std::cout << "[" << __FUNCTION__ << "] " << delta << std::endl;
}

void Session::OnError(const boost::system::error_code& error)
{
    std::cout << "[" << __FUNCTION__ << "] " << error << std::endl;
}

void Session::Send(Packet* packet)
{
    uint64 time = (uint64)std::time(NULL);
    uint8 direction = (uint8)ServerToClient;
    uint16 opcode = packet->GetOpcode();
    uint16 length = (uint16)packet->GetDataSize();

    std::vector<uint8> buffer(packet->GetDataSize() + 13);
    buffer.resize(packet->GetDataSize() + 13);

    memcpy(&buffer[0],  &time,          8);
    memcpy(&buffer[8],  &direction,     1);
    memcpy(&buffer[9],  &opcode,        2);
    memcpy(&buffer[11], &length,        2);
    memcpy(&buffer[13], packet->Data(), packet->GetDataSize());

    Connection::Send(buffer);
}

