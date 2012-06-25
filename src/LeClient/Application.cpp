#include "Application.h"
#include "Log.h"
#include "SettingsManager.h"
#include "Kernel.h"
#include "ProfileLogHandler.h"
#include "ProfileSample.h"
#include "GlobalTimer.h"
#include "ITask.h"
#include "InputTask.h"
#include "SoundTask.h"
#include "VideoUpdate.h"
#include "TestTask.h"

#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

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

    // Init tasks

    shared_ptr<GlobalTimer> globalTimer(new GlobalTimer);
    globalTimer->Priority = 10;
    Kernel::Get().AddTask(globalTimer);

    shared_ptr<VideoUpdate> videoTask(new VideoUpdate);
    videoTask->Priority = 10000;
    Kernel::Get().AddTask(videoTask);

    shared_ptr<InputTask> inputTask(new InputTask);
    inputTask->Priority = 20;
    Kernel::Get().AddTask(inputTask);

    shared_ptr<SoundTask> soundTask(new SoundTask);
    soundTask->Priority = 50;
    Kernel::Get().AddTask(soundTask);

    // Game specific tasks

    shared_ptr<TestTask> tt(new TestTask);
    tt->Priority = 100;
    Kernel::Get().AddTask(tt);

    //**********************
    Kernel::Get().Execute();
    //**********************

    delete Kernel::GetPtr();
    delete SettingsManager::GetPtr();
    delete Log::GetPtr();
}