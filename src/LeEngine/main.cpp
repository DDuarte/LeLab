#include "Log.h"
#include "Application.h"
int main(int argc, char **argv) 
{
    Log::Get().Init();

    Log::Get().Write(LOG_ALL_INTERNAL, "Initializing...");
    
    glutInit(&argc, argv);
    Application::Get();
    // Do super complicated stuff here...

    Log::Get().Write(LOG_ALL_INTERNAL, "Closing...");
    return 0;
}
