#include "SettingsManager.h"
#include "Log.h"
#include <string>
#include <exception>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/info_parser.hpp>

SettingsManager::SettingsManager() : _fileName(SETTINGS_FILENAME), _loaded(false), _onLoadCallback(NULL)
{
    LoadConfig();
}

SettingsManager::SettingsManager(void (*f)()) : _fileName(SETTINGS_FILENAME), _loaded(false), _onLoadCallback(NULL)
{
    SetOnLoadCallback(f);
    LoadConfig();
}


void SettingsManager::LoadConfig()
{
    LeLog.WriteP("Loading configuration file %s...", _fileName.c_str());
    try
    {
        _settings.Load(_fileName);
        _loaded = true;

        if (_onLoadCallback)
            _onLoadCallback();
    }
    catch (std::exception &e)
    {
    	_loaded = false;
        LeLog.WriteP("Loading configuration file %s failed: %s", _fileName.c_str(), e.what());
    }
}

void SettingsManager::SaveConfig()
{
    if (!_loaded)
    {
        LeLog.Write("Saving configuration file failed because configuration was not loaded before.");
        return;
    }

    LeLog.WriteP( "Saving configuration file %s...", _fileName.c_str());
    try
    {
        _settings.Save(_fileName);
    }
    catch (std::exception &e)
    {
        _loaded = false;
        LeLog.WriteP("Saving configuration file %s failed: %s", _fileName.c_str(), e.what());
    }
}

void SettingsManager::ReloadConfig()
{
    if (!_loaded)
    {
        LeLog.Write("Reloading configuration file failed because configuration was not loaded before.");
        return;
    }
    
    LeLog.Write( "Reloading configuration file...");
    LoadConfig();
}

void SettingsManager::Settings::Load(const std::string& fileName)
{
    using boost::property_tree::ptree;
    ptree pt;

    read_info(fileName, pt);

    // screen
    ScreenWidth = pt.get("screen.X", 800);
    ScreenHeight = pt.get("screen.Y", 600);
    ScreenBPP = pt.get("screen.BPP", 24);
    ScreenFullScreen = pt.get("screen.fullscreen", false);

    // logging
    LogClientFileName = pt.get("logging.files.client", "clntlog.log");
    LogApplicationFileName = pt.get("logging.files.app", "applog.log");
    LogServerFileName = pt.get<std::string>("logging.files.server", "srvrlog.log");
    LogWriteToConsole = pt.get("logging.write_to_console", true);
    LogWithTimestamp = pt.get("logging.with_timestamp", true);
}

void SettingsManager::Settings::Save( const std::string& fileName )
{
    using boost::property_tree::ptree;
    ptree pt;

    // screen
    pt.put("screen.X", ScreenWidth);
    pt.put("screen.Y", ScreenHeight);
    pt.put("screen.BPP", ScreenBPP);
    pt.put("screen.fullscreen", ScreenFullScreen);

    // logging
    pt.put("logging.files.client", LogClientFileName);
    pt.put("logging.files.app", LogApplicationFileName);
    pt.put("logging.files.server", LogServerFileName);
    pt.put("logging.write_to_console", LogWriteToConsole);
    pt.put("logging.with_timestamp", LogWithTimestamp);

    write_info(fileName, pt);
}
