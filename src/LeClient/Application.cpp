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

void OnConfigLoad()
{
    LeLog.EnableConsole(GetConfig("logging.write_to_console", bool));
    LeLog.EnableTime(GetConfig("logging.with_timestamp", bool));
    // TODO: Change used .log files
    // LeLog.SetLogFile(GetConfig<std::string>("logging.file));
}

void Application::Run(int argc, char* argv[])
{
    new Log;
    if (!LeLog.Init())
        return;

    const std::string logFile = "client.conf";
    SettingsManager* settings = new SettingsManager(logFile, OnConfigLoad);
    settings->AddSetting("screen.X", 800);
    settings->AddSetting("screen.Y", 600);
    settings->AddSetting("screen.BPP", 24);
    settings->AddSetting("screen.fullscreen", false);
    settings->AddSetting("logging.file", "client.log");
    settings->AddSetting("logging.write_to_console", true);
    settings->AddSetting("logging.with_timestamp", true);
    settings->LoadConfig();

    new Kernel();

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

    SettingsManager::Get().SaveConfig();

    delete Kernel::GetPtr();
    delete SettingsManager::GetPtr();
    delete Log::GetPtr();
}