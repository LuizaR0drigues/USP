#ifndef ILUMINACAO_H
#define ILUMINACAO_H

#include "include/glad/glad.h"
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

    void desenha_esfera(){
        glPushMatrix();
        glTranslatef(posicao[0], posicao[1], posicao[2]);
        
        GLfloat material_cor[] = {cor[0], cor[1], cor[2], 1.0f};
        glMaterialfv(GL_FRONT, GL_EMISSION, material_cor); // parecer que brilha
        
        //Se for direcional ou spot, desenha linha
        if(tipo != PONTUAL) {
            glEnable(GL_LINE_STIPPLE);
            glLineStipple(1, 0xF0F0);
            glBegin(GL_LINES);
            glVertex3f(0,0,0);
            //linha apontando a direção
            glVertex3f(direcao[0]*2, direcao[1]*2, direcao[2]*2); 
            glEnd();
            glDisable(GL_LINE_STIPPLE);
        }

        //Esfera pequena
        GLUquadric* q = gluNewQuadric();
        gluSphere(q, 0.3, 10, 10);
        gluDeleteQuadric(q);
        
        // Reseta emissão para preto (para não afetar outros objetos)
        GLfloat sem_cor[] = {0,0,0,1};
        glMaterialfv(GL_FRONT, GL_EMISSION, sem_cor);

        glPopMatrix();
    };

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