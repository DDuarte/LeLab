#include "Application.h"
#include "Log.h"
#include "SettingsManager.h"
#include "Kernel.h"
#include "ProfileLogHandler.h"
#include "ProfileSample.h"

#include <string>

void Application::Run(int argc, char* argv[])
{
    new Log;
    if (!LeLog.Init())
        return;

    LeLog.EnableConsole();

    new SettingsManager();
    new Kernel();

    SettingsManager::Get().ParseFile("settings.conf");
    if (argc > 1)
        for (int i = 0; i < argc; ++i)
            SettingsManager::Get().ParseSetting(argv[i]);

    ProfileLogHandler profileLogHandler;
    ProfileSample::OutputHandler = &profileLogHandler;

    //**********************
    Kernel::Get().Execute();
    //**********************

    delete Kernel::GetPtr();
    delete SettingsManager::GetPtr();
    delete Log::GetPtr();
}