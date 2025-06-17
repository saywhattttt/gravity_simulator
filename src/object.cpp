#include "transformations.hpp"
#include "buffer.hpp"
#include "shapes.hpp"
#include "object.hpp"

#include <iostream>

void ObjectC::setObj(Object& to_set_obj, Transform& transOBJ){
    if (to_set_obj.type == cube){
        setSquare(to_set_obj, transOBJ);
    }
    else if (to_set_obj.type == sphere){
        setSphere(to_set_obj, transOBJ);
    }
}

void ObjectC::drawObj(Object& draw_obj){
    if (draw_obj.type == cube){
        drawSquare();
    }
    else if (draw_obj.type == sphere){
        drawSphere();
    }
}

void ObjectC::updateEntity(entity& to_set_entity, float time){
    if (to_set_entity.fixed) {return;}
    to_set_entity.velocity += to_set_entity.acceleration * time;
    to_set_entity.theObject->position += to_set_entity.velocity * time;
}

void ObjectC::setSquare(Object& to_set_obj, Transform& transOBJ){
    shapeOBJ.cube(to_set_obj.location, to_set_obj.VAO);
    transOBJ.reset_model();
    transOBJ.scale(to_set_obj.scale); 
    transOBJ.rotate(to_set_obj.rotationAngle, to_set_obj.rotationAxis);
    transOBJ.translation(to_set_obj.position); 
    transOBJ.set_model();
}

void ObjectC::drawSquare(){
    shapeOBJ.drawCube();
}

void ObjectC::setSphere(Object& to_draw_obj, Transform& transOBJ){
    shapeOBJ.sphere(to_draw_obj.radius, to_draw_obj.sectorCount, to_draw_obj.stackCount ,to_draw_obj.location, to_draw_obj.VAO);
    transOBJ.reset_model();
    transOBJ.translation(to_draw_obj.position);
    transOBJ.rotate(to_draw_obj.rotationAngle, to_draw_obj.rotationAxis);
    transOBJ.scale(to_draw_obj.scale);
    transOBJ.set_model();
}

void ObjectC::drawSphere(){
    shapeOBJ.drawSphere();
}
