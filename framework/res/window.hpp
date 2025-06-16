#ifndef WINDOW_HPP
#define WINDOW_HPP

#pragma once

#include <GLFW/glfw3.h>

// Handles GLFW window creation and management
class Window {
    public:
        Window();
        Window(int window_h, int window_w, const char* window_n);
        ~Window();

        GLFWwindow* window;

    private:
        int window_height;
        int window_width;
        const char* window_name;

        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};

#endif