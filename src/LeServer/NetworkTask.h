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
    NetworkTask()
    {
        _hive = new Hive();
        _acceptor = new TcpAcceptor(_hive);
    }

    bool Start() 
    {
        // accept one connection; next one will be accepted in TcpAcceptor::OnAccept
        TcpConnection* connection = new TcpConnection(_hive);
        _acceptor->Accept(connection);
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
        _acceptor->Stop();

        delete _acceptor;
        delete _hive;
    }
};

#endif // NETWORKTASK_H
