#ifndef PHONG_H
#define PHONG_H
#include "include/glad/glad.h"
#include <GL/freeglut.h>
#include <vector>
#include <cmath>
#include <algorithm>
#include "camera.h"


using namespace std;

struct Cor_phong{
    float r;
    float g;
    float b;
};

struct DadosET_phong
{
    int Ymax;
    float xMin;//x ataul
    float IncX;

    float zMin;//z atual
    float incZ;

    Vertices nMin; //normal atual
    Vertices incN;

    Vertices pViewMin;
    Vertices incPView;
};

struct ET_phong
{
    int yMin, nroNiveis;
    vector<DadosET_phong> *lista;
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
    void OrdenaPorX(vector<DadosET_phong> *nivel);
    ET_phong* CriaET(vector<Vertices> vertices);
    void scan_line(ET_phong *listaET, Cor_phong cor,float ka, float kd, float ks, Cor_phong cor_amb, Cor_phong cor_difusa, Cor_phong cor_espc);
    void aplicar_shading();
    Vertices transf_coord_tela(const Vertices V,  int largura, int altura);

};

#endif