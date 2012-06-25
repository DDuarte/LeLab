#include "SoundTask.h"
#include "Defines.h"
#include <fmod.h>
#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

bool SoundTask::Start()
{
    if (!FSOUND_Init(44100, 32, 0))
        return false;
    return true;
}

void SoundTask::OnSuspend()
{
    int channelCount = FSOUND_GetMaxChannels();
    _isPaused = new bool[channelCount];

    for (int i = 0; i < channelCount; ++i)
        _isPaused[i] = FSOUND_IsPlaying(i);

    FSOUND_SetPaused(FSOUND_ALL, 1);
}

void SoundTask::OnResume()
{
    if (_isPaused)
    {
        int channelCount = FSOUND_GetMaxChannels();
        for (int i = 0; i < channelCount; ++i)
            if (_isPaused[i])
                FSOUND_SetPaused(i, 0);

        delete[] _isPaused;
    }
}

void SoundTask::Stop()
{
    FSOUND_Close();
}
