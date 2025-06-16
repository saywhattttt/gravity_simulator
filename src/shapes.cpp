#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <cmath>
#include <iostream>

#include "buffer.hpp"
#include "shapes.hpp"

void Shapes::cube(unsigned int location, unsigned int VAO){
    cubeVAO = VAO;

    float vertex[] = {
    // Positions (x, y, z)  // Texture Coords (u, v)

    // Face 1: Front (-Z face)
    -0.5f, -0.5f, -0.5f, // 0: Bottom-left
    0.5f, -0.5f, -0.5f, // 1: Bottom-right
    0.5f,  0.5f, -0.5f, // 2: Top-right
    -0.5f,  0.5f, -0.5f, // 3: Top-left

    // Face 2: Back (+Z face)
    -0.5f, -0.5f,  0.5f, // 4: Bottom-left
    0.5f, -0.5f,  0.5f, // 5: Bottom-right
    0.5f,  0.5f,  0.5f, // 6: Top-right
    -0.5f,  0.5f,  0.5f, // 7: Top-left

    // Face 3: Left (-X face)
    -0.5f,  0.5f,  0.5f, // 8: Top-back
    -0.5f,  0.5f, -0.5f, // 9: Top-front
    -0.5f, -0.5f, -0.5f, // 10: Bottom-front
    -0.5f, -0.5f,  0.5f, // 11: Bottom-back

    // Face 4: Right (+X face)
    0.5f,  0.5f,  0.5f, // 12: Top-back
    0.5f,  0.5f, -0.5f, // 13: Top-front
    0.5f, -0.5f, -0.5f, // 14: Bottom-front
    0.5f, -0.5f,  0.5f, // 15: Bottom-back

    // Face 5: Bottom (-Y face)
    -0.5f, -0.5f, -0.5f, // 16: Front-left
    0.5f, -0.5f, -0.5f, // 17: Front-right
    0.5f, -0.5f,  0.5f, // 18: Back-right
    -0.5f, -0.5f,  0.5f, // 19: Back-left

    // Face 6: Top (+Y face)
    -0.5f,  0.5f, -0.5f, // 20: Front-left
    0.5f,  0.5f, -0.5f, // 21: Front-right
    0.5f,  0.5f,  0.5f, // 22: Back-right
    -0.5f,  0.5f,  0.5f, // 23: Back-left
    };

    unsigned int index[] = {
    // Face 1: Front (-Z face) - using uniqueVertices 0, 1, 2, 3
    0, 1, 2,  // Triangle 1: bottom-left, bottom-right, top-right
    2, 3, 0,  // Triangle 2: top-right, top-left, bottom-left

    // Face 2: Back (+Z face) - using uniqueVertices 4, 5, 6, 7
    4, 5, 6,  // Triangle 1: bottom-left, bottom-right, top-right
    6, 7, 4,  // Triangle 2: top-right, top-left, bottom-left

    // Face 3: Left (-X face) - using uniqueVertices 8, 9, 10, 11
    8, 9, 10, // Triangle 1: top-back, top-front, bottom-front
    10, 11, 8, // Triangle 2: bottom-front, bottom-back, top-back

    // Face 4: Right (+X face) - using uniqueVertices 12, 13, 14, 15
    12, 13, 14, // Triangle 1: top-back, top-front, bottom-front
    14, 15, 12, // Triangle 2: bottom-front, bottom-back, top-back

    // Face 5: Bottom (-Y face) - using uniqueVertices 16, 17, 18, 19
    16, 17, 18, // Triangle 1: front-left, front-right, back-right
    18, 19, 16, // Triangle 2: back-right, back-left, front-left

    // Face 6: Top (+Y face) - using uniqueVertices 20, 21, 22, 23
    20, 21, 22, // Triangle 1: front-left, front-right, back-right
    22, 23, 20  // Triangle 2: back-right, back-left, front-left
    };

    Buffer bufferOBJ = Buffer(VAO, vertex, sizeof(vertex), index, sizeof(index), 3);
    bufferOBJ.mk_attrib_ptr(3, location, 0);
}

void Shapes::drawCube(){
    Buffer::bind_vao(cubeVAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}


void Shapes::sphere(float radius, int sectorCount, int stackCount, int location, unsigned int VAO) {
    sphereVAO = VAO;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    float x, y, z, xy;
    float sectorStep = 2 * M_PI / sectorCount;
    float stackStep = M_PI / stackCount;
    float sectorAngle, stackAngle;

    for(int i = 0; i <= stackCount; ++i) {
        stackAngle = M_PI / 2 - i * stackStep;
        xy = radius * cosf(stackAngle);
        z = radius * sinf(stackAngle);

        for(int j = 0; j <= sectorCount; ++j) {
            sectorAngle = j * sectorStep;
            x = xy * cosf(sectorAngle);
            y = xy * sinf(sectorAngle);
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
        }
    }

    int k1, k2;
    for(int i = 0; i < stackCount; ++i) {
        k1 = i * (sectorCount + 1);
        k2 = k1 + sectorCount + 1;
        for(int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
            if(i != 0) {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }
            if(i != (stackCount-1)) {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }
    sphereIndexCount = indices.size();

    Buffer bufferOBJ = Buffer(VAO, vertices.data(), vertices.size() * sizeof(float),
     indices.data(),  indices.size() * sizeof(float), 3);
    bufferOBJ.mk_attrib_ptr(3, location, 0);
}

void Shapes::drawSphere() {
    glBindVertexArray(sphereVAO);
    glDrawElements(GL_TRIANGLES, sphereIndexCount, GL_UNSIGNED_INT, 0);
}