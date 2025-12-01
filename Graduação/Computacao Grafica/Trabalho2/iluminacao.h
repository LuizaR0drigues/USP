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
        if(!ligada) return;

        glPushMatrix();
        glTranslatef(posicao[0], posicao[1], posicao[2]);
        glDisable(GL_LIGHTING);
        glColor3f(cor[0], cor[1], cor[2]);

        
        //Se for direcional ou spot, desenha linha
        if(tipo != PONTUAL) {
            glEnable(GL_LINE_STIPPLE);
            glLineStipple(1, 0xF0F0);
            
            glBegin(GL_LINES);
            glVertex3f(0,0,0);
            glVertex3f(direcao[0]*3, direcao[1]*3, direcao[2]*3); 
            glEnd();
            
            glDisable(GL_LINE_STIPPLE);
            glColor3f(cor[0], cor[1], cor[2]);
        }

        //Esfera pequena
        GLUquadric* q = gluNewQuadric();
        gluSphere(q, 1, 15, 15);
        gluDeleteQuadric(q);
        
        glEnable(GL_LIGHTING);
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