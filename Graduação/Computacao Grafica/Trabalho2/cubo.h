#ifndef CUBO_H
#define CUBO_H

#include "vertices.h"
#include <vector>
#include "include/glad/glad.h"
#include <GL/freeglut.h>
using namespace std;
class Cubo
{

public:
    Cubo();
   
    void init(int tam); //inicializa
    void draw(float x, float y, float z); //desenha na tela
    vector<vector<Vertices>> gera_malhas(float tamanho);

private:

    float vertices[8][3];
    int faces[6][4];
    float colors[6][3];
    float normais[6][3];
    float cor[3];
};
#endif