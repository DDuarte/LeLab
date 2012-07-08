#ifndef SESSION_H
#define SESSION_H

#include "Network.h"
#include "Packet.h"
#include "OpcodeMgr.h"

#include "Defines.h"
#include <ctime>
#include <vector>
#include <cstring>

class Session : public Connection
{
private:
    void OnAccept(const std::string& host, uint16 port);
    void OnConnect(const std::string& host, uint16 port);
    void OnSend(const std::vector<uint8>& buffer);
    void OnRecv(std::vector<uint8>& buffer);
    void OnTimer(const boost::posix_time::time_duration& delta);
    void OnError(const boost::system::error_code& error);

public:
    Session(Hive* hive) : Connection(hive) {}

    void Send(Packet* packet)
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
};

#endif // SESSION_H
