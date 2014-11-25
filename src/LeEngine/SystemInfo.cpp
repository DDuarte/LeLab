#include "SystemInfo.h"
#include <vector>
#include <string>

std::string SystemInfo::GetOS()
{
#ifdef _WIN32
    return "Windows";
#else
    return "Unix";
#endif
    //...
}

std::vector<VideoMode> SystemInfo::GetAvailableVideoModes() {
    const int maxCount = 25;
    GLFWvidmode list[maxCount];

    int count = glfwGetVideoModes(list, maxCount);

    // It's a bit pointless to convert GLFWvidmode to
    // this VideoMode but it was done so we are not
    // dependent on glfw structs/headers.

    std::vector<VideoMode> vec;
    VideoMode mod;
    for (int i = 0; i < count; ++i) {
        mod.Width = list[i].Width;
        mod.Height = list[i].Height;
        mod.RedBits = list[i].RedBits;
        mod.GreenBits = list[i].GreenBits;
        mod.BlueBits = list[i].BlueBits;
        vec.push_back(mod);
    }
    return vec;
}
