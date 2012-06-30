#include "Camera.h"
#include "InputTask.h"
#include "DMath.h"
#include <GL/glfw.h>


bool Camera::Start()
{
    _view.Set(0,0,-5);
    return true;
}

void Camera::Update()
{
    if (InputTask::KeyDown('Q'))
    {
        _rot[0] += 1;
        if (_rot[0] > 360) _rot[0] -= 360;
    }
    if (InputTask::KeyDown('Z'))
    {
        _rot[0] -= 1;
        if (_rot[0] < -360) _rot[0] += 360;
    }
    if (InputTask::KeyDown('S'))
    {
        Vector<2> rotrad;
        rotrad = (_rot / 180.0f * Mathf::PI);
        _pos[0] += float(Mathf::Sin(rotrad[1]));
        _pos[1] -= float(Mathf::Sin(rotrad[0]));
        _pos[2] -= float(Mathf::Cos(rotrad[1]));
    }
    if (InputTask::KeyDown('W'))
    {
        Vector<2> rotrad;
        rotrad = (_rot / 180.0f * Mathf::PI);
        _pos[0] -= float(Mathf::Sin(rotrad[1]));
        _pos[1] += float(Mathf::Sin(rotrad[0]));
        _pos[2] += float(Mathf::Cos(rotrad[1]));
    }
    if (InputTask::KeyDown('D'))
    { 
        float yRotRad = (_rot[1] / 180.0f * Mathf::PI);
        _pos[0] += float(Mathf::Cos(yRotRad)) * 0.2f;
        _pos[2] += float(Mathf::Sin(yRotRad)) * 0.2f;

    }
    if (InputTask::KeyDown('A'))
    {
        float yRotRad = (_rot[1] / 180.0f * Mathf::PI);
        _pos[0] -= float(Mathf::Cos(yRotRad)) * 0.2f;
        _pos[2] -= float(Mathf::Sin(yRotRad)) * 0.2f;
    }

    static int oldMousePosX = InputTask::MouseX, oldMousePosY = InputTask::MouseY;
    
    if (oldMousePosX != InputTask::MouseX || oldMousePosY != InputTask::MouseY)
    {
        _rot[0] += (float)InputTask::dY;
        _rot[1] += (float)InputTask::dX;
        oldMousePosX = InputTask::MouseX;
        oldMousePosY = InputTask::MouseY;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    //gluLookAt( _pos[0], _pos[1], _pos[2], _view[0], _view[1], _view[2], 0, 0, 1 );
    glRotatef(_rot[0], 1.0f, 0.0f, 0.0f);
    glRotatef(_rot[1], 0.0f, 1.0f, 0.0f);
    glTranslated(_pos[0], _pos[1], _pos[2]);
    //glfwSetMousePos(VideoUpdate::SourceWidth / 2, VideoUpdate::SourceHeight / 2);
}

void Camera::Stop()
{

}
