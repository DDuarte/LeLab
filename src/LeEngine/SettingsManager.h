#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include "Singleton.h"
#include <string>
#include <boost/noncopyable.hpp>
#include <utility>
#include <boost/lexical_cast.hpp>
#include <map>

#define GetConfig(name, T) SettingsManager::Get().GetSetting<T>(name)

class SettingsManager : public Singleton<SettingsManager>
{
private:
    std::string _fileName;
    bool _loaded;
    void (*_onLoadCallback)();

    std::map< std::string, std::pair<std::string, std::string> > _settings;
    void Load(const std::string& fileName);
    void Save(const std::string& fileName, bool firstLoad = false);

public:
    SettingsManager(const std::string& filename);
    SettingsManager(const std::string& filename, void (*f)());

    void SetOnLoadCallback(void (*f)()) { _onLoadCallback = f; }

    void LoadConfig();
    void SaveConfig();
    void ReloadConfig();
    
    template <typename T>
    T GetSetting(std::string name);

    template <typename T>
    void AddSetting(std::string name, T defaultValue);
};

template <typename T>
T SettingsManager::GetSetting(std::string name)
{
    if (_settings.find(name) != _settings.end())
        return boost::lexical_cast<T>(_settings[name].first);
    return T();
}

template <typename T>
void SettingsManager::AddSetting(std::string name, T defaultValue)
{
    _settings[name] = std::make_pair("", boost::lexical_cast<std::string>(defaultValue));
}

#endif // SETTINGSMANAGER_H
