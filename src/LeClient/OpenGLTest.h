#ifndef OPENGLTEST_H
#define OPENGLTEST_H

#include <LeEngine/ITask.h>
#include <LeEngine/Shapes.h>
#include <LeEngine/Lighting.h>

#include <GL/glew.h>
#include <GL/glfw.h>

class OpenGLTest : public ITask
{
public:
    OpenGLTest() : ITask("OpenGLTest")
    {
        z = -5.0f;
        filter = 0;
        xrot = yrot = 0.0f;
        xspeed = yspeed = 0.0012f;
    }
    bool Start();
    void Update();
    void Render() const;
    void Stop();
    
    //! Called when the window is resized
    static void GLFWCALL WindowResizeHandler(int width, int height);

public:

    float xrot, yrot,
        xspeed, yspeed,
        z /*= -5.0f*/;

    bool light,
        blend,
        lp,
        fp,
        bp,
        f1p;

    Light* light1;

    unsigned int filter/* = 0*/,
        texture[3];

    int LoadGLTexture();
};

#endif // OPENGLTEST_H
