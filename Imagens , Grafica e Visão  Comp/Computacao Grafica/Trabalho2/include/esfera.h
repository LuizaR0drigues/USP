#ifndef ESFERA_H
#define ESFERA_H

#include "glad/glad.h"
#include <GL/freeglut.h>
#include <vector>
#include "structs.h"

using namespace std;

class Esfera
{

public:
    Esfera();
   
    void init(float raio, int fatias, int stacks); //inicializa
    void draw(float x, float y, float z); //desenha na tela
    vector<vector<VerticesPhong>> gera_malhas(float raio, int fatias, int stacks);

private:

    float raio;
    int fatias, stacks;
};

#endif