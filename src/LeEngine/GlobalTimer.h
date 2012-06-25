#ifndef GLOBALTIMER_H
#define GLOBALTIMER_H

#include "ITask.h"
#include "Defines.h"

class GlobalTimer : public ITask
{
public:
    //! Difference between last and current frame (s)
    static float dT;
    //! Time of the previous frame (ms)
    static uint32 LastFrameIndex;
    //! Time of the current frame (ms)
    static uint32 ThisFrameIndex;

    bool Start();
    void Update();
    void Stop() {}
};

#endif // GLOBALTIMER_H
