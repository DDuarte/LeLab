#include "ProfileSample.h"
#include "IProfilerOutputHandler.h"
#include <string>
#include <cassert>

int ProfileSample::_lastOpenedSample = -1;
int ProfileSample::_openSampleCount = 0;
ProfileSample::ProfileSampleS ProfileSample::_samples[MAX_PROFILER_SAMPLES];
IProfilerOutputHandler *ProfileSample::OutputHandler = NULL;
float ProfileSample::_rootBegin = 0.0f;
float ProfileSample::_rootEnd = 0.0f;
bool ProfileSample::ProfilerIsRunning = true;

ProfileSample::ProfileSample(std::string name)
{
    int i = 0;
    int storeIndex = -1;
    for (i = 0; i < MAX_PROFILER_SAMPLES; ++i)
    {
        if (!_samples[i].IsValid)
        {
            if (storeIndex < 0)
                storeIndex = 1;
        }
        else
        {
            if (_samples[i].Name == name)
            {
                assert(!_samples[i].IsOpen &&
                    "Tried to profile a sample which was already being profiled.");
                _sampleIndex = i;
                _parentIndex = _lastOpenedSample;
                _samples[i].ParentCount = _openSampleCount;
                ++_openSampleCount;
                _samples[i].IsOpen = true;
                ++_samples[i].CallCount;
                _samples[i].StartTime = GetTime();
                if (_parentIndex < 0)
                    _rootBegin = _samples[i].StartTime;
                return;
            }
        }
    }

    assert(storeIndex >= 0 && "Profiler has run out of sample slots!");
    _samples[storeIndex].IsValid = true;
    _samples[storeIndex].Name = name;
    _sampleIndex = storeIndex;
    _parentIndex = _lastOpenedSample;
    _lastOpenedSample = storeIndex;
    _samples[i].ParentCount = _openSampleCount;
    ++_openSampleCount;
    _samples[storeIndex].IsOpen = true;
    _samples[storeIndex].CallCount = 1;

    _samples[storeIndex].TotalTime = 0.0f;
    _samples[storeIndex].ChildTime = 0.0f;
    _samples[storeIndex].StartTime = GetTime();

    if (_parentIndex < 0)
        _rootBegin = _samples[storeIndex].StartTime;
}

ProfileSample::~ProfileSample()
{
    float endTime = GetTime();

    _samples[_sampleIndex].IsOpen = false;
    float timeTaken = endTime - _samples[_sampleIndex].StartTime;

    if (_parentIndex > 0)
    {
        _samples[_sampleIndex].TotalTime += timeTaken;
        _lastOpenedSample = _parentIndex;
        --_openSampleCount;
    }
}

void ProfileSample::Output()
{
    assert(OutputHandler && "Profiler has no output handler set.");

    OutputHandler->BeginOutput();

    for (int i = 0; i < MAX_PROFILER_SAMPLES; ++i)
    {
        if (!_samples[i].IsValid)
            continue;

        float sampleTime, percentage;

        sampleTime = _samples[i].TotalTime - _samples[i].ChildTime;
        percentage = (sampleTime / (_rootEnd - _rootBegin)) * 100.0f;

        float totalPc;
        totalPc = _samples[i].AveragePc * _samples[i].DataCount;
        totalPc += percentage;
        ++_samples[i].DataCount;
        _samples[i].AveragePc = totalPc / _samples[i].DataCount;
        if (_samples[i].MinPc == -1 || percentage < _samples[i].MinPc)
            _samples[i].MinPc = percentage;
        if (_samples[i].MaxPc == -1 || percentage > _samples[i].MaxPc)
            _samples[i].MaxPc = percentage;

        OutputHandler->Sample(_samples[i].MinPc,
            _samples[i].AveragePc,
            _samples[i].MaxPc,
            _samples[i].CallCount,
            _samples[i].Name,
            _samples[i].ParentCount);

        _samples[i].CallCount = 0;
        _samples[i].TotalTime = 0;
        _samples[i].ChildTime = 0;
    }

    OutputHandler->EndOutput();

}

void ProfileSample::ResetSample( std::string name )
{
    for (int i = 0; i < MAX_PROFILER_SAMPLES; ++i)
    {
        if (_samples[i].IsValid && _samples[i].Name == name)
        {
            _samples[i].MaxPc = -1;
            _samples[i].MinPc = -1;
            _samples[i].DataCount = 0;
            return;
        }
    }
}

void ProfileSample::ResetAll()
{
    for(int i = 0;i < MAX_PROFILER_SAMPLES; ++i)
    {
        if(_samples[i].IsValid)
        {
            _samples[i].MaxPc = -1;
            _samples[i].MinPc = -1;
            _samples[i].DataCount=0;
        }
    }
}
