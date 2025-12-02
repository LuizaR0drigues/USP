#ifndef PIRAMIDE_H
#define PIRAMIDE_H

#include "include/glad/glad.h"
#include <GL/freeglut.h>
#include <cmath>
#include <vector>
#include "vertices.h"

using namespace std;

class Piramide
{

public:
    Piramide();
   
    void init(int tam); //inicializa
    void draw(float x, float y, float z); //desenha na tela
    vector<vector<Vertices>> gera_malhas();
    void calcNormalFace(Vertices v1, Vertices v2, Vertices v3, float& nx, float& ny, float&nz);

private:
    float vertices[4][3];
    int faces[4][3];
    float colors[4][3];
    GLfloat nromal[3];    
    void calcula_normal(GLfloat* v1, GLfloat* v2, GLfloat* v3, GLfloat* saida);

};
#endif