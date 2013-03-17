#ifndef SOUNDTASK_H
#define SOUNDTASK_H

#include "ITask.h"

class SoundTask : public ITask
{
protected:
    bool* _isPaused; // I couldn't use a scoped_array or shared_array
public:
    SoundTask() : ITask("SoundTask") {}

    bool Start();
    void OnSuspend();
    void Update() {}
    void OnResume();
    void Stop();
};

#endif // SOUNDTASK_H
