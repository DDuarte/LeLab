#ifndef DEFINES_H
#define DEFINES_H

#include <boost/integer.hpp>

// Helper typedefs

typedef boost::int8_t int8;
typedef boost::int16_t int16;
typedef boost::int32_t int32;
typedef boost::int64_t int64;
typedef boost::uint8_t uint8;
typedef boost::uint16_t uint16;
typedef boost::uint32_t uint32;
typedef boost::uint64_t uint64;

template<typename T>
class Vector2
{
public:
    Vector2() : X(static_cast<T>(0)), Y(static_cast<T>(0)) { }
    Vector2(T x, T y) : X(x), Y(y) { }
    T X, Y;
};

typedef Vector2<uint32> Size2;


#endif // DEFINES_H
