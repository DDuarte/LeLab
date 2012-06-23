#ifndef WINDOW_H
#define WINDOW_H

#include "Defines.h"

#include <GL/freeglut.h>
#include <string>
#include <map>

#define DEFAULT_WINDOW_SIZE Size2(800,600)
#define DEFAULT_WINDOW_DISPLAY_MODE GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA

class Window
{
public:
    Window(std::string name = "", Size2 size = DEFAULT_WINDOW_SIZE, uint32 displayMode = DEFAULT_WINDOW_DISPLAY_MODE);

    void SetSize(Size2 newSize) { _size = newSize; }
    int32 GetId() { return _id; }
private:
    int32 _id;

    Size2 _position;
    Size2 _size;
    uint32 _displayMode;

    std::string _name;
    std::string _title;
};

class WindowManager
{
public:
    WindowManager() { _windows = std::map<int32, Window*>(); }
    Window* GetActiveWindow() { return _windows[glutGetWindow()]; }

    void AddWindow(Window *newWindow) { _windows[newWindow->GetId()] = newWindow; }
private:
    std::map<int32, Window*> _windows;
};

#endif // WINDOW_H