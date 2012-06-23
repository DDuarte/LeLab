#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include "Defines.h"

// TODO: Replace by boost::circular_buffer

template <class T, uint32 bufSize>
class RingBuffer
{
protected:
    T _buffer[bufSize];
    uint32 _read, _write;

public:
    RingBuffer() : _read(0), _write(1) {}

    bool operator << (T& obj);
    bool operator >> (T& res);

    uint32 DataSize();

    void Flood(const T& value);

};

#endif // RINGBUFFER_H
