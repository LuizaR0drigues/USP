#ifndef ILUMINACAO_H
#define ILUMINACAO_H

#include "glad/glad.h"
#include <GL/freeglut.h>
#include <vector>

enum TIPOLUZ{
    PONTUAL, 
    DIRECIONAL,
    SPOT
};

class Luz
{
private:
    int id;
    TIPOLUZ tipo;

    //propriedades da luz
    GLfloat posicao[4]; //x,y,z,w
    GLfloat cor[4]; //rgba
    GLfloat direcao[3]; //usa no spot

    ///propriedades spot
    float spot_cutoff;
    float spot_potencia;

    //estado
    bool ligada;
    float intensidade;

    void DesenhaEsfera();

public:

    Luz();

    void init(int id_liz, TIPOLUZ tipo_luz);
    void set_cor(float r, float g, float b);
    void set_posicao(float x, float y, float z);
    void set_direcao(float x, float y, float z);
    void set_Spot_configuracao(float cutoff, float potencia);
    void set_intensidade(float intes);
    void atualizar();
    void desenha();
    void ligar();
    void desligar();

};



#endif