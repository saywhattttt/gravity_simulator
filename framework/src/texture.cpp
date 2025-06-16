#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <string>
#include <iostream>

#include "texture.hpp"

// tex_s_wrap -> x axis wrap
// tex_t_wrap -> y axis wrap
// tex_min_filter -> minmap compression filter
Texture::Texture(std::string path, GLenum tex_s_wrap, GLenum tex_t_wrap, GLenum tex_min_filter){
    path_p = path;
    
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, tex_s_wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tex_t_wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, tex_min_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);                   // mag filter is not needed because minmaps do not zoom

    GLenum format;
    
    stbi_set_flip_vertically_on_load(true);                                             // flips the got data vertically (can remove if needed)
    data = stbi_load(path.c_str(), &width, &height, &N_channels, 0);
    if (data){
        switch (N_channels) {
        case 1: format = GL_RED;
            break;
        case 3: format = GL_RGB;
            break;
        case 4: format = GL_RGBA;
            break;
        default:
            std::cout << "courrepted file read" << std::endl;
            break;
        }
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}