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

//! Simple file logging
class Log
{
protected:
    //! Singleton, protected constructor
    Log() {};

    //! Application log stream/file
    std::ofstream _appLog;
    //! Client log stream/file
    std::ofstream _clientLog;
    //! Server log stream/file
    std::ofstream _serverLog;

private:
    //! Writes the final buffer to the streams. Use Write and WriteP
    void WriteToStream(int target, const char* buffer);
    //! Returns a formatted string of current time
    std::string GetTime() const;

public:
    //! Singleton
    static Log& Get() { static Log Log; return Log; }

    //! Initializes streams
    bool Init();

    //! Parametrized write. Use any LOG_ enum values in target or a combination of them
    void WriteP(int target, const char* msg, ...);
    //! Simple write.  Use LOG_ enum values in target or a combination of them
    void Write(int target, const char* msg) { WriteToStream(target, msg); }
};

#endif // LOG_H
