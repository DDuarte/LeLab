#ifndef NETWORKTASK_H
#define NETWORKTASK_H

#include "ITask.h"
#include "TcpServer.h"
#include "Session.h"
#include "Singleton.h"
#include "Log.h"
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

    void AddHandler(uint16 opcode, OpcHandler handler)
    {
#ifdef _DEBUG
        std::map<uint16, OpcHandler>::iterator itr = _handlers.find(opcode);
        if (itr != _handlers.end())
            LeLog.WriteP("Handler for opcode %u already registered.", opcode);
#endif

        _handlers[opcode] = handler;
    }

    void Handle(Session* session, Packet* packet)
    {
        OpcHandler* handler = GetHandler(packet->GetOpcode());
        if (handler)
            (*handler)(session, packet);
    }

    OpcHandler* GetHandler(uint16 opcode)
    {
        std::map<uint16, OpcHandler>::iterator itr = _handlers.find(opcode);
        if (itr == _handlers.end())
            return NULL;

        return &_handlers[opcode];
    }
};

#endif // NETWORKTASK_H
