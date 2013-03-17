#ifndef VIDEOUPDATE_H
#define VIDEOUPDATE_H

#include "ITask.h"

class Window;

class VideoUpdate : public ITask
{
private:
    static Window* _window;

public:
    VideoUpdate() : ITask("VideoUpdate") {}
    virtual ~VideoUpdate() {}

    static Window* GetWindow() { return _window;}

    bool Start();
    void Update();
    void Stop();
};

#endif // VIDEOUPDATE_H
