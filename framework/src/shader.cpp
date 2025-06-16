#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>

#include "shader.hpp"

std::string Shader::get_src (const std::string& shader_path){
    std::ifstream file(shader_path.c_str());
    if (!file.is_open()){
        std::cout << "Failed to open file: " << shader_path<< std::endl;
        return "";
    }
    std::string file_content((std::istreambuf_iterator<char>(file)),std::istreambuf_iterator<char>());
    file.close();
    return file_content;
}

void Shader::error_log(unsigned int& obj_id, std::string error_pos){
    glGetShaderiv(obj_id, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(obj_id, 512, NULL, infoLog);
        std::cout << error_pos << "\n" << infoLog << std::endl;
    };
}

void Shader::link_error(unsigned int& obj_id, std::string error_pos){
    glGetShaderiv(obj_id, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(obj_id, 512, NULL, infoLog);
        std::cout << error_pos << "\n" << infoLog << std::endl;
    };
}

void Shader::compile_shader(GLenum shader_type, unsigned int& shader_id, std::string& shader_source_str){
    const char* shader_source = shader_source_str.c_str();
    shader_id = glCreateShader(shader_type);
    glShaderSource(shader_id, 1, &shader_source, NULL);
    glCompileShader(shader_id);
}

Shader::Shader(const std::string& vertex_path, const std::string& fragment_path){
    std::string vertex_source = get_src(vertex_path);
    std::string fragment_source = get_src(fragment_path);

    unsigned int vertex_shader;
    unsigned int fragment_shader;

    compile_shader(GL_VERTEX_SHADER, vertex_shader, vertex_source);
    error_log(vertex_shader, "ERROR::SHADER::VERTEX::COMPILATION_FAILED");
    compile_shader(GL_FRAGMENT_SHADER, fragment_shader, fragment_source);
    error_log(fragment_shader, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED");

    Program_id = glCreateProgram();
    glAttachShader(Program_id, vertex_shader);
    glAttachShader(Program_id, fragment_shader);
    glLinkProgram(Program_id);

    link_error(Program_id, "ERROR::SHADER::PROGRAM::LINKING_FAILED");

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

void Shader::use(){
    glUseProgram(Program_id);
}

void const Shader::set_uniform_mat4(const std::string& name, const GLfloat* trans_ptr){
    use();
    glUniformMatrix4fv(glGetUniformLocation(Program_id, name.c_str()), 1, GL_FALSE, trans_ptr);
}

// here use float there is no such thing as vec1 in glsl(would be useless anyway)
void const Shader::set_uniform_float(const std::string& name, float value){
    use();
    glUniform1f(glGetUniformLocation(Program_id, name.c_str()), value);
}

// use vec2 in shader
void const Shader::set_uniform_float(const std::string& name, float value1, float value2){
    use();
    glUniform2f(glGetUniformLocation(Program_id, name.c_str()), value1, value2);
}

// use vec 3 in shader
void const Shader::set_uniform_float(const std::string& name, float value1, float value2, float value3){
    use();
    glUniform3f(glGetUniformLocation(Program_id, name.c_str()), value1, value2, value3);
}

// use vec4 in shader
void const Shader::set_uniform_float(const std::string& name, float value1, float value2, float value3, float value4){
    use();
    glUniform4f(glGetUniformLocation(Program_id, name.c_str()), value1, value2, value3, value4);
}

void const Shader::set_uniform_int(const std::string& name, int value){
    use();
    glUniform1i(glGetUniformLocation(Program_id, name.c_str()), (int)value);
}

void const Shader::set_uniform_bool(const std::string& name, bool value){
    use();
    glUniform1i(glGetUniformLocation(Program_id, name.c_str()), (int)value);
}