#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <iostream>
#include <math.h>
#include <vector>
#include <thread>
#include <chrono>

#include "window.hpp"
#include "input.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "buffer.hpp"
#include "transformations.hpp"
#include "camera.hpp"

#include "shapes.hpp"
#include "object.hpp"

#define window_w 1920
#define window_h 1080
#define window_name "GravitySimulator"

float square_border = 30.0f;
float G = 1.0f;
// const double G = 6.67430e-11;
bool borderCollisions = true;
bool objectCollisions = true;
float time_speed = 1.0f;

bool was_set = false;
float set_time = 0.0f;
double radius = 1.0f;
float next_velo = 0.0f;
float mass = 3000.0f;
int sectorCount = 32;
int stackCount = 32;
bool PausedTime = false;
float frameCap = 60.0f;

void collision(std::vector<entity>& obj_vec){
    // Border collision
    if (borderCollisions){
        for (auto& ent : obj_vec) {
            float r = ent.theObject->radius;
            if (ent.theObject->position.y - r <= -square_border){
                ent.theObject->position.y = -square_border + r;
                ent.velocity.y *= -1.0f;
            }
            else if (ent.theObject->position.y + r >= square_border){
                ent.theObject->position.y = square_border - r;
                ent.velocity.y *= -1.0f;
            }
            if (ent.theObject->position.x - r <= -square_border){
                ent.theObject->position.x = -square_border + r;
                ent.velocity.x *= -1.0f;
            }
            else if (ent.theObject->position.x + r >= square_border){
                ent.theObject->position.x = square_border - r;
                ent.velocity.x *= -1.0f;
            }
            if (ent.theObject->position.z - r <= -square_border){
                ent.theObject->position.z = -square_border + r;
                ent.velocity.z *= -1.0f;
            }
            else if (ent.theObject->position.z + r >= square_border){
                ent.theObject->position.z = square_border - r;
                ent.velocity.z *= -1.0f;
            }
        }
    }

    for (int i = 0; i < obj_vec.size(); ++i) {
        glm::vec3 total_accel(0.0f);
        for (int j = 0; j < obj_vec.size(); ++j) {
            if (i == j) continue;
            glm::vec3 dir = obj_vec[j].theObject->position - obj_vec[i].theObject->position;
            float dist = glm::distance(obj_vec[i].theObject->position, obj_vec[j].theObject->position);
            float minDist = obj_vec[i].theObject->radius + obj_vec[j].theObject->radius;
            if (objectCollisions){
                if (dist < minDist) {
                    std::swap(obj_vec[i].velocity, obj_vec[j].velocity);
                    glm::vec3 norm = glm::normalize(dir);
                    float overlap = 0.5f * (minDist - dist);
                    obj_vec[i].theObject->position -= overlap * norm;
                    obj_vec[j].theObject->position += overlap * norm;
                }
            }
            if (dist > 0) {
                glm::vec3 norm = glm::normalize(dir);
                double accel_mag = G * obj_vec[j].mass / (dist * dist);
                total_accel += static_cast<float>(accel_mag) * norm;
            }
        }
        obj_vec[i].acceleration = total_accel;
    }
}

void addObj (GLFWwindow* window, glm::vec3& position, glm::vec3& cameraFront, unsigned int& VAO, std::vector<entity>& obj_vec, std::vector<Object>& usr_added, float time){
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS){
        was_set = true;
        set_time = time;
        Object temp_obj;
        temp_obj.type = sphere;
        temp_obj.VAO = VAO;
        temp_obj.location = 0;

        temp_obj.scale = glm::vec3(1.0f, 1.0f, 1.0f);
        temp_obj.radius = radius;

        temp_obj.rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);

        temp_obj.position = position;

        temp_obj.sectorCount = sectorCount;
        temp_obj.stackCount = stackCount;

        entity test_entity;
        usr_added.push_back(temp_obj);
        test_entity.theObject = &usr_added[usr_added.size() - 1];
        cameraFront = glm::normalize(cameraFront);
        test_entity.velocity = cameraFront * next_velo; 
        test_entity.acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
        test_entity.mass = mass;

        obj_vec.push_back(test_entity);
    }
}

void imguiHandle(std::vector<entity>& obj_vec, std::vector<Object>& usr_added, float time, Camera& camOBJ){
    ImGui::Begin("Gravity Simulator Info");
    ImGui::Text("Simulation time: %.2f", time);
    ImGui::Text("Object count: %zu", obj_vec.size());
    ImGui::InputFloat("Time speed", &time_speed);
    ImGui::InputFloat("Frame Cap", &frameCap);
    ImGui::InputFloat("Camera Speed", &camOBJ.cameraSpeed_usr);
    ImGui::InputFloat("Gravity", &G);
    ImGui::InputFloat("Box Size", &square_border);
    if (ImGui::Button("Delete All")) {
        obj_vec.clear();
        usr_added.clear();
    }
    if (ImGui::Button("Reset Velocity")) {
        for (auto& item : obj_vec){
            item.velocity = glm::vec3(0.0f, 0.0f, 0.0f);
        }
    }
    ImGui::Checkbox("Pause Time", &PausedTime);
    ImGui::Checkbox("Border Collisions", &borderCollisions);
    ImGui::Checkbox("Object Collisions", &objectCollisions);
    ImGui::End();

    ImGui::Begin("Next Object Controls");
    ImGui::InputDouble("Radius", &radius);
    ImGui::InputFloat("Mass", &mass);
    ImGui::InputFloat("Initial Velocity (cam dir)", &next_velo);
    ImGui::InputInt("Sector Count", &sectorCount);
    ImGui::InputInt("Stack Count", &stackCount);
    ImGui::End();

    ImGui::Begin("All Objects");
    for (int i = 0; i < obj_vec.size(); ++i) {
        entity& ent = obj_vec[i];
        Object* obj = ent.theObject;
        std::string nodeLabel = "Object " + std::to_string(i);
        char name_buf[128];
        strncpy(name_buf, obj->Name.c_str(), sizeof(name_buf));
        name_buf[sizeof(name_buf) - 1] = '\0';

        if (ImGui::TreeNodeEx(nodeLabel.c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::Text("Type: %s", obj->type == sphere ? "Sphere" : "Cube");
            if (ImGui::InputText("Name", name_buf, sizeof(name_buf))) {
                obj->Name = name_buf;
            }
            ImGui::Checkbox("Fixed", &ent.fixed);
            ImGui::InputFloat3("Position", glm::value_ptr(obj->position));
            ImGui::InputFloat3("Velocity", glm::value_ptr(ent.velocity));
            ImGui::InputFloat3("Scale", glm::value_ptr(obj->scale));
            ImGui::InputDouble("Mass", &ent.mass);
            ImGui::InputDouble("Radius", &obj->radius);
            ImGui::InputFloat("Rotation Angle", &obj->rotationAngle);
            ImGui::InputFloat3("Rotation Axis", glm::value_ptr(obj->rotationAxis));
            ImGui::InputInt("Sector Count", &obj->sectorCount);
            ImGui::InputInt("Stack Count", &obj->stackCount);

            std::string delLabel = "Delete##" + std::to_string(i);
            if (ImGui::Button(delLabel.c_str())) {
                obj_vec.erase(obj_vec.begin() + i);
                usr_added.erase(usr_added.begin() + i);
                ImGui::TreePop();
                break;
            }

            ImGui::TreePop();
        }
    }
    ImGui::End();
}

int main(){
    glfwInit();
    Window windowOBJ(window_h, window_w, window_name);
    Shader shaderOBJ("../shaders/vertex_shader.glsl", "../shaders/fragment_shader.glsl");

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(windowOBJ.window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    Transform transOBJ(shaderOBJ);
    Camera cameraOBJ(transOBJ, 20.0f);
    Input inputOBJ(cameraOBJ, windowOBJ.window);

    ObjectC objectOBJ;
    
    unsigned int VAO = Buffer::mk_vao();

    Object my_obj;
    my_obj.type = sphere;
    my_obj.VAO = VAO;
    my_obj.location = 0;
    my_obj.position = glm::vec3(-5.0f, 0.0f, 0.0f);
    my_obj.scale = glm::vec3(1.0f, 1.0f, 1.0f);
    my_obj.rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
    my_obj.rotationAngle = 0.0f;

    my_obj.radius = 2.0f * 1.0f;
    my_obj.sectorCount = 32;
    my_obj.stackCount = 32;

    Object my_obj2;
    my_obj2.type = sphere;
    my_obj2.VAO = VAO;
    my_obj2.location = 0;
    my_obj2.position = glm::vec3(5.0f, 0.0f, 0.0f);
    my_obj2.scale = glm::vec3(1.0f, 1.0f, 1.0f);
    my_obj2.rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
    my_obj2.rotationAngle = 0.0f;

    my_obj2.radius = 2.0f * 1.0f;
    my_obj2.sectorCount = 32;
    my_obj2.stackCount = 32;

    entity my_entity;
    my_entity.theObject = &my_obj;
    my_entity.velocity = glm::vec3(10.0f, -10.0f, 0.0f);
    my_entity.acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
    // my_entity.mass = 5.97 * pow(10, 24);
    my_entity.mass = 3000.0f;
    my_entity.fixed = false;

    entity my_entity2;
    my_entity2.theObject = &my_obj2;
    my_entity2.velocity = glm::vec3(-10.0f, 10.0f, 0.0f); 
    my_entity2.acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
    // my_entity2.mass = 7.34 * pow(10, 22);
    my_entity2.mass = 3000.0f;
    my_entity2.fixed = false;

    std::vector<entity> obj_vec;
    std::vector<Object> usr_added;          // added so obj_vec does not have a null pointer
    usr_added.reserve(99999);
    usr_added.push_back(my_obj);
    usr_added.push_back(my_obj2);
    obj_vec.push_back(my_entity);
    obj_vec.push_back(my_entity2);

    unsigned int bordervao = Buffer::mk_vao();
    Object borderCube;
    borderCube.type = cube;
    borderCube.VAO = bordervao;
    borderCube.location = 0;
    borderCube.position = glm::vec3(0.0f, 0.0f, 0.0f);
    borderCube.scale = glm::vec3(2.0f * square_border, 2.0f * square_border, 2.0f * square_border);
    borderCube.rotationAngle = 0.0f;
    borderCube.rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
    
    transOBJ.perspective(45.0f, window_w, window_h, 0.1f, 9999999.0f);
    
    glEnable(GL_DEPTH_TEST);
    
    float lastFrame = 0.0f;     // its 0 and not glfwGetTime because the original rotation suffers without it
    float deltaTime = 0.0f;

    
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
while (!glfwWindowShouldClose(windowOBJ.window)){
    float time = glfwGetTime();
    deltaTime = (time - lastFrame);
    lastFrame = time;
    
    if (PausedTime){deltaTime = 0.0f;}
    float frameCap_mili = 1.0f / frameCap;      // 60 fps by default
    
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    imguiHandle(obj_vec, usr_added, time, cameraOBJ);

    ImGuiIO& io = ImGui::GetIO();
    if (!io.WantCaptureMouse && !io.WantCaptureKeyboard) {
        inputOBJ.process_input(time);
    }
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    shaderOBJ.use();

    if (time - set_time >= 1.0f) was_set = false;
    if (was_set == false){
        addObj(windowOBJ.window, cameraOBJ.cameraPos,cameraOBJ.cameraFront, VAO, obj_vec, usr_added, time);
    }
    
    if (borderCollisions){
        borderCube.scale = glm::vec3(2.0f * square_border, 2.0f * square_border, 2.0f * square_border);
        objectOBJ.setObj(borderCube, transOBJ);
        objectOBJ.drawObj(borderCube);
    }

    for (auto& ent : obj_vec) {
        objectOBJ.updateEntity(ent, deltaTime);
    }
    collision(obj_vec);
    for (auto& ent : obj_vec) {
        objectOBJ.setObj(*ent.theObject, transOBJ);
        objectOBJ.drawObj(*ent.theObject);
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(windowOBJ.window);
    if (glfwGetWindowAttrib(windowOBJ.window, GLFW_FOCUSED)){
        float frameEnd = glfwGetTime();
        float frameDuration = frameEnd - time;
        if  (frameDuration < frameCap_mili){
            std::this_thread::sleep_for(std::chrono::duration<float>(frameCap_mili - frameDuration));
        }
    glfwPollEvents();
    } else {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        glfwPollEvents();
    }

}
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}