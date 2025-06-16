#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 tex_coor_in;

out vec2 tex_coor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    tex_coor = tex_coor_in;
}