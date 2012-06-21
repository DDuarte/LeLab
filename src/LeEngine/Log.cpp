#include "Log.h"
#include <cstdio>
#include <cstdarg>
#include "boost/date_time/posix_time/posix_time.hpp"

#ifdef WIN32
#include <windows.h>
#endif

bool Log::Init()
{
    _appLog.open("applog.log");
    _clientLog.open("clntlog.log");
    _serverLog.open("srvrlog.log");

    if (!_appLog.is_open() || !_clientLog.is_open() || !_serverLog.is_open())
        return false;

    return true;
}

void Log::WriteP(int target, const char* msg, ...)
{
    va_list args;
    va_start(args, msg);

    char buffer[1024];
    vsprintf(buffer, msg, args);

    WriteToStream(target, buffer);
}

void Log::WriteToStream(int target, const char* buffer)
{
    std::string msg = GetTime();
    msg.append(buffer);

    if (target & LOG_APP)
    {
        _appLog << msg << '\n';
#ifdef DEBUG
        _appLog.flush();
#endif
    }

    if (target & LOG_CLIENT)
    {
        _clientLog << msg << '\n';
#ifdef DEBUG
        _clientLog.flush();
#endif
    }

    if (target & LOG_SERVER)
    {
        _serverLog << msg << '\n';
#ifdef DEBUG
        _serverLog.flush();
#endif
    }

    if (target & LOG_USER)
    {
#ifdef WIN32
        MessageBoxA(NULL, msg.c_str(), "Message", MB_OK);
#else
#error User-level logging is not yet implemented for this platform.
#endif
    }
}

std::string Log::GetTime() const
{
    boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
    std::string time = boost::posix_time::to_iso_extended_string(now);

    time.insert(0, 1, '[');
    time.append("] ");

    return time;
}

