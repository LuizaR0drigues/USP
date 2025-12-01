#include "piramide.h"
#include <iostream>
#include <cmath>

Piramide::Piramide() {}

void Piramide::init(int tam)
{
    int v[4][3] = {
        {tam, tam, tam},
        {-tam, -tam, tam},
        {-tam, tam, -tam},
        {tam, -tam, -tam}};

    int f[4][3] = {
        {0, 1, 2},
        {0, 1, 3},
        {0, 2, 3},
        {1, 2, 3}};

    float c[4][3] = {
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f},
        {1.0f, 1.0f, 0.0f}};

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            vertices[i][j] = v[i][j];
            faces[i][j] = f[i][j];
            colors[i][j] = c[i][j];
        }
    }
}

void Piramide::calcula_normal(GLfloat *v1, GLfloat *v2, GLfloat *v3, GLfloat *saida)
{
    // mao direita
    GLfloat U[3] = {v2[0] - v1[0], v2[1] - v1[1], v2[2] - v1[2]};
    GLfloat V[3] = {v3[0] - v1[0], v3[1] - v1[1], v3[2] - v1[2]};

    // produto vetorial
    saida[0] = (U[1] * V[2]) - (U[2] * V[1]); // x
    saida[1] = (U[2] * V[0]) - (U[0] * V[2]); // y
    saida[2] = (U[0] * V[1]) - (U[1] * V[0]); // z

    // normaliza
    GLfloat len = sqrt(saida[0] * saida[0] + saida[1] * saida[1] + saida[2] * saida[2]);
    if (len > 0)
    {
        saida[0] /= len;
        saida[1] /= len;
        saida[2] /= len;
    }
}

void Piramide::draw(float x, float y, float z)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    glBegin(GL_TRIANGLES);

    // percorre as faces
    for (int i = 0; i < 4; i++)
    {
        

        //3 vertices
        int Idx0 = faces[i][0];
        int Idx1 = faces[i][1];
        int Idx2 = faces[i][2];
        //monta os vertices
        float* v0 = vertices[Idx0];
        float* v1 = vertices[Idx1];
        float* v2 = vertices[Idx2];

        GLfloat normal[3];
        calcula_normal(v0, v1, v2, nromal);
        //realiza o desenho, cor e normal
        glNormal3fv(normal);
        glColor3fv(colors[i]);
        glVertex3fv(v0);
        glVertex3fv(v1);
        glVertex3fv(v2);
    }
    glEnd();
    glPopMatrix();
}
