#ifndef VIDEOUPDATE_H
#define VIDEOUPDATE_H

#include "ITask.h"
#include "Dator.h"
#include "Window.h"

#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

class VideoUpdate : public ITask
{
private:
    static Window* _window;

public:
    VideoUpdate() {}
    virtual ~VideoUpdate() {}

    static int SourceWidth, SourceHeight, SourceBPP;
    static bool SourceFullscreen;
    static shared_ptr< Dator<int> > ScreenWidth, ScreenHeight, ScreenBPP;
    static shared_ptr< Dator<bool> > Fullscreen;

    static Window* GetWindow() { return _window;}

    bool Start();
    void Update();
    void Stop();
};

#endif // VIDEOUPDATE_H
