#ifndef NETWORKTASK_H
#define NETWORKTASK_H

#include "ITask.h"
#include "TcpClient.h"
#include "Singleton.h"
#include "Packet.h"
#include "OpcodeMgr.h"
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
