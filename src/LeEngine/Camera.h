#ifndef CAMERA_H
#define CAMERA_H

#include "ITask.h"
#include "Shapes.h"
#include "Vector.h"

class Camera : public ITask
{
public:
    Vector<3> _pos;
    Vector<3> _view;

    Vector<2> _rot;
public:
    Camera() {}
    virtual ~Camera() {}

    bool Start();
    void Update();
    void Stop();
    
};

#endif // CAMERA_H