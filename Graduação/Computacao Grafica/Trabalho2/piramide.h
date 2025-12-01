#ifndef PIRAMIDE_H
#define PIRAMIDE_H

#include "include/glad/glad.h"
#include <GL/freeglut.h>

class Piramide
{

public:
    Piramide();
   
    void init(int tam); //inicializa
    void draw(float x, float y, float z); //desenha na tela

private:

    float vertices[4][3];
    int faces[4][3];
    float colors[4][3];
    GLfloat nromal[3];

    void calcula_normal(GLfloat* v1, GLfloat* v2, GLfloat* v3, GLfloat* saida);
};
#endif