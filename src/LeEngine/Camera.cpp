#include "Camera.h"
#include "InputTask.h"
#include "DMath.h"
#include <GL/glfw.h>


bool Camera::Start()
{
    _pos.Set(0,0,0);
    _rot.Set(0,0);
    _view.Set(0,0,0);
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
        _pos[0] += float(Mathf::Sin(rotrad[1])) * 0.01f;
        _pos[1] -= float(Mathf::Sin(rotrad[0])) * 0.01f;
        _pos[2] -= float(Mathf::Cos(rotrad[1])) * 0.01f;
    }
    if (InputTask::KeyDown('W'))
    {
        Vector<2> rotrad;
        rotrad = (_rot / 180.0f * Mathf::PI);
        _pos[0] -= float(Mathf::Sin(rotrad[1])) * 0.01f;
        _pos[1] += float(Mathf::Sin(rotrad[0])) * 0.01f;
        _pos[2] += float(Mathf::Cos(rotrad[1])) * 0.01f;
    }
    if (InputTask::KeyDown('D'))
    { 
        float yRotRad = (_rot[1] / 180.0f * Mathf::PI);
        _pos[0] += float(Mathf::Cos(yRotRad)) * 0.01f;
        _pos[2] += float(Mathf::Sin(yRotRad)) * 0.01f;

    }
    if (InputTask::KeyDown('A'))
    {
        float yRotRad = (_rot[1] / 180.0f * Mathf::PI);
        _pos[0] -= float(Mathf::Cos(yRotRad)) * 0.01f;
        _pos[2] -= float(Mathf::Sin(yRotRad)) * 0.01f;
    }

    static int oldMousePosX = InputTask::MouseX, oldMousePosY = InputTask::MouseY;
    
    if (oldMousePosX != InputTask::MouseX || oldMousePosY != InputTask::MouseY)
    {
        _rot[0] += (float)InputTask::dY * 0.1f;
        _rot[1] += (float)InputTask::dX * 0.1f;
        oldMousePosX = InputTask::MouseX;
        oldMousePosY = InputTask::MouseY;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //gluLookAt( _pos[0], _pos[1], _pos[2], _view[0], _view[1], _view[2], 0, 1, 0 );
    glRotatef(_rot[0], 1.0f, 0.0f, 0.0f);
    glRotatef(_rot[1], 0.0f, 1.0f, 0.0f);
    glTranslated(_pos[0], _pos[1], _pos[2]);
    //glfwSetMousePos(VideoUpdate::SourceWidth / 2, VideoUpdate::SourceHeight / 2);
}

void Camera::Stop()
{

}
