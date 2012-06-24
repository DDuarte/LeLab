#include "SoundTask.h"
#include "MMPointer.h"
#include "MMDynamicBlob.h"
#include "Defines.h"
#include <fmod.h>

bool SoundTask::Start()
{
    if (!FSOUND_Init(44100, 32, 0))
        return false;
    return true;
}

void SoundTask::OnSuspend()
{
    int channelCount = FSOUND_GetMaxChannels();
    _isPaused = new MMDynamicBlob<bool>(channelCount);

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

        _isPaused = NULL;
    }
}

void SoundTask::Stop()
{
    FSOUND_Close();
}
