include_directories(LeEngine ${Boost_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} ${GLFW_INCLUDE_DIR})

add_library(LeEngine
    ByteBuffer.cpp
    InputTask.cpp
    Network.cpp
    SettingsManager.cpp
    Camera.cpp
    Kernel.cpp
    OpcodeMgr.cpp
    SoundTask.cpp
    Color.cpp
    Lighting.cpp
    Plane.cpp
    SystemInfo.cpp
    File.cpp
    Line.cpp
    Random.cpp
    VideoUpdate.cpp
    GlobalTimer.cpp
    Log.cpp
    Scene.cpp
    Window.cpp
)

target_link_libraries(LeEngine ${GLEW_LIBRARY} ${GLFW_LIBRARY} ${OPENGL_LIBRARIES} ${Boost_LIBRARIES})
