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

    // [setting name, [actual value, default value]]
    std::map< std::string, std::pair<std::string, std::string> > _settings;
    void Load(const std::string& fileName);
    void Save(const std::string& fileName, bool firstLoad = false);

public:
    //! Constructor
    SettingsManager(const std::string& filename);
    //! Constructor with OnLoad callback
    SettingsManager(const std::string& filename, void (*f)());

    //! Sets a callback that is called when the config is loaded
    void SetOnLoadCallback(void (*f)()) { _onLoadCallback = f; }

    //! Loads the config file, will create one if it does not exist
    void LoadConfig();
    //! Save config, requires existing config file
    void SaveConfig();
    //! Loads the config file once again
    void ReloadConfig();
    
    //! Retrieves a setting, use the macro GetConfig for ease of use
    template <typename T> T GetSetting(std::string name);
    //! Creates a new setting, a default/initial value is required
    template <typename T> void AddSetting(std::string name, T defaultValue);
};

template <typename T>
T SettingsManager::GetSetting(std::string name)
{
    if (_settings.find(name) != _settings.end())
        return boost::lexical_cast<T>(_settings[name].second);
    return T();
}

template <typename T>
void SettingsManager::AddSetting(std::string name, T defaultValue)
{
    _settings[name] = std::make_pair("", boost::lexical_cast<std::string>(defaultValue));
}

#endif // SETTINGSMANAGER_H
