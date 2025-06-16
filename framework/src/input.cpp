#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "input.hpp"


Input::Input(Camera& CameraOBJ_i, GLFWwindow* window)
    : cameraOBJ(CameraOBJ_i), window_p(window)
{
    glfwSetWindowUserPointer(window, &cameraOBJ);
    glfwSetScrollCallback(window_p, Camera::scrollCallback);
}

void Input::process_input(float time) {
    if (glfwGetKey(window_p, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window_p, true);

    cameraOBJ.processKeyboard(window_p, time);

    double xpos, ypos;
    glfwGetCursorPos(window_p, &xpos, &ypos);
    cameraOBJ.processMouse(window_p, xpos, ypos);

}