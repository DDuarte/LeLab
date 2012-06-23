#ifndef APPLICATION_H
#define APPLICATION_H

#include "window.h"

#include <string>

class Application
{
public:
    Application();

    //! Singleton
    static Application& Get() { static Application Application; return Application; }

    void Initialize();
    static void Render();
    static void Resize(int32 width, int32 height);
    static void KeyboardCB(uint8 key, int x, int y);
    static void MouseCB(int32 button, int32 state, int32 x, int32 y);
private:
    std::string _name;
    WindowManager _wManager;
};




#endif // APPLICATION_H