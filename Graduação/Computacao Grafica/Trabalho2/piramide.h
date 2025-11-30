#ifndef PIRAMIDE_H
#define PIRAMIDE_H

#include "include/glad/glad.h"
#include <GL/freeglut.h>

class Piramide
{

public:
    Piramide();
   
    void init(); //inicializa
    void draw(float x, float y, float z); //desenha na tela

private:

    float vertices[4][3];
    int faces[4][3];
    float colors[4][3];
};
#endif