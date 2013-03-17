#include "ServerApplication.h"
#include <LeEngine/Log.h>
#include <LeEngine/SettingsManager.h>
#include <LeEngine/Kernel.h>
#include "NetworkTask.h"
#include <LeEngine/ITask.h>

#include <memory>

void ServerApplication::Run(int argc, char* argv[])
{
    SettingsManager* settings = new SettingsManager("server.conf");
    settings->AddSetting("server.port", 54321);
    settings->AddSetting("server.bindIp", "127.0.0.1");
    settings->AddSetting("logging.file", "server.log");
    settings->AddSetting("logging.write_to_console", true);
    settings->AddSetting("logging.with_timestamp", true);
    settings->LoadConfig();

    new Log(GetConfig("logging.file", std::string));
    if (!LeLog.Init())
        return;

    LeLog.EnableConsole(GetConfig("logging.write_to_console", bool));
    LeLog.EnableTime(GetConfig("logging.with_timestamp", bool));

    new Kernel();

    // Init tasks

    std::shared_ptr<NetworkTask> network(new NetworkTask);
    network->Priority = 100;
    Kernel::Get().AddTask(network);

    //**********************
    Kernel::Get().Execute();
    //**********************

    SettingsManager::Get().SaveConfig();

    delete Kernel::GetPtr();
    delete Log::GetPtr();
    delete SettingsManager::GetPtr();
}