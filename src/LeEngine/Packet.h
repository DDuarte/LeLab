#ifndef PACKET_H
#define PACKET_H

#include "ByteBuffer.h"
#include "Opcode.h"
#include "Defines.h"

class Packet : public ByteBuffer
{
protected:
    // uint64 _time; // unix time
    // uint8 _direction; // enum Direction
    uint16 _opcode; // enum Opcode
    // uint16 _length;
    // Byte* _data;

public:
    Packet(Opcode opcode, uint32 reserveSize) : ByteBuffer(reserveSize), _opcode((uint16)opcode) {}
    Packet(const Packet& other) : ByteBuffer(other), _opcode(other._opcode) {}

    Opcode GetOpcode() const { _return (Opcode)_opcode; }
    void SetOpcode(Opcode opcode) { _opcode = opcode; }

    uint32 GetDataSize() const { return _buffer.size(); }

};

#endif // PACKET_H
