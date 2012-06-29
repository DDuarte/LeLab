#include "Application.h"
#include "Log.h"
#include "SettingsManager.h"
#include "Kernel.h"
#include "GlobalTimer.h"
#include "ITask.h"
#include "InputTask.h"
#include "SoundTask.h"
#include "VideoUpdate.h"
#include "OpenGLTest.h"
#include "Camera.h"

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

    shared_ptr<Camera> camera(new Camera);
    camera->Priority = 40;
    Kernel::Get().AddTask(camera);

    // Game specific tasks
    
    shared_ptr<OpenGLTest> test(new OpenGLTest);
    test->Priority = 100;
    Kernel::Get().AddTask(test);

    //**********************
    Kernel::Get().Execute();
    //**********************

    delete Kernel::GetPtr();
    delete SettingsManager::GetPtr();
    delete Log::GetPtr();
}