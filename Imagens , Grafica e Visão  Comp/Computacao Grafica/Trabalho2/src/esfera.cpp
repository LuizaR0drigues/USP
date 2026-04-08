#include "esfera.h"
#include <iostream>
#include <cmath>

float pi = M_PI;

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

            glNormal3f(x*zr0, y*zr0, z0);//iluminação --nromal
            glVertex3f(x * zr0*raio, y * zr0*raio, z0*raio);

            glNormal3f(x*zr1, y*zr1, z1);//iluminação -- normal
            glVertex3f(x * zr1*raio, y * zr1*raio, z1*raio);

        }
        glEnd();
    }

    glPopMatrix();
}

vector<vector<VerticesPhong>> Esfera::gera_malhas(float raio, int stacks, int slices) {
    vector<vector<VerticesPhong>> todas_faces;

    for (int i = 0; i< stacks; i++){
        //latitudes da esfera
        float lat0 = pi * (-0.5f + ((float) i)/stacks );
        float z0 = sin(lat0);
        float zr0 = cos(lat0);

        float lat1 = pi * (-0.5f + ((float) (i+1))/stacks );
        float z1 = sin(lat1);
        float zr1 = cos(lat1);

        //desenhando a fatia
        for(int j =0; j< fatias+1; j++)
        {
            float long0 = 2*pi * (float)(j) /fatias;
            float long1 = 2*pi * (float)(j+1) /fatias;

            float x0 = cos(long0);
            float y0 = sin(long0);

            float x1 = cos(long1);
            float y1 = sin(long1);
            vector<VerticesPhong> quad;
            VerticesPhong v;

            //vertice1
            v.nx = x0 * zr0;
            v.ny = y0 * zr0;
            v.nz = z0;

            v.x = v.nx * raio;
            v.y = v.ny * raio;
            v.z = v.nz * raio;

            v.vx = v.x; v.vy = v.y; v.vz = v.z; 
            quad.push_back(v);

            //vertice 2
            v.nx = x1 * zr0;
            v.ny = y1 * zr0;
            v.nz = z0;
            v.x = v.nx * raio;
            v.y = v.ny * raio;
            v.z = v.nz * raio;
            v.vx = v.x; v.vy = v.y; v.vz = v.z;
            quad.push_back(v);

            //vertice 3
            v.nx = x1 * zr1; 
            v.ny = y1 * zr1; 
            v.nz = z1;
            v.x = v.nx * raio; 
            v.y = v.ny * raio; 
            v.z = v.nz * raio;
            v.vx = v.x; v.vy = v.y; v.vz = v.z;
            quad.push_back(v);

            //vertice 4
            v.nx = x0 * zr1; 
            v.ny = y0 * zr1; 
            v.nz = z1;
            v.x = v.nx * raio; 
            v.y = v.ny * raio; 
            v.z = v.nz * raio;

            v.vx = v.x; v.vy = v.y; v.vz = v.z;
            quad.push_back(v);

            todas_faces.push_back(quad);
            

        }
        
    }
    return todas_faces;
}