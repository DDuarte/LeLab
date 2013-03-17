#include "OpcodeMgr.h"
#include <functional>
#include <boost/bind.hpp>
#include "Defines.h"
#include "Log.h"
#include "Packet.h"

void OpcodeMgr::AddHandler(uint16 opcode, OpcHandler handler)
{
#ifdef _DEBUG
    std::map<uint16, OpcHandler>::iterator itr = _handlers.find(opcode);
    if (itr != _handlers.end())
        LeLog.WriteP("Handler for opcode %u already registered.", opcode);
#endif

    _handlers[opcode] = handler;
}

void OpcodeMgr::Handle(Packet* packet)
{
    OpcHandler* handler = GetHandler(packet->GetOpcode());
    if (!handler)
    {
        LeLog.WriteP("Handler for opcode %u not found.", packet->GetOpcode());
        return;
    }

    boost::bind(*handler, packet)();
}

OpcHandler* OpcodeMgr::GetHandler(uint16 opcode)
{
    std::map<uint16, OpcHandler>::iterator itr = _handlers.find(opcode);
    if (itr == _handlers.end())
        return NULL;

    return &_handlers[opcode];
}
