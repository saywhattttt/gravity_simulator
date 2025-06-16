#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#pragma once

#include <glm/glm.hpp>

enum objectType{
    cube,
    sphere
};

struct Object{
    objectType type;

    // universal need
    std::string Name;
    unsigned int VAO;
    int location;
    glm::vec3 position;
    glm::vec3 scale;
    float rotationAngle;
    glm::vec3 rotationAxis;

    // sphere need
    double radius;
    int sectorCount;
    int stackCount;
};

struct entity{
    Object* theObject;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    double mass;
};

class ObjectC{
    public:
    
        void setObj(Object& to_set_obj, Transform& transOBJ);
        void drawObj(Object& draw_obj);

        void updateEntity(entity& to_set_entity, float time);
    
    private:
        
        void setSquare(Object& to_set_obj, Transform& transOBJ);
        void setSphere(Object& to_set_obj, Transform& transOBJ);

        void drawSquare();
        void drawSphere();

        Shapes shapeOBJ;
};


#endif

