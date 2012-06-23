#include "Log.h"
#include "Application.h"
#include "ProfileLogHandler.h"

int main(int argc, char **argv) 
{
    Log* log = new Log();
    log->EnableConsole();
    log->EnabledTime();

    Log::Get().Write(LOG_ALL_INTERNAL, "Initializing...");

    glutInit(&argc, argv);
    Application::Get();
    // Do super complicated stuff here...

    Log::Get().Write(LOG_ALL_INTERNAL, "Closing...");

    delete log->GetPtr();

    std::cout << "Press any key to exit." << std::endl;
    std::cin.get();
    return 0;
}
