#ifndef SOUNDTASK_H
#define SOUNDTASK_H

#include "ITask.h"
#include "MMPointer.h"
#include "MMDynamicBlob.h"

class SoundTask : public ITask
{
protected:
    MMPointer< MMDynamicBlob<bool> > _isPaused;
public:
    SoundTask() {}

    bool Start();
    void OnSuspend();
    void Update() {}
    void OnResume();
    void Stop();

    AUTO_SIZE;
};

#endif // SOUNDTASK_H
