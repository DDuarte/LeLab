#ifndef LOG_H
#define LOG_H

#include <fstream>
#include <string>

enum LogFilter // flags
{
    LOG_APP = 1,
    LOG_CLIENT = 2,
    LOG_SERVER = 4,
    LOG_USER = 8, // in-game console?

    LOG_ALL_INTERNAL = LOG_APP | LOG_CLIENT | LOG_SERVER,
    LOG_ALL = LOG_ALL_INTERNAL | LOG_USER
};

class Log
{
protected:
    Log() {};

    std::ofstream _appLog;
    std::ofstream _clientLog;
    std::ofstream _serverLog;

private:
    void WriteToStream(int target, const char* buffer);
    std::string GetTime() const;

public:
    static Log& Get() { static Log Log; return Log; }

    bool Init();

    void WriteP(int target, const char* msg, ...);
    void Write(int target, const char* msg) { WriteToStream(target, msg); }


};

#endif // LOG_H
