#ifndef INPUTTASK_H
#define INPUTTASK_H

#include "ITask.h"
#include "Defines.h"

#include <map>
#include <GL/glew.h>
#include <GL/glfw.h>

class InputTask : public ITask
{
public:
    InputTask() {}
    virtual ~InputTask() {}

    bool Start();
    void Update();
    void Stop();

    // Keyboard

    static std::map<int, bool> Keys;
    static std::map<int, bool> OldKeys;

    //! glfwSetKeyCallback
    static void GLFWCALL KeyHandler(int key, int action) { OldKeys[key] = Keys[key]; Keys[key] = (action == GLFW_PRESS); }

    static bool CurKey(int index) { return Keys[index]; }
    static bool OldKey(int index) { return OldKeys[index]; }

    static bool KeyDown(int index)      { return CurKey(index) && !OldKey(index); }
    static bool KeyStillDown(int index) { return CurKey(index) && OldKey(index); }
    static bool KeyUp(int index)        { return !CurKey(index) && OldKey(index); }
    static bool KeyStillUp(int index)   { return !CurKey(index) && !OldKey(index); }

    // Mouse

    static int MouseX, MouseY;
    static int dX, dY;
    static int Wheel, OldWheel;
    static std::map<int, bool> Buttons;
    static std::map<int, bool> OldButtons;

    //! glfwSetMouseButtonCallback
    static void GLFWCALL MouseButtonHandler(int button, int action) { OldButtons[button] = Buttons[button]; Buttons[button] = (button == GLFW_PRESS); }
    //! glfwSetMousePosCallback
    static void GLFWCALL MousePosHandler(int x, int y) { dX = x - MouseX; dY = y - MouseY; MouseX = x; MouseY = y; }
    //! glfwSetMouseWheelCallback
    static void GLFWCALL MouseWheelHandler(int pos) { OldWheel = Wheel; Wheel = pos; }

    static bool CurMouse(int button) { return Buttons[button]; }
    static bool OldMouse(int button) { return OldButtons[button]; }

    static bool MouseDown(int button)      { return CurMouse(button) && !OldMouse(button); }
    static bool MouseStillDown(int button) { return CurMouse(button) && OldMouse(button); }
    static bool MouseUp(int button)        { return !CurMouse(button) && OldMouse(button); }
    static bool MouseStillUp(int button)   { return !CurMouse(button) && !OldMouse(button); }
};

#endif // INPUTTASK_H
