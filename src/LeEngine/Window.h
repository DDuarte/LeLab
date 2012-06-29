#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <GL/glew.h>
#include <GL/glfw.h>
#include "SystemInfo.h"

class Window
{
protected:
    std::string _title;
    int _width, _height;
    bool _fullScreen;
    int _redBits, _greenBits, _blueBits, _alphaBits, _depthBits, _stencilBits;

public:
    //! Constructor
    Window(const std::string& title, int width, int height, bool fullScreen, int depth);

    //! Creates the actual windows. Returns false if anything goes wrong.
    bool Create();

    //! Returns the current windows title name
    const std::string& GetTitleName() const { return _title; }

    //! Changes windows title name
    void SetTitleName(const std::string& title);

    //! Changes vertical monitor refresh rate
    /*!
      Only available in fullscreen mode.
      0 by default (defined by the system)
    */
    void SetRefreshRate(int rate);

    //! Enables or disables mouse cursor
    void EnableMouse(bool enable);

    //! Hint for compatibility (1.1 by default)
    void ForceOpenGlVersion(int major, int minor);

    //! Returns the version of OpenGl running
    void GetOpenGlVersion(int* major, int* minor, int* rev) { SystemInfo::GetOpenGlVersion(major, minor, rev); }

    void EnableOpenGlDebugContext(bool enable);

    //! Disables or enables window resize (disabled by default)
    void DisableResize(bool disable);

    //! Number of samples to use for multisampling
    /*!
      Also called full-scene anti-aliasing.
      A value of 0 disables multisampling (default).
      http://en.wikipedia.org/wiki/Spatial_anti-aliasing
    */
    void SetFSAA(int samples);

    // TODO: callback handling, use for depth and stencil bits, close,
    // set windows position, iconify/restore (http://www.glfw.org/GLFWReference275.pdf)

protected:
    // helpers
    static void BPPToBits(int bpp, int& redBits, int& greenBits, int& blueBits, int& alphaBits);
    static int FullScreenMode(bool fullScreen) { return fullScreen ? GLFW_FULLSCREEN : GLFW_WINDOW; }

};

#endif // WINDOW_H
