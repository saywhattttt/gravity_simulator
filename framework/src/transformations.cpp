#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "transformations.hpp"
#include "shader.hpp"

#include <iostream>

Transform::Transform(Shader& ShaderOBJ_i)
    : shaderOBJ(ShaderOBJ_i), model(glm::mat4(1.0f)), projection(glm::mat4(1.0f)), view(glm::mat4(1.0f))
{}



void Transform::translation(const glm::vec3& trans_by) {
    model = glm::translate(model, trans_by);
}

void Transform::rotate(float rotate_by_deg, const glm::vec3& axis) {
    model = glm::rotate(model, glm::radians(rotate_by_deg), axis);
}

void Transform::scale(const glm::vec3& scale_by) {
    model = glm::scale(model, scale_by);
}

void Transform::set_model(){
    shaderOBJ.set_uniform_mat4("model", glm::value_ptr(model));
}



void Transform::set_view(){
    shaderOBJ.set_uniform_mat4("view", glm::value_ptr(view));
}

void Transform::set_view(glm::vec3 mov_vec){
    view = glm::translate(view, mov_vec);
    shaderOBJ.set_uniform_mat4("view", glm::value_ptr(view));
}



void Transform::perspective(float fov, float width, float height, float near, float far) {
    projection = glm::perspective(glm::radians(fov), width / height, near, far);
    ratio_p = width / height;
    near_p = near;
    far_p = far;
    shaderOBJ.set_uniform_mat4("projection", glm::value_ptr(projection));
}
void Transform::changeFov(float fov){
    projection = glm::perspective(glm::radians(fov), ratio_p, near_p, far_p);
    shaderOBJ.set_uniform_mat4("projection", glm::value_ptr(projection));
}