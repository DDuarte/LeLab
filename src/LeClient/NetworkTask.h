#ifndef NETWORKTASK_H
#define NETWORKTASK_H

#include "ITask.h"
#include "TcpClient.h"
#include "SettingsManager.h"

class NetworkTask : public ITask
{
private:
    Hive* _hive;
    TcpConnection* _connection;

public:
    NetworkTask()
    {
        _hive = new Hive();
    }

    bool Start() 
    {
        _connection = new TcpConnection(_hive);
        _connection->Connect(GetConfig("connection.host", std::string), GetConfig("connection.port", int));
        return true;
    }

    void Update() 
    {
        _hive->Poll();
        Sleep(1);
    }

    void Stop() 
    {
        _hive->Stop();
        _connection->Disconnect();

        delete _hive;
        delete _connection;
    }
};

#endif // NETWORKTASK_H
