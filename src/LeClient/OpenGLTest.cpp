#include "OpenGLTest.h"
#include <GL/glew.h>
#include <GL/glfw.h>
#include "InputTask.h"
#include "Kernel.h"
#include "SOIL.h"
#include "Shapes.h"

int texture[1];
int LoadGLTexture()
{
    texture[0] = SOIL_load_OGL_texture("star.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    if (texture[0] == 0)
        return false;

    //glBindTexture(GL_TEXTURE_2D, texture[0]);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return true;
}

bool OpenGLTest::Start()
{
    glfwSetWindowSizeCallback(WindowResizeHandler);

    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);

    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    //if (!LoadGLTexture())
    //    return false;

    //glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    return true;
}

void OpenGLTest::Update()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // ...
}

void OpenGLTest::Stop()
{

}

void GLFWCALL OpenGLTest::WindowResizeHandler( int width, int height )
{
    if (height == 0)
        height = 1;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f, float(width)/float(height), 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

