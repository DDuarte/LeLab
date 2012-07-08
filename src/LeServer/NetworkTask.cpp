#include "NetworkTask.h"
#include "Session.h"

NetworkTask::NetworkTask()
{
    _hive = new Hive();
    _server = new TcpServer(_hive);
}

bool NetworkTask::Start()
{
    NewSession();
    return true;
}

void NetworkTask::Update()
{
    _hive->Poll();
    Sleep(1);
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
