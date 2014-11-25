#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H

#include <GL/glew.h>
#include <GL/glfw.h>
#include <vector>
#include <string>

struct VideoMode
{
    int Width, Height; // Video resolution
    int RedBits; // Number of red bits
    int GreenBits; // Number of green bits
    int BlueBits; // Number of blue bits
};

class SystemInfo
{
public:
    static std::string GetOS();
    static int ProcessorCount() { return glfwGetNumberOfProcessors(); }

    static void GetOpenGlVersion(int* major, int* minor, int* rev) { glfwGetGLVersion(major, minor, rev); }

    static std::vector<VideoMode> GetAvailableVideoModes();

    // To be expanded...
};

#endif // SYSTEMINFO_H
