include_directories(LeEngine ${Boost_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} ${GLFW_INCLUDE_DIR})

set(Network_hdrs   ByteBuffer.h Network.h OpcodeMgr.h Packet.h)
set(Math_hdrs      DMath.h MathDefines.h Matrix.h Quaternion.h Random.h Vector.h)
set(Geometry_hdrs  Line.h Plane.h)
set(Logging_hdrs   Log.h)
set(Helpers_hdrs   Singleton.h)
set(Sound_hdrs     SoundTask.h)
set(Misc_hdrs      Defines.h SystemInfo.h)
set(Settings_hdrs  SettingsManager.h)
set(Kernel_hdrs    ITask.h Kernel.h IApplication.h)
set(Timing_hdrs    GlobalTimer.h)
set(Input_hdrs     InputTask.h)
set(Rendering_hdrs VideoUpdate.h Camera.h Scene.h Renderer.h Window.h Shapes.h Color.h Vertex.h Lighting.h VideoUpdate.h)

set(Network_srcs   ByteBuffer.cpp Network.cpp OpcodeMgr.cpp)
set(Math_srcs      Random.cpp)
set(Geometry_srcs  Line.cpp Plane.cpp)
set(Logging_srcs   Log.cpp)
set(Helpers_srcs   )
set(Sound_srcs     SoundTask.cpp)
set(Misc_srcs      SystemInfo.cpp)
set(Settings_srcs  SettingsManager.cpp)
set(Kernel_srcs    Kernel.cpp)
set(Timing_srcs    GlobalTimer.cpp)
set(Input_srcs     InputTask.cpp)
set(Rendering_srcs VideoUpdate.cpp Camera.cpp Scene.cpp Window.cpp Shapes.h Color.cpp Lighting.cpp VideoUpdate.cpp)

source_group(Network   FILES ${Network_hdrs}   ${Network_srcs})
source_group(Math      FILES ${Math_hdrs}      ${Math_srcs})
source_group(Geometry  FILES ${Geometry_hdrs}  ${Geometry_srcs})
source_group(Logging   FILES ${Logging_hdrs}   ${Logging_srcs})
source_group(Helpers   FILES ${Helpers_hdrs}   ${Helpers_srcs})
source_group(Sound     FILES ${Sound_hdrs}     ${Sound_srcs})
source_group(Misc      FILES ${Misc_hdrs}      ${Misc_srcs})
source_group(Settings  FILES ${Settings_hdrs}  ${Settings_srcs})
source_group(Kernel    FILES ${Kernel_hdrs}    ${Kernel_srcs})
source_group(Timing    FILES ${Timing_hdrs}    ${Timing_srcs})
source_group(Input     FILES ${Input_hdrs}     ${Input_srcs})
source_group(Rendering FILES ${Rendering_hdrs} ${Rendering_srcs})

add_library(LeEngine STATIC
    ${Network_hdrs}   ${Network_srcs}
    ${Math_hdrs}      ${Math_srcs}
    ${Geometry_hdrs}  ${Geometry_srcs}
    ${Logging_hdrs}   ${Logging_srcs}
    ${Helpers_hdrs}   ${Helpers_srcs}
    ${Sound_hdrs}     ${Sound_srcs}
    ${Misc_hdrs}      ${Misc_srcs}
    ${Settings_hdrs}  ${Settings_srcs}
    ${Kernel_hdrs}    ${Kernel_srcs}
    ${Timing_hdrs}    ${Timing_srcs}
    ${Input_hdrs}     ${Input_srcs}
    ${Rendering_hdrs} ${Rendering_srcs}
)

target_link_libraries(LeEngine ${GLEW_LIBRARY} ${GLFW_LIBRARY} ${OPENGL_LIBRARIES} ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${X11_LIBRARIES})
