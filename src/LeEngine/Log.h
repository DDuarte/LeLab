#ifndef LOG_H
#define LOG_H

#include <fstream>
#include <string>
#include <boost/noncopyable.hpp>
#include "Singleton.h"

//! Simple file logging
/*!
    Example usages:
        - LeLog.WriteP("This is a test: %s", variable);
        - LeLog.Write(boost::format("This is a test: %1%") % variable);
*/
class Log : public Singleton<Log>, public boost::noncopyable
{
public:
    //! Constructor
    Log(const std::string& filename) : _consoleEnabled(true), _timeEnabled(true), _filename(filename) { /*Init();*/ };

    //! Initializes streams
    bool Init();

    //! Parametrized write
    void WriteP(const char* msg, ...);
    //! Simple write
    void Write(const char* msg);

    //! Enabled/disables writing logs to console
    void EnableConsole(bool write = true) { _consoleEnabled = write; }

    //! Enables/disables writing date time in logs
    void EnableTime(bool write = true) { _timeEnabled = write; }

private:
    //! Writes the final buffer to the streams. Use Write and WriteP
    void WriteToStream(const char* buffer);

    //! Returns a formatted string of current time
    static std::string GetTime();

    //! Log file
    std::string _filename;

    //! Log stream
    std::ofstream _stream;

    //! Defines if logs should be written to console (cout)
    bool _consoleEnabled;

    //! Defines if logs should have a date time
    bool _timeEnabled;
};

#define LeLog Log::Get()

#endif // LOG_H
