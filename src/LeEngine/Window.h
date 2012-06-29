#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <GL/glew.h>
#include <GL/glfw.h>
#include "SystemInfo.h"

// TODO: use for depth and stencil bits (http://www.glfw.org/GLFWReference275.pdf)

enum Callback // unused
{
    CALLBACK_WINDOW_CLOSE = 0, // glfwSetWindowCloseCallback | int GLFWCALL functionname(void);
    CALLBACK_WINDOW_RESIZE = 1, // glfwSetWindowSizeCallback | void GLFWCALL functionname(int width, int height);
    CALLBACK_WINDOW_REFRESH = 2 // glfwSetWindowRefreshCallback | void GLFWCALL functionname(void );
};

class Window
{
protected:
    //typedef boost::function<void(void)> func;
    //std::map<Callback, boost::function_base*> _callbacks;

    std::string _title;
    int _width, _height;
    bool _fullScreen;
    int _redBits, _greenBits, _blueBits, _alphaBits, _depthBits, _stencilBits;

public:
    //! Constructor
    Window(const std::string& title, int width, int height, bool fullScreen, int depth);

    //! Destructor, closes window
    ~Window() { glfwCloseWindow(); }

    //! Creates the actual windows. Returns false if anything goes wrong.
    bool Create();

    //! Returns the current window's title name
    const std::string& GetTitleName() const { return _title; }

    //! Changes window's title name
    void SetTitleName(const std::string& title);

    //! Changes window's size
    /*!
      This is not affected by DisableResize(true)
    */
    void SetWindowSize(int width, int height) { glfwSetWindowSize(width, height); }

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

    //! Disables or enables window resize (resize enabled by default)
    void DisableResize(bool disable);

    //! Number of samples to use for multisampling
    /*!
      Also called full-scene anti-aliasing.
      A value of 0 disables multisampling (default).
      http://en.wikipedia.org/wiki/Spatial_anti-aliasing
    */
    void SetFSAA(int samples);

    //! Minimizes (iconify) this window
    /*!
      This has no effect if window is minimized already
    */
    void MinimizeWindow() { glfwIconifyWindow(); }

    //! Restores a minimized window
    /*!
      This has no effect if window was not minimized
    */
    void RestoreWindow() { glfwRestoreWindow(); }

    //! Swaps back and front color buffers of this window
    /*
     It will also poll input events
    */
    void SwapBuffers() { glfwSwapBuffers(); }

    //! Function called when the window is closed (int func())
    void SetWindowCloseCallback(int (*f)(void)) { glfwSetWindowCloseCallback(f); }
    //! Function called when the window's size changes (void func(int width, int height))
    /*!
      It will be called at least once when window is created.
    */
    void SetWindowResizeCallback(void (*f)(int,int)) { glfwSetWindowSizeCallback(f); }
    //! Function called when the window was damaged and needs to be refreshed
    void SetWindowRefreshCallback(void (*f)(void)) { glfwSetWindowRefreshCallback(f); }

protected:
    // helpers
    static void BPPToBits(int bpp, int& redBits, int& greenBits, int& blueBits, int& alphaBits);
    static int FullScreenMode(bool fullScreen) { return fullScreen ? GLFW_FULLSCREEN : GLFW_WINDOW; }

};

#endif // WINDOW_H
