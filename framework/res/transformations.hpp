#ifndef TRANSFORMATIONS_HPP
#define TRANSFORMATIONS_HPP

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.hpp"

// Handles model, view, projection matrices and camera movement
class Transform {
    public:
        Transform(Shader& shaderOBJ_i);

        // Model matrix transformations
        void translation(const glm::vec3& trans_by);
        void rotate(float rotate_by_deg, const glm::vec3& axis);
        void scale(const glm::vec3& scale_by);
        void set_model();

        // Projection matrix setup
        void perspective(float fov, float width, float height, float near, float far);
        void changeFov(float fov);

        // view matrix setup
        void set_view();
        void set_view(glm::vec3 mov_vec);

        // Reset matrices
        void reset_model() { model = glm::mat4(1.0f); }
        void reset_view() { view = glm::mat4(1.0f); }
        void reset_projection() { projection = glm::mat4(1.0f); }

        // Matrices
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 projection;
    private:

        Shader& shaderOBJ;

        float ratio_p;
        float near_p;
        float far_p;
};

#endif