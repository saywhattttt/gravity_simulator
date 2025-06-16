#ifndef CAMERA_HPP
#define CAMERA_HPP

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "transformations.hpp"

class Camera{

    public:

        Camera(Transform& transOBJ_i, float camSpeed);

        static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
        static void scrollCallback(GLFWwindow* window, double xOff, double yOff);
        void processMouse(GLFWwindow* window, double xpos, double ypos);
        void processScroll(double xOff, double yOff);
        void calculateDirection();
        
        void processKeyboard(GLFWwindow* window, float time);
        
        float cameraSpeed_usr;
        
        glm::vec3 cameraPos;
        glm::vec3 cameraFront;
        glm::vec3 cameraUp;

    private:
        
        void set_cam();
        Transform& transOBJ;
        float lastFrame;

        float lastX;
        float lastY;
        bool firstMouse;

        float yaw;
        float pitch;

        float fov;

        glm::vec3 direction;

        float sensitivity;
};

#endif 