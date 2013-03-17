#ifndef CAMERA_H
#define CAMERA_H

#include "ITask.h"
#include "Shapes.h"
#include "Vector.h"

class Camera : public ITask
{
public:
    Vector3f _pos;
    Vector3f _view;

    Vector2f _rot;
public:
    Camera() : ITask("Camera") {}
    virtual ~Camera() {}

    bool Start();
    void Update();
    void Stop();
    
};

#endif // CAMERA_H