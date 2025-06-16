#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "buffer.hpp"

Buffer::Buffer(unsigned int& VAO, float data[], int data_size, int total_elemets){
    
    // total_elemets is the total elements in 1 line of you buffer

    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, data_size, data, GL_STATIC_DRAW);

    total_elemets_i = total_elemets;
}

Buffer::Buffer(unsigned int& VAO, float data[], int data_size, unsigned int element_data[], int element_size, int total_elemets){

    // total_elemets is the total elements in 1 line of you buffer

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ARRAY_BUFFER, data_size, data, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, element_size, element_data, GL_STATIC_DRAW);

    total_elemets_i = total_elemets;
}


void Buffer::mk_attrib_ptr(int elements, int location, int start_loc) {

    // elements are the number of elements in the current attrib
    // location is the location you want to access the data from in the vertex shader
    // start loc is the number of elements from the start where you said attrib start lies

    glVertexAttribPointer(location, elements, GL_FLOAT, GL_FALSE, sizeof(float)*total_elemets_i, (void*)(sizeof(float) * start_loc));
    glEnableVertexAttribArray(location);
}

unsigned int Buffer::mk_vao(){
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    return VAO;
}

void Buffer::bind_vao(unsigned int VAO){
    glBindVertexArray(VAO);
}