#include "SettingsManager.h"
#include "Log.h"
#include <string>
#include <exception>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/info_parser.hpp>
#include <boost/filesystem.hpp>

SettingsManager::SettingsManager(const std::string& filename) : _fileName(filename), _loaded(false), _onLoadCallback(NULL)
{
}

SettingsManager::SettingsManager(const std::string& filename, void (*f)()) : _fileName(filename), _loaded(false)
{
    SetOnLoadCallback(f);
}

void SettingsManager::LoadConfig()
{
    LeLog.WriteP("Loading configuration file %s...", _fileName.c_str());
    try
    {
        if (!boost::filesystem::exists(_fileName))
            Save(_fileName, true);

        Load(_fileName);
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
    LeLog.WriteP( "Saving configuration file %s...", _fileName.c_str());
    try
    {
        Save(_fileName);
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

void SettingsManager::Load(const std::string& fileName)
{
    using boost::property_tree::ptree;
    ptree pt;

    read_info(fileName, pt);

    for (auto itr = _settings.begin(); itr != _settings.end(); ++itr)
    {
        itr->second.first = pt.get(itr->first, itr->second.second);
    }
}

void SettingsManager::Save(const std::string& fileName, bool firstLoad /*=false*/)
{
    using boost::property_tree::ptree;
    ptree pt;

    for (auto itr = _settings.begin(); itr != _settings.end(); ++itr)
        pt.put(itr->first, firstLoad ? itr->second.second : itr->second.first);

    write_info(fileName, pt);
}
