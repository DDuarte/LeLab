cmake_minimum_required(VERSION 2.6)
project(LeLab)

# find and configure Boost
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON) 
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED COMPONENTS system date_time regex filesystem)

# find opengl
find_package(OpenGL REQUIRED)

# add source directories
add_subdirectory(dep)
add_subdirectory(src)
