#ifndef OPCODEMGR_H
#define OPCODEMGR_H

#include <map>
#include <functional>
#include "Defines.h"
//#include "Singleton.h"

class Packet;

enum Direction
{
    ClientToServer = 0, // CMSG
    ServerToClient = 1, // SMSG
};

typedef std::function<void (Packet* packet)> OpcHandler;

class OpcodeMgr// : Singleton<OpcodeMgr>
{
public:
    void AddHandler(uint16 opcode, OpcHandler handler);

    void Handle(Packet* packet);

private:
    std::map<uint16, OpcHandler> _handlers;
    OpcHandler* GetHandler(uint16 opcode);
};

#endif // OPCODEMGR_H
