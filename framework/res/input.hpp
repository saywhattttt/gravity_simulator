#ifndef INPUT_HPP
#define INPUT_HPP

#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include "camera.hpp"

// Handles keyboard and mouse input for camera movement
class Input {
    public:
        Input(Camera& CameraOBJ_i, GLFWwindow* window);
        void process_input(float time);
    private:
        GLFWwindow* window_p;
        Camera& cameraOBJ;
};

#endif