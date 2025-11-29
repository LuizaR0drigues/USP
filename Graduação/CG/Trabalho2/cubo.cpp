#include "cubo.h"
#include <iostream>


Cubo::Cubo(){}
void Cubo::init(int tam){
    float h = tam/2;
    //vertices
    float v[8][3] = {
        {-h, -h, -h},
        {h, -h, -h},
        {h, h, -h},
        {-h, h, -h},
        {-h, -h, h},
        {h, -h, h},
        {h, h, h},
        {-h, h, h}
    };
    //faces
    int f[6][4]=  {
        {0,1,2,3},
        {4,5,6,7},
        {0,1,5,4},
        {2,3,7,6},
        {1,2,6,5},
        {0,3,7,4}
    };
    //cores
    float c[6][3] = {
        {1.0f,0.0f,0.0f},
        {0.0f,1.0f,0.0f},
        {0.0f,0.0f,1.0f},
        {0.0f,1.0f,1.0f},
        {1.0f,0.0f,1.0f},
        {1.0f,0.5f,0.0f}
    };

    for(int i=0; i< 8; i++){
        for(int j=0; j<3; j++){
            vertices[i][j] = v[i][j];
        }
    }

    for(int i=0; i<6; i++){
        for(int j=0; j< 4; j++)
        {
            faces[i][j] = f[i][j];
        }
        for(int j=0; j<3; j++)
        {
            colors[i][j] = c[i][j];
        }
    }
}

void Cubo::draw(float x, float y, float z)
{
    glPushMatrix();
    glTranslatef(x,y,z);
    glBegin(GL_QUADS);
    for (int i=0; i<6; i++){
        glColor3fv(colors[i]);//define a cor por face
        for(int j=0; j<4; j++){//realiza o desenho das 4 vertices de cada face
            int vertexIdx = faces[i][j];
            glVertex3fv(vertices[vertexIdx]);
        }
    }
    glEnd();
    glPopMatrix();
    
}