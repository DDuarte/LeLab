#include "SettingsManager.h"
#include "Log.h"
#include "Dator.h"
#include "VideoUpdate.h"
#include <list>
#include <fstream>
#include <string>

#include <boost/scoped_array.hpp>
using boost::shared_ptr;

void SettingsManager::ParseFile(std::string fileName)
{
    std::ifstream in(fileName.c_str());
    if (!in.is_open())
    {
        LeLog << LOG_APP << "Error, could not open file " << fileName << " in SettingsManager::ParseFile" << NL;
        return;
    }

    while (!in.eof())
    {
        std::string str;
        std::getline(in, str);
        ParseSetting(str);
    }
}

void SettingsManager::SetVariable(std::string& name, std::string& value, int bias /*= 0*/)
{
    if (!_settingMap[name])
        return;

    if (_settingMap[name]->HasMultipleValues())
    {
        std::list<std::string> valuesList;
        
        if (value.find(';') != -1)
        {
            int first = 0;
            int last;

            while ((last = value.find(';', first)) != -1)
            {
                valuesList.push_back(value.substr(first, last - first));
                first = last + 1;
            }

            valuesList.push_back(value.substr(first));
        }
        else
            valuesList.push_back(value);

        for (auto it = valuesList.begin(); it != valuesList.end(); it++)
        {
            if (bias > 0)
                (*_settingMap[name]) += (*it);
            else if (bias < 0)
                (*_settingMap[name]) -= (*it);
            else
                (*_settingMap[name]) = (*it);
        }
    }
    else
        (*_settingMap[name]) = value;
}

void SettingsManager::ParseSetting(std::string str)
{
    int bias = 0;
    std::string name, value;

    if (str[0] == '+')
    {
        bias = 1;
        str = str.substr(1);
    }
    else if (str[0] == '-')
    {
        bias = -1;
        str = str.substr(1);
    }

    int eqPos = str.find('=');
    if (eqPos != -1)
    {
        name = str.substr(0, eqPos);
        value = str.substr(eqPos + 1);
    }
    else
    {
        name = str;
        if (bias == 1 || bias == 0)
            value = "1";
        else
            value = "0";
    }

    SetVariable(name, value, bias);
}

#define SETTING(type, target, var, name) target = shared_ptr<Dator<type>>(new Dator<type>(var));RegisterVariable(std::string(name),shared_ptr<BaseDator>(target));
#define LIST(type, target, var, name) target=shared_ptr<ListDator<type>>(new ListDator<type>(var));RegisterVariable(std::string(name),shared_ptr<BaseDator>(target));

void SettingsManager::CreateStandardSettings()
{

    //target(new Dator<type>(var));RegisterVariable(std::string(name),shared_ptr<BaseDator>(target));

    SETTING(int,  VideoUpdate::ScreenWidth,  VideoUpdate::SourceWidth,      "screenX");
    SETTING(int,  VideoUpdate::ScreenHeight, VideoUpdate::SourceHeight,     "screenY");
    SETTING(int,  VideoUpdate::ScreenBPP,    VideoUpdate::SourceBPP,        "screenBPP");
    SETTING(bool, VideoUpdate::Fullscreen,   VideoUpdate::SourceFullscreen, "fullscreen")
}

void SettingsManager::DestroyStandardSettings()
{
}
