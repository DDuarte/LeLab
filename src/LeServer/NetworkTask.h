#ifndef NETWORKTASK_H
#define NETWORKTASK_H

#include "ITask.h"
#include "TcpServer.h"
#include "Session.h"
#include "Singleton.h"
#include <queue>
#include <utility>
#include <boost/function.hpp>
#include <map>

enum Direction
{
    ClientToServer = 0, // CMSG
    ServerToClient = 1, // SMSG
};

typedef boost::function<void (Session*, Packet*)> OpcHandler;

class NetworkTask : public ITask, public Singleton<NetworkTask>
{
private:
    Hive* _hive;
    TcpServer* _server;

    std::list<Session*> _sessions;
    std::queue< std::pair<Session*, Packet> > _packetQueue;

    std::map<uint16, OpcHandler> _handlers;

public:
    NetworkTask();
    bool Start();
    void Update();
    void Stop();

    void AcceptNew();
    void AddSession(Session* session);
    void AddPacket(Session* session, Packet packet) { _packetQueue.push(std::make_pair(session, packet)); }

    void AddHandler(uint16 opcode, OpcHandler handler);
    OpcHandler* GetHandler(uint16 opcode);
    void Handle(Session* session, Packet* packet);

};

#endif // NETWORKTASK_H
