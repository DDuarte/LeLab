#ifndef INPUTTASK_H
#define INPUTTASK_H

#include "ITask.h"
#include "Defines.h"
#include "MMPointer.h"
#include "MMDynamicBlob.h"

#include <iostream>

#include <map>
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
    //static int KeyCount;

    //! glfwSetKeyCallback
    static void GLFWCALL KeyHandler(int key, int action) { OldKeys[key] = Keys[key]; Keys[key] = (action == GLFW_PRESS); std::cout << "Key " << (char)key << " - " << action << std::endl; }

    static bool CurKey(int index) { return Keys[index]; }
    static bool OldKey(int index) { return OldKeys[index]; }

    static bool KeyDown(int index)      { return CurKey(index) && !OldKey(index); }
    static bool KeyStillDown(int index) { return CurKey(index) && OldKey(index); }
    static bool KeyUp(int index)        { return !CurKey(index) && OldKey(index); }
    static bool KeyStillUp(int index)   { return !CurKey(index) && !OldKey(index); }

    // Mouse

    static int dX, dY;
    static int Wheel, OldWheel;
    static std::map<int, bool> Buttons;
    static std::map<int, bool> OldButtons;

    //! glfwSetMouseButtonCallback
    static void GLFWCALL MouseButtonHandler(int button, int action) { OldButtons[button] = Buttons[button]; Buttons[button] = (button == GLFW_PRESS); std::cout << "Mouse " << button << " - " << action << std::endl; }
    //! glfwSetMousePosCallback
    static void GLFWCALL MousePosHandler(int x, int y) { dX = x; dY = y; std::cout << "mouse: " << x << ", " << y << std::endl; }
    //! glfwSetMouseWheelCallback
    static void GLFWCALL MouseWheelHandler(int pos) { OldWheel = Wheel; Wheel = pos; std::cout << "wheel: " << pos << std::endl; }

    static bool CurMouse(int button) { return Buttons[button]; }
    static bool OldMouse(int button) { return OldButtons[button]; }

    static bool MouseDown(int button)      { return CurMouse(button) && !OldMouse(button); }
    static bool MouseStillDown(int button) { return CurMouse(button) && OldMouse(button); }
    static bool MouseUp(int button)        { return !CurMouse(button) && OldMouse(button); }
    static bool MouseStillUp(int button)   { return !CurMouse(button) && !OldMouse(button); }

    AUTO_SIZE;
};

#endif // INPUTTASK_H
