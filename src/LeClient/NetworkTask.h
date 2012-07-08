#ifndef NETWORKTASK_H
#define NETWORKTASK_H

#include "ITask.h"
#include "TcpClient.h"

class NetworkTask : public ITask
{
private:
    Hive* _hive;
    TcpConnection* _connection;

public:
    NetworkTask();
    bool Start();
    void Update();
    void Stop();
};

#endif // NETWORKTASK_H
