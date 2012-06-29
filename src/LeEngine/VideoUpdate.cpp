#include "VideoUpdate.h"
#include "Log.h"
#include "Defines.h"
#include "Kernel.h"
#include "Window.h"
#include <GL/glfw.h>
#include <cassert>
#include <boost/format.hpp>
#include <boost/shared_ptr.hpp>
using boost::shared_ptr;


Window* VideoUpdate::_window  = NULL;
int VideoUpdate::SourceWidth  = 800;
int VideoUpdate::SourceHeight = 600;
int VideoUpdate::SourceBPP    = 24;
bool VideoUpdate::SourceFullscreen = false;
shared_ptr< Dator<int> > VideoUpdate::ScreenWidth;
shared_ptr< Dator<int> > VideoUpdate::ScreenHeight;
shared_ptr< Dator<int> > VideoUpdate::ScreenBPP;
shared_ptr< Dator<bool> > VideoUpdate::Fullscreen;

bool VideoUpdate::Start()
{
    assert(ScreenWidth && ScreenHeight && ScreenBPP && Fullscreen);

    if (!glfwInit())
    {
        LeLog << LOG_CLIENT << "Could not initialize glfw." << NL;
        return false;
    }

    _window = new Window("CHANGEME", SourceWidth, SourceHeight, SourceFullscreen, SourceBPP);
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
