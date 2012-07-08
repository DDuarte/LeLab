#include "NetworkTask.h"

NetworkTask::NetworkTask()
{
    _hive = new Hive();
    _acceptor = new TcpAcceptor(_hive);
}

bool NetworkTask::Start()
{
    // accept one connection; next one will be accepted in TcpAcceptor::OnAccept
    TcpConnection* connection = new TcpConnection(_hive);
    _acceptor->Accept(connection);
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
    _acceptor->Stop();

    delete _acceptor;
    delete _hive;
}
