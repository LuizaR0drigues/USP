#ifndef PHONG_H
#define PHONG_H

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#include "glad/glad.h"
#include "camera.h"
#include "structs.h"

using namespace std;

struct DadosET_phong
{
    int Ymax;
    float xMin; //x atual
    float IncX;

    float zMin; //z atual
    float incZ;

    VerticesPhong nMin;
    VerticesPhong incN;

    VerticesPhong pViewMin;
    VerticesPhong incPView;
};

struct ET_phong
{
    int yMin, nroNiveis;
    vector<DadosET_phong> *lista;
};

class Phong
{
private:
    VerticesPhong posicao;
    VerticesPhong pos_cam;
    Color cor_final;    

public:
    Phong();
    void init(float* pos, float* norm, float* pos_cam);
    void OrdenaPorX(vector<DadosET_phong> *nivel);
    ET_phong* CriaET(vector<VerticesPhong> vertices);
    void scan_line(ET_phong *listaET, Color cor,float ka, float kd, float ks, 
        Color cor_amb, Color cor_difusa, Color cor_espc);
    void aplicar_shading();
    VerticesPhong transf_coord_tela(const VerticesPhong V,  int largura, int altura);

};

#endif