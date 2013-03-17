include_directories(LeServer ${PROJECT_SOURCE_DIR}/src ${Boost_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} ${GLFW_INCLUDE_DIR})

add_executable(LeServer
    main.cpp
    NetworkTask.cpp
    ServerApplication.cpp
    Session.cpp
    TcpServer.cpp
)

target_link_libraries(LeServer ${LE_ENGINE_LIBRARIES} ${GLEW_LIBRARY} ${GLFW_LIBRARY} ${Boost_LIBRARIES} ${OPENGL_LIBRARIES})
