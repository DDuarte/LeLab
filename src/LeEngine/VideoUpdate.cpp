#include "VideoUpdate.h"
#include "Log.h"
#include "Defines.h"
#include "Kernel.h"
#include <GL/glfw.h>
#include <cassert>
#include <boost/format.hpp>
#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

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

    int redBits, greenBits, blueBits, alphaBits;
    switch (SourceBPP)
    {
        case 8:
        {
            redBits = 3;
            greenBits = 3;
            blueBits = 2;
            alphaBits = 0;
            break;
        }
        case 16:
        {
            redBits = 5;
            greenBits = 6;
            blueBits = 5;
            alphaBits = 0;
            break;
        }
        case 24:
        {
            redBits = 8;
            greenBits = 8;
            blueBits = 8;
            alphaBits = 0;
            break;
        }
        case 32:
        {
            redBits = 8;
            greenBits = 8;
            blueBits = 8;
            alphaBits = 8;
            break;
        }
        default:
        {
            LeLog << LOG_CLIENT << "Bad BPP defined in settings file (" << ToString(SourceBPP) << ")." << NL;
            glfwTerminate();
            return false;
        }
    }
    
    int mode = SourceFullscreen ? GLFW_FULLSCREEN : GLFW_WINDOW;

    if(!glfwOpenWindow(SourceWidth, SourceHeight, redBits, greenBits, blueBits, alphaBits, 0, 0, mode))
    {
        LeLog << LOG_CLIENT << (boost::format("Could not open glfw window. Width: %1%, height: %2%, r: %3%, g: %4%, b: %5%, a: %6%, mode: %7%") %
            SourceWidth % SourceHeight % redBits % greenBits % blueBits % alphaBits % SourceFullscreen).str() << NL;

        glfwTerminate();
        return false;
    }

    //glfwDisable(GLFW_MOUSE_CURSOR);
    return true;
}

void VideoUpdate::Update()
{
    //glClear(GL_COLOR_BUFFER_BIT);
    if (!glfwGetWindowParam(GLFW_OPENED)) Kernel::Get().KillAllTasks();

    Kernel::Get().RenderObjectList();

    glfwSwapBuffers();
}

void VideoUpdate::Stop()
{
    glfwTerminate();
}
