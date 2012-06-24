#include "InputTask.h"
#include <GL/glfw.h>
#include <map>

int InputTask::dX = 0;
int InputTask::dY = 0;
int InputTask::Wheel = 0;
int InputTask::OldWheel = 0;
std::map<int, bool> InputTask::Buttons = std::map<int, bool>();
std::map<int, bool> InputTask::OldButtons = std::map<int, bool>();
std::map<int, bool> InputTask::Keys = std::map<int, bool>();
std::map<int, bool> InputTask::OldKeys = std::map<int, bool>();

bool InputTask::Start()
{
    dX = 0;
    dY = 0;
    Wheel = 0;
    OldWheel = 0;

    glfwSetKeyCallback(KeyHandler);
    glfwSetMouseButtonCallback(MouseButtonHandler);
    glfwSetMousePosCallback(MousePosHandler);
    glfwSetMouseWheelCallback(MouseWheelHandler);

    glfwPollEvents();

    return true;
}

void InputTask::Update()
{
    //OldButtons = Buttons;
    //OldKeys = Keys;
    //OldWheel = Wheel;

    glfwPollEvents();
}

void InputTask::Stop()
{
    OldButtons.clear();
    Buttons.clear();
    Keys.clear();
    OldKeys.clear();
}
