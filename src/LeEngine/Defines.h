#ifndef DEFINES_H
#define DEFINES_H

#include <sstream>
#include <string>
#include <boost/integer.hpp>
#include <boost/lexical_cast.hpp>

#define INVALID_OGL_VALUE 0xFFFFFFFF

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

template<typename T>
class Vector3
{
public:
    Vector3() : X(static_cast<T>(0)), Y(static_cast<T>(0)), Z(static_cast<T>(0)) { }
    Vector3(T x, T y, T z) : X(x), Y(y), Z(z) { }
    T X, Y, Z;
};

typedef Vector2<uint32> Size2;

template<typename T>
inline void SAFE_DELETE(T* p)
{
    delete p;
    p = NULL;
}

template<typename T>
inline std::string ToString(T& val)
{
    return boost::lexical_cast<std::string>(val);
}

class Version
{
public:
    uint8 Major, Minor, Revision;
    friend std::ostream& operator<<(std::ostream &out, Version &v)
    {
        out << v.Major << "." << v.Minor << "." << v.Revision;
        return out;
    }
};



#endif // DEFINES_H
