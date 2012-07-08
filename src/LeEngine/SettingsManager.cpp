#include "SettingsManager.h"
#include <string>
#include <exception>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/info_parser.hpp>
#include <boost/filesystem.hpp>

SettingsManager::SettingsManager(const std::string& filename) : _fileName(filename),
    _loaded(false), _onLoadCallback(NULL) {}

SettingsManager::SettingsManager(const std::string& filename, void (*f)()) : _fileName(filename), _loaded(false)
{
    SetOnLoadCallback(f);
}

void SettingsManager::LoadConfig()
{

#if _DEBUG
    std::cout << "Loading configuration file " << _fileName << "..." << std::endl;
#endif

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
#if _DEBUG
        std::cout << "Loading configuration file "  << _fileName << " failed: "<< e.what() << ")" << std::endl;
#endif
    }
}

void SettingsManager::SaveConfig()
{
#if _DEBUG
    std::cout << "Saving configuration file " << _fileName << "..." << std::endl;
#endif
    try
    {
        Save(_fileName);
    }
    catch (std::exception &e)
    {
        _loaded = false;

#if _DEBUG
        std::cout << "Saving configuration file " << _fileName << " failed: " << e.what() << std::endl;
#endif
    }
}

void SettingsManager::ReloadConfig()
{
    if (!_loaded)
    {
#if _DEBUG
        std::cout << "Reloading configuration file failed because configuration was not loaded before." << std::endl;
#endif
        return;
    }
    
#if _DEBUG
    std::cout << "Reloading configuration file..." << std::endl;
#endif
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
