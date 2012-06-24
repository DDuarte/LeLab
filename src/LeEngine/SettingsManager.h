#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include "Dator.h"
#include "Singleton.h"
#include "MMPointer.h"
#include <string>
#include <map>

class SettingsManager : public Singleton<SettingsManager>
{
public:
    SettingsManager() { _settingMap.clear(); CreateStandardSettings(); }
    virtual ~SettingsManager() { DestroyStandardSettings(); }

    void RegisterVariable(std::string& name, MMPointer<BaseDator>& var) { _settingMap[name] = var; }
    void SetVariable(std::string& name, std::string& value, int bias = 0);

    void CreateStandardSettings();;
    void DestroyStandardSettings();;

    void ParseSetting(std::string str);
    void ParseFile(std::string fileName);

protected:
    std::map< std::string, MMPointer<BaseDator> > _settingMap;
};

#endif // SETTINGSMANAGER_H
