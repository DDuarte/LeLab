#include "ByteBuffer.h"
#include <vector>
#include <ostream>
#include <sstream>
#include <string>
#include <cstdio>
#include <iomanip>
#include <cctype>

ByteBuffer::ByteBuffer() : _readPos(0), _writePos(0)
{
    _buffer.reserve(DEFAULT_BUFFER_SIZE);
}

ByteBuffer::ByteBuffer(uint32 capacity) : _readPos(0), _writePos(0)
{
    _buffer.reserve(capacity);
}

ByteBuffer::ByteBuffer(const ByteBuffer& other)
    : _readPos(other._readPos), _writePos(other._writePos), _buffer(other._buffer) {}

const Byte* ByteBuffer::Data() const
{
    return &_buffer[0];
}

void ByteBuffer::Clear()
{
    _buffer.clear();
    _readPos = 0;
    _writePos = 0;
}

Byte ByteBuffer::operator[](uint32 pos) const
{
    return Read<Byte>(pos);
}

uint32 ByteBuffer::GetReadPos() const
{
    return _readPos;
}

void ByteBuffer::SetReadPos(uint32 readPos)
{
    _readPos = readPos;
}

uint32 ByteBuffer::GetWritePos() const
{
    return _writePos;
}

void ByteBuffer::SetWritePos(uint32 writePos)
{
    _writePos = writePos;
}

void ByteBuffer::FinishRead()
{
    _readPos = _writePos;
}

void ByteBuffer::ReadSkip(uint32 size)
{
    assert(_readPos + size <= Size());
    _readPos += size;
}

void ByteBuffer::Read(Byte* dest, uint32 count)
{
    assert(_readPos + count <= Size());
    memcpy(dest, &_buffer[_readPos], count);
    _readPos += count;
}

void ByteBuffer::Append(const ByteBuffer& other)
{
    if (_writePos)
        Append(other.Data(), other._writePos);
}

void ByteBuffer::Append(const Byte* src, uint32 count)
{
    assert(count);
    assert(src);
    assert(Size() < 100000);

    if (Size() < _writePos + count)
        _buffer.resize(_writePos + count);
    memcpy(&_buffer[_writePos], src, count);
    _writePos += count;
}

void ByteBuffer::Put(uint32 pos, const Byte* src, uint32 count)
{
    assert(pos + count <= Size());
    assert(src);

    memcpy(&_buffer[pos], src, count);
}

uint32 ByteBuffer::Size() const
{
    return _buffer.size();
}

bool ByteBuffer::IsEmpty() const
{
    return _buffer.empty();
}

void ByteBuffer::Resize(uint32 newSize)
{
    _buffer.resize(newSize, 0);
    _readPos = 0;
    _writePos = Size();
}

void ByteBuffer::Reserve(uint32 size)
{
    if (size > Size())
        _buffer.reserve(size);
}

void ByteBuffer::Print(std::ostream& stream) const
{
    const char* header = "|-------------------------------------------------|---------------------------------|\n"
        "| 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F | 0 1 2 3 4 5 6 7 8 9 A B C D E F |\n"
        "|-------------------------------------------------|---------------------------------|\n";

    stream << header;

    std::stringstream text;
    std::stringstream hex;

    uint32 length = Size();
    for (uint32 i = 0; i < length; i += 16) // 16 bytes per line
    {
        hex << "| ";

        for (int j = 0; j < 16; ++j)
        {
            if (j + i < length)
            {
                Byte val = _buffer[j + i];
                char h[3]; // 2 chars + 1 null
                sprintf(h, "%X", val); // convert byte to hex upper-case
                hex << std::setfill('0') << std::setw(2) << h << " ";

                // print all printable characters in the text side
                if (std::isgraph(val))
                    text << (char)val;
                else
                    text << ".";

                text << " ";
            }
            else
            {
                hex << "   ";
                text << "  ";
            }
        }

        hex << "| " << text.str() << "|\n";
        stream << hex.str();

        // reset streams to be re-used
        hex.str("");
        hex.clear();
        text.str("");
        text.clear();
    }

    stream << "|-------------------------------------------------|---------------------------------|\n";
}

ByteBuffer& ByteBuffer::operator <<(bool value) { Append<bool>(value); return *this; }
ByteBuffer& ByteBuffer::operator <<(uint8 value) { Append<uint8>(value); return *this; }
ByteBuffer& ByteBuffer::operator <<(uint16 value) { Append<uint16>(value); return *this; }
ByteBuffer& ByteBuffer::operator <<(uint32 value) { Append<uint32>(value); return *this; }
ByteBuffer& ByteBuffer::operator <<(uint64 value) { Append<uint64>(value); return *this; }
ByteBuffer& ByteBuffer::operator <<(int8 value) { Append<int8>(value); return *this; }
ByteBuffer& ByteBuffer::operator <<(int16 value) { Append<int16>(value); return *this; }
ByteBuffer& ByteBuffer::operator <<(int32 value) { Append<int32>(value); return *this; }
ByteBuffer& ByteBuffer::operator <<(int64 value) { Append<int64>(value); return *this; }
ByteBuffer& ByteBuffer::operator <<(float value) { Append<float>(value); return *this; }
ByteBuffer& ByteBuffer::operator <<(double value) { Append<double>(value); return *this; }
ByteBuffer& ByteBuffer::operator <<(const ByteBuffer& other) { Append(other); return *this; }
ByteBuffer& ByteBuffer::operator <<(const std::string& value)
{
    if (size_t length = value.length())
        Append((uint8 const*)value.c_str(), length);
    Append((uint8)0); // null terminator
    return *this;
}

ByteBuffer& ByteBuffer::operator <<(const char* str)
{
    size_t length = 0;
    if (str && (length = strlen(str)))
        Append((uint8 const*)str, length);
    Append((uint8)0); // null terminator
    return *this;
}

ByteBuffer& ByteBuffer::operator >>(bool& value) { value = Read<uint8>() > 0 ? true : false; return *this; }
ByteBuffer& ByteBuffer::operator >>(uint8& value) { value = Read<uint8>(); return *this; }
ByteBuffer& ByteBuffer::operator >>(uint16& value) { value = Read<uint16>(); return *this; }
ByteBuffer& ByteBuffer::operator >>(uint32& value) { value = Read<uint32>(); return *this; }
ByteBuffer& ByteBuffer::operator >>(uint64& value) { value = Read<uint64>(); return *this; }
ByteBuffer& ByteBuffer::operator >>(int8& value) { value = Read<int8>(); return *this; }
ByteBuffer& ByteBuffer::operator >>(int16& value) { value = Read<int16>(); return *this; }
ByteBuffer& ByteBuffer::operator >>(int32& value) { value = Read<int32>(); return *this; }
ByteBuffer& ByteBuffer::operator >>(int64& value) { value = Read<int64>(); return *this; }
ByteBuffer& ByteBuffer::operator >>(float& value) { value = Read<float>(); return *this; }
ByteBuffer& ByteBuffer::operator >>(double& value) { value = Read<double>(); return *this; }
ByteBuffer& ByteBuffer::operator >>(std::string& value)
{
    value.clear();
    while (_readPos < Size())
    {
        char c = Read<char>();
        if (c == 0)
            break;
        value += c;
    }

    return *this;
}
