#include "Application.h"
#include <Matrix.h>

int main(int argc, char* argv[])
{
    mat4 t = translate(1.0f, 1.0f, 1.0f);
    mat4 s = scale(2.0f, 2.0f, 2.0f);
    mat4 rx = rotate(45.0f, vec3(1,0,0));
    mat4 ry = rotate(45.0f, vec3(0,1,0));
    mat4 rz = rotate(45.0f, vec3(0,0,1));
    mat4 r = rotate(45.0f, vec3(1,1,1));

    new Application();
    Application::Get().Run(argc, argv);
    delete Application::GetPtr();

    return 0;
}
