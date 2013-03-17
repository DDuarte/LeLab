include_directories(LeClient ${PROJECT_SOURCE_DIR}/src ${Boost_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} ${GLFW_INCLUDE_DIR} ${SOIL_INCLUDE_DIR})

add_executable(LeClient
    Application.cpp
    main.cpp
    NetworkTask.cpp
    OpenGLTest.cpp
    OpenGLTest2.cpp
    PolygonTest.cpp
    TcpClient.cpp
)

target_link_libraries(LeClient ${LE_ENGINE_LIBRARIES} ${GLEW_LIBRARY} ${GLFW_LIBRARY} ${SOIL_LIBRARY} ${Boost_LIBRARIES} ${OPENGL_LIBRARIES})
