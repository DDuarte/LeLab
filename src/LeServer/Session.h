#ifndef SESSION_H
#define SESSION_H

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>

using boost::asio::ip::tcp;

class Session : public boost::enable_shared_from_this<Session>
{
public:
    Session(boost::asio::io_service& io)
        : _socket(io)
    {
    }

    void Start()
    {
        // room_.join(shared_from_this());
        //boost::asio::async_read(_socket,
         //   boost::asio::buffer(read_msg.))
    }

    tcp::socket& GetSocket() { return _socket; }

private:
    tcp::socket _socket;
};

#endif // SESSION_H

