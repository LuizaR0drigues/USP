#ifndef ESFERA_H
#define ESFERA_H

#include "include/glad/glad.h"
#include <GL/freeglut.h>


class Esfera
{

public:
    Esfera();
   
    void init(float raio, int fatias, int stacks); //inicializa
    void draw(float x, float y, float z); //desenha na tela

private:

    float raio;
    int fatias, stacks;
};

#endif