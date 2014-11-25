#include "Application.h"
#include <LeEngine/Log.h>
#include <LeEngine/SettingsManager.h>
#include <LeEngine/Kernel.h>
#include <LeEngine/GlobalTimer.h>
#include <LeEngine/ITask.h>
#include <LeEngine/InputTask.h>
#include <LeEngine/SoundTask.h>
#include <LeEngine/VideoUpdate.h>
#include "OpenGLTest2.h"
#include "PolygonTest.h"
#include <LeEngine/Camera.h>
#include <LeEngine/Window.h>
#include "NetworkTask.h"
#include <LeEngine/Lighting.h>
#include <memory>

void Application::Run(int argc, char* argv[])
{
    SettingsManager* settings = new SettingsManager("client.conf");
    settings->AddSetting("screen.X", 800);
    settings->AddSetting("screen.Y", 600);
    settings->AddSetting("screen.BPP", 24);
    settings->AddSetting("screen.fullscreen", false);
    settings->AddSetting("logging.file", "client.log");
    settings->AddSetting("logging.write_to_console", true);
    settings->AddSetting("logging.with_timestamp", true);
    settings->AddSetting("connection.host", "127.0.0.1");
    settings->AddSetting("connection.port", 54321);
    settings->LoadConfig();

    bool fs = GetConfig("screen.fullscreen", bool);

    new Log(GetConfig("logging.file", std::string));
    if (!LeLog.Init())
        return;

    LeLog.EnableConsole(GetConfig("logging.write_to_console", bool));
    LeLog.EnableTime(GetConfig("logging.with_timestamp", bool));

    new Kernel();

    // Init tasks

    std::shared_ptr<GlobalTimer> globalTimer(new GlobalTimer);
    globalTimer->Priority = 10;
    Kernel::Get().AddTask(globalTimer);

    std::shared_ptr<VideoUpdate> videoTask(new VideoUpdate);
    videoTask->Priority = 10000;
    Kernel::Get().AddTask(videoTask);

    std::shared_ptr<InputTask> inputTask(new InputTask);
    inputTask->Priority = 20;
    Kernel::Get().AddTask(inputTask);

    std::shared_ptr<SoundTask> soundTask(new SoundTask);
    soundTask->Priority = 50;
    Kernel::Get().AddTask(soundTask);

    std::shared_ptr<Camera> camera(new Camera);
    camera->Priority = 40;
    Kernel::Get().AddTask(camera);

    std::shared_ptr<LightingManager> lightingManager(new LightingManager);
    lightingManager->Priority = 50;
    Kernel::Get().AddTask(lightingManager);

    std::shared_ptr<NetworkTask> network(new NetworkTask);
    network->Priority = 30;
    Kernel::Get().AddTask(network);

    // Game specific tasks
    
    std::shared_ptr<OpenGLTest2> test(new OpenGLTest2);
    test->Priority = 100;
    Kernel::Get().AddTask(test);

    //std::shared_ptr<PolygonTest> test(new PolygonTest);
    //test->Priority = 100;
    //Kernel::Get().AddTask(test);

    //**********************
    Kernel::Get().Execute();
    //**********************

    SettingsManager::Get().SaveConfig();

    delete Kernel::GetPtr();
    delete SettingsManager::GetPtr();
    delete Log::GetPtr();
}
