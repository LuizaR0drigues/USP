#include "piramide.h"
#include <iostream>

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
void Piramide::calcNormalFace(VerticesPhong v1, VerticesPhong v2, VerticesPhong v3, float& nx, float& ny, float& nz) {
    // Vetores U (v2 - v1) e V (v3 - v1)
    float ux = v2.x - v1.x; float uy = v2.y - v1.y; float uz = v2.z - v1.z;
    float vx = v3.x - v1.x; float vy = v3.y - v1.y; float vz = v3.z - v1.z;

    // Produto Vetorial
    nx = (uy * vz) - (uz * vy);
    ny = (uz * vx) - (ux * vz);
    nz = (ux * vy) - (uy * vx);

    // Normalização
    float len = sqrt(nx * nx + ny * ny + nz * nz);
    if (len > 0.0f) { nx /= len; ny /= len; nz /= len; }
}
 vector<vector<VerticesPhong>> Piramide::gera_malhas(){
    vector<vector<VerticesPhong>> todas_faces;
    VerticesPhong v0, v1, v2;
    vector<VerticesPhong> face_atual;
    for(int i=0; i<4; i++){

        int idx0 = faces[i][0];
        int idx1 = faces[i][1];
        int idx2 = faces[i][2];

        v0.x = vertices[idx0][0];
        v0.y = vertices[idx0][1];
        v0.z = vertices[idx0][2];

        v1.x = vertices[idx1][0];
        v1.y = vertices[idx1][1];
        v1.z = vertices[idx1][2];

        v2.x = vertices[idx2][0];
        v2.y = vertices[idx2][1];
        v2.z = vertices[idx2][2];

        float nx, ny, nz;
        calcNormalFace(v0, v1, v2, nx, ny, nz);

        face_atual.push_back({v0.x, v0.y, v0.z, nx, ny, nz});
        face_atual.push_back({v1.x, v1.y, v1.z, nx, ny, nz});
        face_atual.push_back({v2.x, v2.y, v2.z, nx, ny, nz});
        todas_faces.push_back(face_atual);
        
    }
    return todas_faces;

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
        calcula_normal(v0, v1, v2, normal);

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
