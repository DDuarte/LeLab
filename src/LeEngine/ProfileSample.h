#ifndef PROFILESAMPLE_H
#define PROFILESAMPLE_H

#include <ctime>
#include <string>
#include "Defines.h"

class IProfilerOutputHandler;

#define MAX_PROFILER_SAMPLES 50

#ifdef DEBUG
#define PROFILE(name) ProfileSample _profile_sample(name);
#else
#define PROFILE(name)
#endif

class ProfileSample
{
public:
    ProfileSample(std::string name);
    ~ProfileSample();

    static void Output();

    static void ResetSample(std::string name);
    static void ResetAll();

    static IProfilerOutputHandler* OutputHandler;

    static bool ProfilerIsRunning;

protected:
    int _sampleIndex;
    int _parentIndex;

    float GetTime() { return (float)clock()/(float)CLOCKS_PER_SEC; }

    static struct ProfileSampleS
    {
        ProfileSampleS()
        {
            IsValid = false;
            DataCount = 0;
            AveragePc = MinPc = MaxPc = -1;
        }

        bool IsValid;
        bool IsOpen;
        uint32 CallCount;
        std::string Name;

        float StartTime;
        float TotalTime;
        float ChildTime;

        int ParentCount;

        float AveragePc;
        float MinPc;
        float MaxPc;
        uint32 DataCount;
    } _samples[MAX_PROFILER_SAMPLES];

    static int _lastOpenedSample;
    static int _openSampleCount;
    static float _rootBegin, _rootEnd;
};

#endif // PROFILESAMPLE_H
