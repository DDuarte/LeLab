#ifndef PROFILELOGHANDLER_H
#define PROFILELOGHANDLER_H

#include "IProfilerOutputHandler.h"

class ProfileLogHandler : public IProfilerOutputHandler
{
public:
    void BeginOutput();
    void EndOutput();
    void Sample(float min, float avg, float max,
        int callCount, std::string name, int parecentCount);
};

#endif // PROFILELOGHANDLER_H
