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
    LOG_ALL = LOG_ALL_INTERNAL | LOG_USER,

    //! Writes newLine and resets log used by streams
    NL = 0,
    INVALID = -1,
};

//! Simple file logging
/*!
    Example usages:
        - LeLog << LOG_INTERNAL << "This is a test: " << variable << "." << NL;
        - LeLog.WriteP(LOG_INTERNAL, "This is a test: %s", variable);
        - LeLog.Write(LOG_INTERNAL, boost::format("This is a test: %1%") % variable);
*/
class Log : public Singleton<Log>
{
public:
    //! Constructor
    Log() : _consoleEnabled(false), _timeEnabled(true), _lastFilter(INVALID) { /*Init();*/ };

    //! Initializes streams
    bool Init();

    //! Parametrized write. Use any LOG_ enum values in target or a combination of them
    void WriteP(int target, const char* msg, ...);
    //! Simple write.  Use LOG_ enum values in target or a combination of them
    void Write(int target, const char* msg, bool withNewLine = true) { WriteToStream(target, msg, withNewLine); }

    //! Enabled/disables writing logs to console
    void EnableConsole(bool write = true) { _consoleEnabled = write; }

    //! Enables/disables writing date time in logs
    void EnabledTime(bool write = true) { _timeEnabled = write; }

    //! Stream operator for logging
    Log& operator <<(const char* buffer);
    //! Stream operator for logging
    Log& operator <<(const std::string& str);
    //! Stream operator that sets the filter of the next streams
    Log& operator <<(const LogFilter filter);

private:
    //! Writes the final buffer to the streams. Use Write and WriteP
    void WriteToStream(int target, const char* buffer, bool withNewLine);
    //! Write new line to streams
    void WriteNewLine(int target) { WriteToStreamSimple(target, "\n"); }
    //! Writes exactly what is in the given buffer to streams
    void WriteToStreamSimple(int target, const char* buffer);

    //! Returns a formatted string of current time
    static std::string GetTime();

    //! Application log stream/file
    std::ofstream _appLog;
    //! Client log stream/file
    std::ofstream _clientLog;
    //! Server log stream/file
    std::ofstream _serverLog;

    //! Defines if logs should be written to console (cout)
    bool _consoleEnabled;

    //! Defines if logs should have a date time
    bool _timeEnabled;

    //! Used by the stream operators
    LogFilter _lastFilter;
};

#define LeLog Log::Get()

#endif // LOG_H
