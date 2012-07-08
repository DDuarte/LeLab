#ifndef DEFINES_H
#define DEFINES_H

#include <sstream>
#include <string>
#include <boost/integer.hpp>
#include <boost/lexical_cast.hpp>

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

#endif // DEFINES_H
