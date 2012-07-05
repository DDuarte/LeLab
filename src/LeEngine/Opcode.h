#ifndef OPCODE_H
#define OPCODE_H

enum Opcode
{
    NONE = 0,
    CMSG_TEXT_MESSAGE = 1,
};

enum Direction
{
    ClientToServer = 0, // CMSG
    ServerToClient = 1, // SMSG
};

#endif // OPCODE_H
