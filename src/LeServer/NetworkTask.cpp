#include "NetworkTask.h"

NetworkTask::NetworkTask()
{
    _hive = new Hive();
    _server = new TcpServer(_hive);
}

bool NetworkTask::Start()
{
    AcceptNew();

    AddHandler(2, &Session::HandleTest);

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
