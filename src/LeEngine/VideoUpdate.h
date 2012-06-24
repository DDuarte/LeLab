#ifndef VIDEOUPDATE_H
#define VIDEOUPDATE_H

#include "ITask.h"
#include "MMPointer.h"
#include "Dator.h"

class VideoUpdate : public ITask
{
public:
    VideoUpdate() {}
    virtual ~VideoUpdate() {}
    AUTO_SIZE;

    static int SourceWidth, SourceHeight, SourceBPP;
    static bool SourceFullscreen;
    static MMPointer< Dator<int> > ScreenWidth, ScreenHeight, ScreenBPP;
    static MMPointer< Dator<bool> > Fullscreen;

    bool Start();
    void Update();
    void Stop();
};

#endif // VIDEOUPDATE_H
