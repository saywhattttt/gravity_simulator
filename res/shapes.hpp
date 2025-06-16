#ifndef SHAPES_HPP
#define SHAPES_HPP

#pragma once

#include <glm/glm.hpp>

class Shapes{
    public:

        void cube(unsigned int location, unsigned int VAO);
        void drawCube();

        void sphere(float radius, int sectorCount, int stackCount, int location, unsigned int VAO);
        void drawSphere();

    private:
        unsigned int cubeVAO;
        unsigned int sphereVAO;
        int sphereIndexCount = 0;
};


#endif