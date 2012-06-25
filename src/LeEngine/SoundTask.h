#ifndef SOUNDTASK_H
#define SOUNDTASK_H

#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

#include "ITask.h"

class SoundTask : public ITask
{
protected:
    bool* _isPaused; // I couldn't use a scoped_array or shared_array
public:
    SoundTask() {}

    bool Start();
    void OnSuspend();
    void Update() {}
    void OnResume();
    void Stop();
};

#endif // SOUNDTASK_H
