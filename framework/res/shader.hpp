#ifndef SHADER_HPP
#define SHADER_HPP

#pragma once 

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

class Shader{
public:
        unsigned int Program_id;
        Shader(const std::string& vertex_path, const std::string& fragment_path);

        void use();

        void const set_uniform_mat4(const std::string& name, const GLfloat* trans_ptr);

        void const set_uniform_float(const std::string& name, float value);
        void const set_uniform_float(const std::string& name, float value1, float value2);
        void const set_uniform_float(const std::string& name, float value1, float value2, float value3);
        void const set_uniform_float(const std::string& name, float value1, float value2, float value3, float value4);

        void const set_uniform_int(const std::string& name, int value);

        void const set_uniform_bool(const std::string& name, bool value);

    private:
        
        std::string get_src(const std::string& shader_path);
        void compile_shader(GLenum shader_type, unsigned int& shader_id, std::string& shader_source);

        int success;
        char infoLog[512];
        void error_log(unsigned int& obj_id, std::string error_pos);
        void link_error(unsigned int& obj_id, std::string error_pos);
};

#endif