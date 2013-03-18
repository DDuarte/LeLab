include_directories(LeServer ${PROJECT_SOURCE_DIR}/src ${Boost_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} ${GLFW_INCLUDE_DIR})

set(All_hdrs NetworkTask.h ServerApplication.h Session.h TcpServer.h)
set(All_srcs main.cpp NetworkTask.cpp ServerApplication.cpp Session.cpp TcpServer.cpp)

add_executable(LeServer
    ${All_hdrs} ${All_srcs}
)

target_link_libraries(LeServer ${LE_ENGINE_LIBRARIES} ${GLEW_LIBRARY} ${GLFW_LIBRARY} ${Boost_LIBRARIES} ${OPENGL_LIBRARIES})
