#include "Log.h"
#include <cstdio>
#include <cstdarg>
#include <boost/date_time/posix_time/posix_time.hpp>

bool Log::Init()
{
    _stream.open("log.log");

    return _stream.is_open();
}

void Log::WriteP(const char* msg, ...)
{
    va_list args;
    va_start(args, msg);

    char buffer[1024];
    vsprintf(buffer, msg, args);

    Write(buffer);
}

void Log::WriteToStream(const char* buffer)
{
    std::string time = GetTime();

    if (_timeEnabled)
        _stream << time;
    if (buffer)
        _stream << buffer;
    _stream << '\n';

    if (_consoleEnabled)
    {
        if (_timeEnabled)
            std::cout << time;
        std::cout << " APP: ";
        if (buffer)
            std::cout << buffer;
        std::cout << '\n';
    }

#ifdef DEBUG
        _stream.flush();
#endif
}

std::string Log::GetTime()
{
    boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
    std::string time = boost::posix_time::to_iso_extended_string(now);

    time.insert(0, 1, '[');
    time.append("] ");

    return time;
}

void Log::Write(const char* msg)
{
    WriteToStream(msg);
}
