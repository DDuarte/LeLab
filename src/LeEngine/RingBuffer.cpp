#include "RingBuffer.h"

template <class T, uint32 bufSize>
bool RingBuffer<T, bufSize>::operator <<(T& obj)
{
    _buffer[_write] = obj;
    ++_write;
    while (_write >= bufSize)
        _write -= bufSize;

    if (_write == _read)
    {
        --_write;
        while (_write < 0)
            _write += bufSize;
        return false;
    }

    return true;
}


template <class T, uint32 bufSize>
bool RingBuffer<T, bufSize>::operator >>(T& res)
{
    ++_read;
    while (_write >= bufSize)
        _write -= bufSize;
    
    if (_write == _read)
    {
        ++_write;
        while (_write >= bufSize)
            _write -= _bufSize;
        return false;
    }

    res = buf[_read];
    return true;
}

template <class T, uint32 bufSize>
uint32 RingBuffer<T, bufSize>::DataSize()
{
    uint32 wc = _write;
    while (wc < _read)
        wc += bufSize;
    return wc-_read-1;
}

template <class T, uint32 bufSize>
void RingBuffer<T, bufSize>::Flood(const T& value)
{
    _read = 0;
    for (_write = 0; _write < bufSize; ++_write)
        _buffer[_write] = value;
    _write = 1;
}
