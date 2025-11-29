#include "esfera.h"
#include <iostream>
#include <cmath>
Esfera::Esfera(){
    raio = 5.0f;
    fatias = 20;
    stacks = 20;

}

void Esfera::init(float Inputraio, int Inputfatias, int Inputstacks){
    this->raio = Inputraio;
    this->fatias = Inputfatias;
    this->stacks = Inputstacks;
}

void Esfera::draw(float xe, float ye, float ze){
   
    glPushMatrix();
    glTranslatef(xe,ye,ze);

    float pi = M_PI;
    
    for (int i = 0; i< stacks; i++){
        //latitudes da esfera
        float lat0 = pi * (-0.5f + ((float) i)/stacks );
        float z0 = sin(lat0);
        float zr0 = cos(lat0);

        float lat1 = pi * (-0.5f + ((float) (i+1))/stacks );
        float z1 = sin(lat1);
        float zr1 = cos(lat1);

        //desenhando a fatia
        glBegin(GL_QUAD_STRIP);
        for(int j =0; j< fatias+1; j++)
        {
            float longi = 2*pi * (float)(j) /fatias;
            float x = cos(longi);
            float y = sin(longi);

            glColor3f((float)j/fatias, (float)i/fatias, 1.0f - (float)(i/fatias));

            glNormal3f(x*zr0, y*zr0, z0);//iluminação
            glVertex3f(x * zr0*raio, y * zr0*raio, z0*raio);

            glNormal3f(x*zr1, y*zr1, z1);//iluminação
            glVertex3f(x * zr1*raio, y * zr1*raio, z1*raio);

        }
        glEnd();
    }

    glPopMatrix();
}