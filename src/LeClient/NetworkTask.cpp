#include "NetworkTask.h"
#include "SettingsManager.h"
#include "Packet.h"
#include "OpcodeMgr.h"
#include <ctime>
#include <iostream>
#include <string>

NetworkTask::NetworkTask()
{
    _hive = new Hive();
}

bool NetworkTask::Start()
{
    _opcodeManager.AddHandler(1, &NetworkTask::HandleHello);

    _connection = new TcpConnection(_hive);
    _connection->Connect(GetConfig("connection.host", std::string), GetConfig("connection.port", int));
    return true;
}

void NetworkTask::HandleHello(Packet* packet)
{
    std::string test;
    (*packet) >> test;
    std::cout << test << std::endl;
}

void NetworkTask::Update()
{
    _hive->Poll();
    
    if (!_packetQueue.empty())
    {
        _opcodeManager.Handle(&_packetQueue.front());
        _packetQueue.pop();
    }
}

void NetworkTask::Stop()
{
    _hive->Stop();
    _connection->Disconnect();

    delete _hive;
    delete _connection;
}

void NetworkTask::Send(Packet* packet)
{
    uint64 time = (uint64)std::time(NULL);
    uint8 direction = (uint8)ClientToServer;
    uint16 opcode = packet->GetOpcode();
    uint16 length = (uint16)packet->GetDataSize();

    std::vector<uint8> buffer(packet->GetDataSize() + 13);
    buffer.resize(packet->GetDataSize() + 13);

    memcpy(&buffer[0],  &time,          8);
    memcpy(&buffer[8],  &direction,     1);
    memcpy(&buffer[9],  &opcode,        2);
    memcpy(&buffer[11], &length,        2);
    memcpy(&buffer[13], packet->Data(), packet->GetDataSize());

    _connection->Send(buffer);
}
