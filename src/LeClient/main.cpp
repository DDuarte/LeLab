#include "Application.h"
#include "MMObject.h"

int main(int argc, char* argv[])
{
    new Application();
    Application::Get().Run(argc, argv);
    delete Application::GetPtr();

    MMObject::CollectRemainingObjects(true);

    return 0;
}
