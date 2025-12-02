#ifndef PHONG_H
#define PHONG_H
#include "include/glad/glad.h"
#include <GL/freeglut.h>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Vertices{
    float x, y, z;
    float nx, ny, nz;
};

struct Cor_phong{
    float r;
    float g;
    float b;
};

struct DadosET
{
    int Ymax;
    float xMin;//x ataul
    float IncX;

    float zMin;//z atual
    float incZ;

    Vertices nMin; //normal atual
    Vertices incN;
};

struct ET
{
    int yMin, nroNiveis;
    vector<DadosET> *lista;
};

class Phong
{
private:
    Vertices posicao;
    Vertices pos_cam;
    Cor_phong cor_final;
    

public:
    Phong();
    void init(float* pos, float* norm, float* pos_cam);
    void OrdenaPorX(vector<DadosET> *nivel);
    ET* CriaET(vector<Vertices> vertices);
    void scan_line(ET *listaET, Cor_phong cor,float ka, float kd, float ks, Cor_phong cor_amb, Cor_phong cor_difusa, Cor_phong cor_espc);
    void aplicar_shading();

};

#endif