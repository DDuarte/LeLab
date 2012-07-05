#ifndef PACKET_H
#define PACKET_H

#include "ByteBuffer.h"
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
    Packet(uint16 opcode, uint32 reserveSize) : ByteBuffer(reserveSize), _opcode(opcode) {}
    Packet(const Packet& other) : ByteBuffer(other), _opcode(other._opcode) {}

    uint16 GetOpcode() const { return _opcode; }
    void SetOpcode(uint16 opcode) { _opcode = opcode; }

    uint32 GetDataSize() const { return _buffer.size(); }

};

#endif // PACKET_H
