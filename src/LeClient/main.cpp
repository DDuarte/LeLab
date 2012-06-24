#include "Application.h"
#include "MMObject.h"

#include "SoundTask.h"

int main(int argc, char* argv[])
{
    new Application();
    Application::Get().Run(argc, argv);
    delete Application::GetPtr();

    MMObject::CollectRemainingObjects(true);

    SoundTask a;
    a.AddRef();
    //a->Update();
    //a->Stop();

    return 0;
}
