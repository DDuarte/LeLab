#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "Network.h"

class TcpConnection : public Connection
{
private:

private:
    void OnAccept(const std::string& host, uint16 port)
    {
        std::cout << "[" << __FUNCTION__ << "] " << host << ":" << port << std::endl;

        // Start the next receive
        Recv();
    }

    void OnConnect(const std::string& host, uint16 port)
    {
        std::cout << "[" << __FUNCTION__ << "] " << host << ":" << port << std::endl;

        // Start the next receive
        Recv();

        std::string str = "TEST";

        std::vector<uint8> request;
        std::copy(str.begin(), str.end(), std::back_inserter(request));
        Send(request);
    }

    void OnSend(const std::vector<uint8>& buffer)
    {
        std::cout << "[" << __FUNCTION__ << "] " << buffer.size() << " bytes" << std::endl;
        for(size_t x = 0; x < buffer.size(); ++x)
        {
            std::cout << std::hex << std::setfill('0') << 
                std::setw(2) << (int)buffer[x] << " ";
            if((x + 1) % 16 == 0)
                std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    void OnRecv(std::vector<uint8>& buffer)
    {
        std::cout << "[" << __FUNCTION__ << "] " << buffer.size() << " bytes" << std::endl;
        for(size_t x = 0; x < buffer.size(); ++x)
        {
            std::cout << std::hex << std::setfill('0') << 
                std::setw(2) << (int)buffer[x] << " ";
            if((x + 1) % 16 == 0)
            {
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;

        // Start the next receive
        Recv();
    }

    void OnTimer(const boost::posix_time::time_duration& delta)
    {
        std::cout << "[" << __FUNCTION__ << "] " << delta << std::endl;
    }

    void OnError(const boost::system::error_code& error)
    {
        std::cout << "[" << __FUNCTION__ << "] " << error << std::endl;
    }

public:
    TcpConnection(Hive* hive) : Connection(hive) {}

    ~TcpConnection() {}
};

#endif // TCPCLIENT_H
