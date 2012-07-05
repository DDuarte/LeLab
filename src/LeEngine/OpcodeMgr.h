#ifndef OPCODEMGR_H
#define OPCODEMGR_H

#include <map>
#include <boost/function.hpp>
#include "Defines.h"

class Packet;

enum Direction
{
    ClientToServer = 0, // CMSG
    ServerToClient = 1, // SMSG
};

typedef boost::function<void (Packet* packet)> OpcHandler;

class OpcodeMgr
{
public:
    void AddHandler(uint16 opcode, OpcHandler handler);

    void BindAndCall(Packet* packet);

private:
    std::map<uint16, OpcHandler> _handlers;
    OpcHandler* GetHandler(uint16 opcode);
};

#endif // OPCODEMGR_H
