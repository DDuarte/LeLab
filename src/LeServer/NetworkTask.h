#ifndef NETWORKTASK_H
#define NETWORKTASK_H

#include "ITask.h"
#include "TcpServer.h"

class NetworkTask : public ITask
{
private:
    Hive* _hive;
    TcpAcceptor* _acceptor;

public:
    NetworkTask();
    bool Start();
    void Update();
    void Stop();
};

#endif // NETWORKTASK_H
