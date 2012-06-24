#include "Log.h"
#include "Application.h"
#include "ProfileLogHandler.h"

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <IL/il.h>

int main(int argc, char **argv) 
{
    Log* log = new Log();
    log->EnableConsole();
    log->EnabledTime();

    LeLog.Write(LOG_ALL_INTERNAL, "Initializing...");

    LeLog << LOG_APP << "test app" << LOG_SERVER << "lol server";

   
    glutInit(&argc, argv);
    ilInit();

    Application::Get();

    Log::Get().Write(LOG_ALL_INTERNAL, "Closing...");
    delete log->GetPtr();

    std::cout << "Press any key to exit." << std::endl;
    std::cin.get();
    return 0;
}
