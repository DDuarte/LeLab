#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include "Dator.h"
#include "Singleton.h"
#include <string>
#include <map>
#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

class SettingsManager : public Singleton<SettingsManager>
{
public:
    SettingsManager() { _settingMap.clear(); CreateStandardSettings(); }
    virtual ~SettingsManager() { DestroyStandardSettings(); }

    void RegisterVariable(std::string& name, shared_ptr<BaseDator>& var) { _settingMap[name] = var; }
    void SetVariable(std::string& name, std::string& value, int bias = 0);

    void CreateStandardSettings();;
    void DestroyStandardSettings();;

    void ParseSetting(std::string str);
    void ParseFile(std::string fileName);

protected:
    std::map< std::string, shared_ptr<BaseDator> > _settingMap;
};

#endif // SETTINGSMANAGER_H
