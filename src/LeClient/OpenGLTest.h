#ifndef OPENGLTEST_H
#define OPENGLTEST_H

#include "ITask.h"
#include <GL/glew.h>
#include <GL/glfw.h>

class OpenGLTest : public ITask
{
    bool Start();
    void Update();
    void Stop();

    //! Called when the window is resized
    static void GLFWCALL WindowResizeHandler(int width, int height);
};

#endif // OPENGLTEST_H
