#include "ProfileLogHandler.h"
#include "Log.h"
#include <boost/format.hpp>
#include <iomanip>

void ProfileLogHandler::BeginOutput()
{
    Log::Get().Write(LOG_APP, "  Min :   Avg :   Max :   # : Profile Name");
    Log::Get().Write(LOG_APP, "--------------------------------------------");
}

void ProfileLogHandler::EndOutput()
{
    Log::Get().Write(LOG_APP,"\n");
}

void ProfileLogHandler::Sample(float min, float avg, float max, int callCount, std::string name, int parentCount)
{
    using boost::io::group;

    boost::format fmter("%1% : %2% : %3% : %4% : %5%%6%");
    fmter % group(std::setw(5), std::setprecision(1), std::fixed, min)
          % group(std::setw(5), std::setprecision(1), std::fixed, avg)
          % group(std::setw(5), std::setprecision(1), std::fixed, max)
          % group(std::setw(3), callCount)
          % group(std::setw(parentCount), "")
          % name;

    Log::Get().Write(LOG_APP, fmter.str().c_str());
}
