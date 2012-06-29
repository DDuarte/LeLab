#ifndef OPENGLTEST_H
#define OPENGLTEST_H

#include "ITask.h"
#include "Shapes.h"

#include <GL/glew.h>
#include <GL/glfw.h>

class OpenGLTest : public ITask, public IRenderable
{
public:
    OpenGLTest()
    {
        z = -5.0f;
        LightAmbient[0] = 0.5f;
        LightAmbient[1] = 0.5f;
        LightAmbient[2] = 0.5f;
        LightAmbient[3] = 1.0f;
        LightDiffuse[0] = 1.0f;
        LightDiffuse[1] = 1.0f;
        LightDiffuse[2] = 1.0f;
        LightDiffuse[3] = 1.0f;
        LightPosition[0] = 0.0f;
        LightPosition[1] = 0.0f;
        LightPosition[2] = 2.0f;
        LightPosition[3] = 1.0f;
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
        bp;

    float LightAmbient[4]/* = { 0.5f, 0.5f, 0.5f, 1.0f }*/,
        LightDiffuse[4]/* = { 1.0f, 1.0f, 1.0f, 1.0f }*/,
        LightPosition[4]/* = { 0.0f, 0.0f, 2.0f, 1.0f }*/;

    unsigned int filter/* = 0*/,
        texture[3];

    int LoadGLTexture();
};

#endif // OPENGLTEST_H
