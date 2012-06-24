#include "Application.h"

#include "Defines.h"

#include <iostream>
#include <algorithm>
#include <vector>

Application::Application()
{
    glutInitContextVersion(3, 2);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
    glutInitContextProfile(GLUT_CORE_PROFILE);

    glutSetOption(
        GLUT_ACTION_ON_WINDOW_CLOSE,
        GLUT_ACTION_GLUTMAINLOOP_RETURNS
        );

    Initialize();

    glutDisplayFunc(Application::Get().Render);
    glutReshapeFunc(Application::Get().Resize);
    glutKeyboardFunc(Application::Get().KeyboardCB);
    glutMouseFunc(Application::Get().MouseCB);

    glutMainLoop();
}

void Application::Initialize()
{
    _wManager.AddWindow(new Window("LeWindow"));

    _meshes.push_back(Mesh().LoadMesh("monk.3ds"));
}

void Application::Render()
{
    Application& me = Application::Get();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (std::vector<Mesh>::iterator itr = me._meshes.begin(); itr != me._meshes.end(); itr++)
        itr->Render();

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

void Application::MouseCB( int32 button, int32 state, int32 x, int32 y )
{

}
