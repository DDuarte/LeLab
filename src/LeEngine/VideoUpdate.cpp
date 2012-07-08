#include "VideoUpdate.h"
#include "Log.h"
#include "Defines.h"
#include "Kernel.h"
#include "Window.h"
#include "SettingsManager.h"
#include <GL/glfw.h>
#include <cassert>

Window* VideoUpdate::_window;

bool VideoUpdate::Start()
{
    if (!glfwInit())
    {
        LeLog.Write("Could not initialize glfw.");
        return false;
    }

    _window = new Window("CHANGEME", GetConfig(ScreenWidth), GetConfig(ScreenHeight), GetConfig(ScreenFullScreen), GetConfig(ScreenBPP));
    if (!_window->Create())
    {
        glfwTerminate();
        return false;
    }

    //_window->EnableMouse(false);
    return true;
}

void VideoUpdate::Update()
{
    if (!glfwGetWindowParam(GLFW_OPENED))
        Kernel::Get().KillAllTasks();

    _window->SwapBuffers();
}

void VideoUpdate::Stop()
{
    delete _window;
    glfwTerminate();
}
