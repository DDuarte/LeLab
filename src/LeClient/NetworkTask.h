#ifndef NETWORKTASK_H
#define NETWORKTASK_H

#include <LeEngine/ITask.h>
#include "TcpClient.h"
#include <LeEngine/Singleton.h>
#include <LeEngine/Packet.h>
#include <LeEngine/OpcodeMgr.h>
#include <queue>

class NetworkTask : public ITask, public Singleton<NetworkTask>
{
private:
    Hive* _hive;
    TcpConnection* _connection;
    std::queue<Packet> _packetQueue;
    OpcodeMgr _opcodeManager;

public:
    NetworkTask();
    bool Start();
    void Update();
    void Stop();

    void Send(Packet* packet);
    void AddPacket(Packet packet) { _packetQueue.push(packet); }

    static void HandleHello(Packet* packet);
};

#endif // NETWORKTASK_H
