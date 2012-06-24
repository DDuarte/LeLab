#include "Window.h"
#include "Application.h"

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <stdexcept>

Window::Window( std::string name /*= ""*/, Size2 size /*= DEFAULT_WINDOW_SIZE*/, uint32 displayMode /*= DEFAULT_WINDOW_DISPLAY_MODE*/ ) : _name(name), _size(size), _displayMode(displayMode)
{
    glutInitWindowSize(_size.X, _size.Y);

    glutInitDisplayMode(_displayMode);

    _id = glutCreateWindow(_name.c_str());
     glewInit();

    if (_id < 1)
        throw std::runtime_error("ERROR: Could not create a new rendering window.");

}
