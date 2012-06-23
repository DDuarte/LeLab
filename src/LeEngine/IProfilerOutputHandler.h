#ifndef IPROFILEROUTPUTHANDLER_H
#define IPROFILEROUTPUTHANDLER_H

#include <string>

class IProfilerOutputHandler
{
public:
    virtual void BeginOutput() = 0;
    virtual void EndOutput() = 0;
    virtual void Sample(float min, float avg, float max,
        int callCount, std::string name, int parecentCount) = 0;
};

#endif // IPROFILEROUTPUTHANDLER_H
