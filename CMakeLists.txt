cmake_minimum_required(VERSION 2.6)
project(LeLab)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lXrandr")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules/")

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED COMPONENTS system date_time regex filesystem)

find_package(X11 REQUIRED)

# find opengl
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLFW2 REQUIRED)
find_package(ASSIMP REQUIRED)
find_package(SOIL REQUIRED)
find_package (Threads)
find_package(GTest REQUIRED)

# add source directories
add_subdirectory(src)
