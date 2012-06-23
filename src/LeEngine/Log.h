#ifndef LOG_H
#define LOG_H

#include <fstream>
#include <string>
#include "Singleton.h"

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
class Log : public Singleton<Log>
{
public:
    //! Constructor
    Log() : _consoleEnabled(false), _timeEnabled(true) { Init(); };

    //! Parametrized write. Use any LOG_ enum values in target or a combination of them
    void WriteP(int target, const char* msg, ...);
    //! Simple write.  Use LOG_ enum values in target or a combination of them
    void Write(int target, const char* msg) { WriteToStream(target, msg); }

    //! Enabled/disables writing logs to console
    void EnableConsole(bool write = true) { _consoleEnabled = write; }

    //! Enables/disables writing date time in logs
    void EnabledTime(bool write = true) { _timeEnabled = write; }

private:
    //! Writes the final buffer to the streams. Use Write and WriteP
    void WriteToStream(int target, const char* buffer);
    //! Returns a formatted string of current time
    std::string GetTime() const;

    //! Application log stream/file
    std::ofstream _appLog;
    //! Client log stream/file
    std::ofstream _clientLog;
    //! Server log stream/file
    std::ofstream _serverLog;

    //! Initializes streams
    bool Init();

    //! Defines if logs should be written to console (cout)
    bool _consoleEnabled;

    //! Defines if logs should have a date time
    bool _timeEnabled;
};

#endif // LOG_H
