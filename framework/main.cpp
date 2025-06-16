#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <math.h>

#include "window.hpp"
#include "input.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "buffer.hpp"
#include "transformations.hpp"
#include "camera.hpp"

#define window_w 1920
#define window_h 1080
#define window_name "hello"

int main() {
    glfwInit();
    
    Window windowOBJ(window_h, window_w, window_name);
    Shader shaderOBJ("../shaders/vertex_shader.glsl", "../shaders/fragment_shader.glsl");
    Transform transOBJ(shaderOBJ);
    Camera cameraOBJ(transOBJ, 0.05f);
    Input inputOBJ(cameraOBJ, windowOBJ.window);


    float vertex[] = {
        // Positions (x, y, z)  // Texture Coords (u, v)

        // Face 1: Front (-Z face)
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // 0: Bottom-left
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // 1: Bottom-right
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // 2: Top-right
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // 3: Top-left

        // Face 2: Back (+Z face)
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // 4: Bottom-left
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // 5: Bottom-right
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // 6: Top-right
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // 7: Top-left

        // Face 3: Left (-X face)
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // 8: Top-back
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // 9: Top-front
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // 10: Bottom-front
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // 11: Bottom-back

        // Face 4: Right (+X face)
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // 12: Top-back
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // 13: Top-front
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // 14: Bottom-front
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // 15: Bottom-back

        // Face 5: Bottom (-Y face)
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // 16: Front-left
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // 17: Front-right
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // 18: Back-right
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // 19: Back-left

        // Face 6: Top (+Y face)
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // 20: Front-left
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // 21: Front-right
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // 22: Back-right
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // 23: Back-left
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

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f), 
        glm::vec3( 2.0f,  5.0f, -15.0f), 
        glm::vec3(-1.5f, -2.2f, -2.5f),  
        glm::vec3(-3.8f, -2.0f, -12.3f),  
        glm::vec3( 2.4f, -0.4f, -3.5f),  
        glm::vec3(-1.7f,  3.0f, -7.5f),  
        glm::vec3( 1.3f, -2.0f, -2.5f),  
        glm::vec3( 1.5f,  2.0f, -2.5f), 
        glm::vec3( 1.5f,  0.2f, -1.5f), 
        glm::vec3(-1.3f,  1.0f, -1.5f)  
    };

    unsigned int VAO = Buffer::mk_vao();

    Buffer buff_obj = Buffer(VAO, vertex, sizeof(vertex), index, sizeof(index), 5);

    buff_obj.mk_attrib_ptr(3, 0, 0);
    buff_obj.mk_attrib_ptr(2, 1, 3);

    Texture tex_obj_box = Texture("../images/box.png", GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR);
    Texture tex_obj_face = Texture("../images/image.png", GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR);

    shaderOBJ.set_uniform_int("tex_1", 0);
    shaderOBJ.set_uniform_int("tex_2", 1);

    transOBJ.perspective(45.0f, window_w, window_h, 0.1f, 100.0f);
    
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(windowOBJ.window)){
        float time = glfwGetTime();
        inputOBJ.process_input(time);
        
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderOBJ.use();
        tex_obj_box.Bind_tex(GL_TEXTURE0);
        tex_obj_face.Bind_tex(GL_TEXTURE1);
        buff_obj.bind_vao(VAO);
        
        for (unsigned int i = 0; i < 10 ; i++ ){
            transOBJ.reset_model();

            float red_val = (sin(time) / 2.0f) + 0.5f;
            shaderOBJ.set_uniform_float("color_value", red_val);

            transOBJ.translation(cubePositions[i]);

            transOBJ.rotate(time * 200, glm::vec3(0.0f, 0.0f, 1.0f));
            
            float angle = 20.0f * i; 
            transOBJ.rotate(angle, glm::vec3(1.0f, 0.3f, 0.5f));

            transOBJ.set_model();

            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            
        }
        glfwSwapBuffers(windowOBJ.window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}