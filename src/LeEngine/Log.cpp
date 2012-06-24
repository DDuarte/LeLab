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

    Write(target, buffer);
}

void Log::WriteToStream(int target, const char* buffer, bool withNewLine)
{
    std::string time = GetTime();

    char newLine = withNewLine ? '\n' : '\0';

    if (target & LOG_APP)
    {
        if (_timeEnabled)
            _appLog << time;
        _appLog << buffer << newLine;

        if (_consoleEnabled)
        {
            if (_timeEnabled)
                std::cout << time;
            std::cout << " APP: " << buffer << newLine;
        }

#ifdef DEBUG
        _appLog.flush();
#endif
    }

    if (target & LOG_CLIENT)
    {
        if (_timeEnabled)
            _clientLog << time;
        _clientLog << buffer << newLine;

        if (_consoleEnabled)
        {
            if (_timeEnabled)
                std::cout << time;
            std::cout << "CLNT: " << buffer << newLine;
        }
#ifdef DEBUG
        _clientLog.flush();
#endif
    }

    if (target & LOG_SERVER)
    {
        if (_timeEnabled)
            _serverLog << time;
        _serverLog << buffer << newLine;

        if (_consoleEnabled)
        {
            if (_timeEnabled)
                std::cout << time;
            std::cout << "SRVR: " << buffer << newLine;
        }
#ifdef DEBUG
        _serverLog.flush();
#endif
    }

    if (target & LOG_USER)
    {
#ifdef WIN32
        MessageBoxA(NULL, buffer, "Message", MB_OK);
#else
#error User-level logging is not yet implemented for this platform.
#endif
    }
}

void Log::WriteToStreamSimple( int target, const char* buffer )
{
    if (target & LOG_APP)
    {
        _appLog << buffer;

#ifdef DEBUG
        _appLog.flush();
#endif
    }

    if (target & LOG_CLIENT)
    {
        _clientLog << buffer;
#ifdef DEBUG
        _clientLog.flush();
#endif
    }

    if (target & LOG_SERVER)
    {
        _serverLog << buffer;
#ifdef DEBUG
        _serverLog.flush();
#endif
    }
}

std::string Log::GetTime()
{
    boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
    std::string time = boost::posix_time::to_iso_extended_string(now);

    time.insert(0, 1, '[');
    time.append("] ");

    return time;
}

Log& Log::operator <<(const char* buffer)
{
    WriteToStreamSimple(_lastFilter, buffer);
    return *this;
}

Log& Log::operator <<(const std::string& str)
{
    WriteToStreamSimple(_lastFilter, str.c_str());
    return *this;
}

Log& Log::operator <<(const LogFilter filter)
{
    if (filter == NL)
    {
        WriteNewLine(_lastFilter);
        _lastFilter = INVALID;
    }
    else if (_lastFilter == INVALID)
    {
        Write(filter, "", false);
        _lastFilter = filter;
    }
    else
        _lastFilter = filter;

    return *this;
}
