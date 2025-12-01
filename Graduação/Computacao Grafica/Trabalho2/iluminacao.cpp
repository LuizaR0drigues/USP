#include "iluminacao.h"
#include <iostream>

Luz::Luz() { ligada = false; };

void Luz::init(int luz_id, TIPOLUZ tipo_luz)
{
    this->id = luz_id;
    this->tipo = tipo_luz;
    this->ligada = true;
    this->intensidade = 1.0f;
    this->spot_cutoff = 45.0f;
    this->spot_potencia = 0.0f;

    posicao[0] = 0;
    posicao[1] = 5;
    posicao[2] = 0;
    posicao[3] = 1;
    direcao[0] = 0;
    direcao[1] = -1;
    direcao[2] = 0;
}

void Luz::set_cor(float r, float g, float b)
{
    cor[0] = r;
    cor[1] = g;
    cor[2] = b;
    cor[3] = 1.0f;
}

void Luz::set_posicao(float x, float y, float z)
{
    posicao[0] = x;
    posicao[1] = y;
    posicao[2] = z;
    if (tipo == DIRECIONAL)
        posicao[3] = 0.0f;
    else
        posicao[3] = 1.0f;
}

void Luz::set_direcao(float x, float y, float z)
{
    direcao[0] = x;
    direcao[1] = y;
    direcao[2] = z;
}

void Luz::set_Spot_configuracao(float cutoff, float potencia)
{
    this->spot_cutoff = cutoff;
    this->spot_potencia = potencia;
}

void Luz::set_intensidade(float intensidade)
{
    this->intensidade = intensidade;
}

void Luz::atualizar()
{
    if (!ligada)
    {
        glDisable(id);
        return;
    }
    glEnable(id);

    // vetores que serao utilizados
    GLfloat difusa[] = {cor[0] * intensidade, cor[1] * intensidade, cor[2] * intensidade, 1.0f}; // cor difusa
    GLfloat especular[] = {cor[0], cor[1], cor[2], 1.0f};                                        // cor especular
    GLfloat ambiente[] = {cor[0] * intensidade * 0.2f, cor[1] * intensidade * 0.2f, cor[2] * intensidade * 0.2f, 1.0f};

    glLightfv(id, GL_POSITION, posicao);
    glLightfv(id, GL_DIFFUSE, difusa);
    glLightfv(id, GL_SPECULAR, especular);
    glLightfv(id, GL_AMBIENT, ambiente);

    if (tipo == SPOT)
    {
        glLightfv(id, GL_SPOT_DIRECTION, direcao);
        glLightf(id, GL_SPOT_CUTOFF, spot_cutoff);     // angulo de abertura
        glLightf(id, GL_SPOT_EXPONENT, spot_potencia); // foco
    }
    else if(tipo == DIRECIONAL){
        glLightf(id, GL_SPOT_CUTOFF, 180.0f);//desativa o spot
    }
    else{
        //fatores de atenuação da luz
        glLightf(id, GL_CONSTANT_ATTENUATION, 1.0f);
        glLightf(id, GL_LINEAR_ATTENUATION, 0.1f);
        glLightf(id, GL_QUADRATIC_ATTENUATION, 0.01f);
    }
}

void Luz::desenha(){
    if(ligada)
        desenha_esfera();
    
}

void Luz::ligar(){
    ligada = true;
    atualizar();
}

void Luz::desligar(){
    ligada = false;
    atualizar();
}