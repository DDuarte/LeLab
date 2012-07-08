#ifndef NETWORKTASK_H
#define NETWORKTASK_H

#include "ITask.h"
#include "TcpServer.h"
#include "Session.h"
#include "Singleton.h"

class NetworkTask : public ITask, public Singleton<NetworkTask>
{
private:
    Hive* _hive;
    TcpServer* _server;

    std::list<Session*> _sessions;

public:
    NetworkTask();
    bool Start();
    void Update();
    void Stop();

    void NewSession()
    {
        Session* session = new Session(_hive);
        _sessions.push_back(session);

        _server->Accept((Connection*)session);
    }
};

#endif // NETWORKTASK_H
