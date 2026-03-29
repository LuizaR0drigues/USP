#ifndef STRUCTS_H
#define STRUCTS_H

#include <vector>

using namespace std;

struct Ponto
{
    float x, y;
};

struct Color
{
    float r, g, b;
};

struct DadosET
{
    float yMax;
    float xMin;
    float incX;
};

struct ET
{
    int yMin, nroNiveis;
    vector<DadosET> *lista;
};

struct Poligono
{
    vector<Ponto> vertices;
    Color corPrenchimento;
    Color cor_Contorno;
    float espessura;
};

struct VerticesPhong{
    float x, y, z;
    float nx, ny, nz;

    //posicao real
    float vx, vy, vz;
};

#endif