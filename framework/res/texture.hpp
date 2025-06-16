#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#pragma once

class Texture {
    public:

        Texture(std::string path, GLenum tex_s_wrap, GLenum tex_t_wrap, GLenum tex_min_filter);

        void Bind_tex(GLenum texture_slot){
            glActiveTexture(texture_slot);
            glBindTexture(GL_TEXTURE_2D, texture);
        }

        int width;
        int height;
        int N_channels;

        unsigned int texture;

    private:

        unsigned char* data;
        std::string path_p;

};


#endif