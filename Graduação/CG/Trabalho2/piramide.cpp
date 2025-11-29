#include "piramide.h"
#include <iostream>

Piramide::Piramide(){}

void Piramide::init(){
    int v[4][3] ={
        {1,1,1},
        {-1,-1,1},
        {-1,1,-1},
        {1,-1,-1}
    };

    int f[4][3]={
        {0,1,2},
        {0,1,3},
        {0,2,3},
        {1,2,3}
    };

    float c[4][3] = {
        {1.0f,0.0f,0.0f},
        {0.0f,1.0f,0.0f},
        {0.0f,0.0f,1.0f},
        {1.0f,1.0f,0.0f}
    };

    for(int i=0; i< 4; i++){
        for(int j=0; j<3; j++){
            vertices[i][j] = v[i][j];
            faces[i][j] = f[i][j];
            colors[i][j] = c[i][j];
        }
    }

    
}
void Piramide::draw(float x, float y, float z)
{
    glPushMatrix();
    glTranslatef(x,y,z);
    glBegin(GL_TRIANGLES);

    for (int i=0; i<4; i++){
        glColor3fv(colors[i]);//define a cor por face
        for(int j=0; j<3; j++){//realiza o desenho das 3 vertices de cada face
            int vertexIdx = faces[i][j];
            glVertex3fv(vertices[vertexIdx]);
        }
    }

    glPopMatrix();
    glEnd();
}
