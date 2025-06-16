#version 330 core
out vec4 fragcolor;

in vec4 color;

uniform float color_value;
uniform sampler2D tex_1;
uniform sampler2D tex_2;

void main(){
    // fragcolor = vec4(color_value, 0.0f, 0.0f, 1.0f);
    fragcolor = color;
}