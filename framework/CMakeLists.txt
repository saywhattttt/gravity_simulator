cmake_minimum_required(VERSION 3.10)
project(GL_abstraction)

set(CMAKE_CXX_STANDARD 11)

set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

include_directories(res)
include_directories(glad/include)

add_library(glad_cfile STATIC glad/src/glad.c)

file(GLOB src_files src/*.cpp)

add_executable(GL_abstraction main.cpp ${src_files})
target_link_libraries(GL_abstraction OpenGL::GL OpenGL::GLX glfw GLEW glad_cfile)