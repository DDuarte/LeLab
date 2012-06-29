#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include "Singleton.h"
#include <string>
#include <boost/noncopyable.hpp>

#define SETTINGS_FILENAME "settings.conf"
#define GetConfig(name) SettingsManager::Get().GetSettings()->name

class SettingsManager : public Singleton<SettingsManager>
{
public:
    struct Settings
    {
        // screen
        int ScreenWidth;
        int ScreenHeight;
        int ScreenBPP;
        bool ScreenFullScreen;

        // logging
        std::string LogClientFileName;
        std::string LogApplicationFileName;
        std::string LogServerFileName;
        bool LogWriteToConsole;
        bool LogWithTimestamp;

        void Load(const std::string& fileName);
        void Save(const std::string& fileName);
    };
private:
    std::string _fileName;
    bool _loaded;
    Settings _settings;

public:
    SettingsManager();

    void LoadConfig();
    void SaveConfig();
    void ReloadConfig();
    Settings* GetSettings() const { return _loaded ? const_cast<Settings*>(&_settings) : NULL;}
};

#endif // SETTINGSMANAGER_H
