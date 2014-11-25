#include "Window.h"
#include "Log.h"
#include <string>
#include <GL/glew.h>
#include <GL/glfw.h>
#include <boost/format.hpp>

Window::Window(const std::string& title, int width, int height, bool fullScreen, int bpp)
    : _title(title), _width(width), _height(height), _fullScreen(fullScreen), _depthBits(0), _stencilBits(0)
{
    BPPToBits(bpp, _redBits, _greenBits, _blueBits, _alphaBits);
}

bool Window::Create()
{
    if(!glfwOpenWindow(_width, _height, _redBits, _greenBits, _blueBits, _alphaBits, _depthBits, _stencilBits, FullScreenMode(_fullScreen)))
    {
        LeLog.WriteP("Window: Could not open glfw window. Width: %i, height: %i, r: %i, g: %i, b: %i, a: %i, d: %i, s: %i, fullscreen: %s",
            _width, _height, _redBits, _greenBits, _blueBits, _alphaBits, _depthBits, _stencilBits, _fullScreen ? "yes" : "no");
        return false;
    }

    glfwSetWindowTitle(_title.c_str());

    LeLog.WriteP("Window: Opened glfw window. Width: %i, height: %i, r: %i, g: %i, b: %i, a: %i, d: %i, s: %i, fullscreen: %s",
        _width, _height, _redBits, _greenBits, _blueBits, _alphaBits, _depthBits, _stencilBits, _fullScreen ? "yes" : "no");

    auto version = glGetString(GL_VERSION);
    auto renderer = glGetString(GL_RENDERER);

    LeLog.WriteP("OpenGL version: %s, renderer: %s", version, renderer);

    return true;
}

void Window::EnableMouse(bool enable)
{
    enable ? glfwEnable(GLFW_MOUSE_CURSOR) : glfwDisable(GLFW_MOUSE_CURSOR);
    LeLog.WriteP( "Window: Mouse cursor %b", enable);;
}

void Window::SetRefreshRate(int rate)
{
    // Only available in fullscreen mode
    if (!_fullScreen)
        return;

    glfwOpenWindowHint(GLFW_REFRESH_RATE, rate);
    LeLog.WriteP("Window: Changed screen refresh rate to %i", rate);
}

void Window::ForceOpenGlVersion(int major, int minor)
{
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, major);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, minor);

    LeLog.WriteP("Window: Forced OpenGl version: (%i, %i)", major, minor);
}

void Window::SetTitleName(const std::string& title)
{
    _title = title;
    glfwSetWindowTitle(title.c_str());
    LeLog.WriteP("Window: Changed title to \"%s\"", title.c_str());
}

void Window::EnableOpenGlDebugContext(bool enable)
{
    glfwOpenWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, enable ? GL_TRUE : GL_FALSE);
    LeLog.WriteP("Window: Debug context %b", enable);
}

void Window::SetFSAA(int samples)
{
    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, samples);
    LeLog.WriteP("Window: Set multisampling samples to %i", samples);
}

void Window::DisableResize(bool disable)
{
    glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, disable ? GL_FALSE : GL_TRUE);
    LeLog.WriteP("Window: Disable resize %b", disable);
}

void Window::BPPToBits(int bpp, int& redBits, int& greenBits, int& blueBits, int& alphaBits)
{
    switch (bpp)
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
            LeLog.WriteP("Bad BPP in Window::BPPToBits (%i). Defaulting to 24.", bpp);
            BPPToBits(24, redBits, greenBits, blueBits, alphaBits);
            return;
        }
    }
}
