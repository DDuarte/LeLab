#ifndef SESSION_H
#define SESSION_H

#include <LeEngine/Network.h>
#include <LeEngine/Packet.h>
#include <LeEngine/Defines.h>

#include <iostream>

class Session : public Connection
{
private:
    void OnAccept(const std::string& host, uint16 port);
    void OnConnect(const std::string& host, uint16 port) {} // never called, use OnAccept
    void OnSend(const std::vector<uint8>& buffer);
    void OnRecv(std::vector<uint8>& buffer);
    void OnTimer(const boost::posix_time::time_duration& delta);
    void OnError(const boost::system::error_code& error);

public:
    Session(Hive* hive) : Connection(hive) {}

    void Send(Packet* packet);

    void HandleTest(Packet* packet)
    {
        std::string a;
        (*packet) >> a;
        std::cout << a << std::endl;
    }
};

#endif // SESSION_H
