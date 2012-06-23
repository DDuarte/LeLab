#include "Application.h"

#include <iostream>

Application::Application()
{
    glutInitContextVersion(4, 0);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
    glutInitContextProfile(GLUT_CORE_PROFILE);

    glutSetOption(
        GLUT_ACTION_ON_WINDOW_CLOSE,
        GLUT_ACTION_GLUTMAINLOOP_RETURNS
        );

    Initialize();

    glutDisplayFunc(Application::Get().Render);
    glutReshapeFunc(Application::Get().Resize);

    glutMainLoop();
}

void Application::Initialize()
{
    _wManager.AddWindow(new Window("LeWindow"));


}

void Application::Render()
{
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     glutSwapBuffers();
     glutPostRedisplay();
}

void Application::Resize(int32 width, int32 height)
{
    Application::Get()._wManager.GetActiveWindow()->SetSize(Size2(width,height));
    glViewport(0, 0, width, height);
    std::clog << "Resized: " << width << "x" << height << std::endl;
}

void Application::KeyboardCB( uint8 key, int x, int y )
{

}
