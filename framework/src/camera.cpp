#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <camera.hpp>
#include <iostream>

Camera::Camera(Transform& transOBJ_i, float camSpeed)
    : transOBJ(transOBJ_i), cameraPos(glm::vec3(0.0f, 0.0f, 3.0f)), cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)), cameraUp(glm::vec3(0.0f, 1.0f,  0.0f)),
      cameraSpeed_usr(camSpeed), lastFrame{0.0f}, yaw(-90.0f), pitch(0.0f), direction(glm::vec3(0.0f, 0.0f, 0.0f)), lastX(400.0f), lastY(300.0f), sensitivity(0.1f), firstMouse(true), fov(45.0f)
{}

void Camera::set_cam(){
    transOBJ.view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    transOBJ.set_view();
}

void Camera::processKeyboard(GLFWwindow* window, float time){
    float deltaTime = time - lastFrame;
    lastFrame = time;
    float cameraSpeed = cameraSpeed_usr * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
        cameraSpeed = cameraSpeed_usr * 2 * deltaTime;
    }
    else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS){
        cameraSpeed = cameraSpeed_usr * 4 * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        cameraPos += cameraUp * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        cameraPos -= cameraUp * cameraSpeed;
    set_cam();
}

void Camera::mouseCallback(GLFWwindow* window, double xpos, double ypos){
    Camera* cam = static_cast<Camera*>(glfwGetWindowUserPointer(window));
    if (cam) {
        cam->processMouse(window, xpos, ypos);
    }
}
void Camera::scrollCallback(GLFWwindow* window, double xOff, double yOff){
    Camera* cam = static_cast<Camera*>(glfwGetWindowUserPointer(window));
    if (cam) {
        cam->processScroll(xOff, yOff);
    }
}
void Camera::processMouse(GLFWwindow* window, double xpos, double ypos){
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS){
        if (firstMouse) {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }
        float xOffset = xpos - lastX;
        float yOffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;
        xOffset *= sensitivity;
        yOffset *= sensitivity;
        yaw += xOffset;
        pitch += yOffset;
        if(pitch > 89.0f)
        pitch =  89.0f;
        if(pitch < -89.0f)
        pitch = -89.0f;
        calculateDirection();
        set_cam();
    } else {
        lastX = xpos;
        lastY = ypos;
    }
}
void Camera::processScroll(double xOff, double yOff){
    fov -= (float)yOff;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f; 
    transOBJ.changeFov(fov);
}

void Camera::calculateDirection(){
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}