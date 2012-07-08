#include "NetworkTask.h"
#include "SettingsManager.h"

NetworkTask::NetworkTask()
{
    _hive = new Hive();
}

bool NetworkTask::Start()
{
    _connection = new TcpConnection(_hive);
    _connection->Connect(GetConfig("connection.host", std::string), GetConfig("connection.port", int));
    return true;
}

void NetworkTask::Update()
{
    _hive->Poll();
    Sleep(1);
}

void NetworkTask::Stop()
{
    _hive->Stop();
    _connection->Disconnect();

    delete _hive;
    delete _connection;
}
