#include "NetworkTask.h"
#include <LeEngine/Log.h>
#include <functional>

NetworkTask::NetworkTask() : ITask("NetworkTask")
{
    _hive = new Hive();
    _server = new TcpServer(_hive);
}

bool NetworkTask::Start()
{
    AcceptNew();

    AddHandler(2, std::mem_fn(&Session::HandleTest));

    return true;
}

void NetworkTask::Update()
{
    _hive->Poll();
    
    if (!_packetQueue.empty())
    {
        Handle(_packetQueue.front().first, &_packetQueue.front().second);
        _packetQueue.pop();
    }
}

void NetworkTask::Stop()
{
    for (std::list<Session*>::iterator itr = _sessions.begin(); itr != _sessions.end(); ++itr)
    {
        if (*itr)
        {
            (*itr)->Disconnect();
            delete (*itr);
        }
    }
    _sessions.clear();

    _hive->Stop();
    _server->Stop();

    delete _server;
    delete _hive;
}

void NetworkTask::AcceptNew()
{
    Session* session = new Session(_hive);
    _server->Accept((Connection*)session);
}

void NetworkTask::AddSession(Session* session)
{
    _sessions.push_back(session);
}

void NetworkTask::AddHandler(uint16 opcode, OpcHandler handler)
{
#ifdef _DEBUG
    std::map<uint16, OpcHandler>::iterator itr = _handlers.find(opcode);
    if (itr != _handlers.end())
        LeLog.WriteP("Handler for opcode %u already registered.", opcode);
#endif

    _handlers[opcode] = handler;
}

void NetworkTask::Handle(Session* session, Packet* packet)
{
    OpcHandler* handler = GetHandler(packet->GetOpcode());
    if (handler)
        (*handler)(session, packet);
}

OpcHandler* NetworkTask::GetHandler(uint16 opcode)
{
    std::map<uint16, OpcHandler>::iterator itr = _handlers.find(opcode);
    if (itr == _handlers.end())
        return NULL;

    return &_handlers[opcode];
}
