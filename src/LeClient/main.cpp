#include "Application.h"

#include "SoundTask.h"

int main(int argc, char* argv[])
{
    new Application();
    Application::Get().Run(argc, argv);
    delete Application::GetPtr();

    return 0;
}
