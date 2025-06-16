cmake_minimum_required(VERSION 3.10)
project(GL_abstraction)

set(CMAKE_CXX_STANDARD 11)

set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

include_directories(framework/res)
include_directories(res)
include_directories(glad/include)
include_directories(imgui-master)

add_library(glad_cfile STATIC glad/src/glad.c)

file(GLOB frame_src_files framework/src/*.cpp)
file(GLOB src_files src/*.cpp)
file(GLOB IMGUI_SRC
    imgui-master/imgui.cpp
    imgui-master/imgui_draw.cpp
    imgui-master/imgui_tables.cpp
    imgui-master/imgui_widgets.cpp
    imgui-master/imgui_demo.cpp
    imgui-master/backends/imgui_impl_glfw.cpp
    imgui-master/backends/imgui_impl_opengl3.cpp
)

add_executable(GL_abstraction main.cpp ${frame_src_files} ${src_files} ${IMGUI_SRC})

target_include_directories(GL_abstraction PRIVATE imgui-master imgui-master/backends)
target_link_libraries(GL_abstraction OpenGL::GL OpenGL::GLX glfw GLEW glad_cfile)