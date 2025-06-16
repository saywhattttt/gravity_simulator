#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "window.hpp"
#include "input.hpp"

Window::Window()
    : window_name("basic window"), window_height(800), window_width(600)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(window_width, window_height, window_name, nullptr, nullptr);
    if (!window) {
        std::cout << "Failed to create window" << std::endl;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
    glViewport(0, 0, window_width, window_height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

Window::Window(int window_h, int window_w, const char* window_n)
    : window_name(window_n), window_height(window_h), window_width(window_w)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(window_width, window_height, window_name, nullptr, nullptr);
    if (!window) {
        std::cout << "Failed to create window" << std::endl;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
    glViewport(0, 0, window_width, window_height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);                                // lock cursor
}

Window::~Window() {
    glfwDestroyWindow(window);
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}