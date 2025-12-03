#include "cubo.h"
#include <iostream>

Cubo::Cubo() {}
void Cubo::init(int tam)
{
    float h = tam / 2;
    // vertices
    float v[8][3] = {
        {-h, -h, -h},
        {h, -h, -h},
        {h, h, -h},
        {-h, h, -h},
        {-h, -h, h},
        {h, -h, h},
        {h, h, h},
        {-h, h, h}};
    // faces
    int f[6][4] = {
        {0, 1, 2, 3}, // frontal
        {1, 5, 6, 2}, // direita
        {5, 4, 7, 6}, // tras
        {4, 0, 3, 7}, // esq
        {3, 2, 6, 7}, // sup
        {4, 5, 1, 0}  // inferio
    };
    // cores
    float c[6][3] = {
        {1.0f,0.0f,0.0f},
        {0.0f,1.0f,0.0f},
        {0.0f,0.0f,1.0f},
        {0.0f,1.0f,1.0f},
        {1.0f,0.0f,1.0f},
        {1.0f,0.5f,0.0f}
    };


    // normais
    float n[6][3] =
        {
            {0, 0, -1},
            {1, 0, 0},
            {0, 0, 1},
            {-1, 0, 0},
            {0, 1, 0},
            {0, -1, 0}
        };

    
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            vertices[i][j] = v[i][j];
        }
    }

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            faces[i][j] = f[i][j];
        }
        for (int j = 0; j < 3; j++)
        {
             normais[i][j] = n[i][j];
             colors[i][j] = c[i][j];
        }
    }
   
    
}
//funcao que vai auxiliar no metodo de phong
vector<vector<VerticesPhong>> Cubo::gera_malhas(float tamanho){
    
    vector<vector<VerticesPhong>> todasFaces;
    float t = tamanho / 2.0f; // 't' é a distância do centro até a borda

    vector<VerticesPhong> frente;
    frente.push_back({ -t, -t,  t,   0.0f, 0.0f, 1.0f }); // Inferior Esq
    frente.push_back({  t, -t,  t,   0.0f, 0.0f, 1.0f }); // Inferior Dir
    frente.push_back({  t,  t,  t,   0.0f, 0.0f, 1.0f }); // Superior Dir
    frente.push_back({ -t,  t,  t,   0.0f, 0.0f, 1.0f }); // Superior Esq
    todasFaces.push_back(frente);

    vector<VerticesPhong> direita;
    direita.push_back({  t, -t,  t,   1.0f, 0.0f, 0.0f }); // Frente Baixo
    direita.push_back({  t, -t, -t,   1.0f, 0.0f, 0.0f }); // Tras Baixo
    direita.push_back({  t,  t, -t,   1.0f, 0.0f, 0.0f }); // Tras Cima
    direita.push_back({  t,  t,  t,   1.0f, 0.0f, 0.0f }); // Frente Cima
    todasFaces.push_back(direita);

    vector<VerticesPhong> tras;
    tras.push_back({  t, -t, -t,   0.0f, 0.0f, -1.0f }); // Inferior Dir (visto de tras)
    tras.push_back({ -t, -t, -t,   0.0f, 0.0f, -1.0f }); // Inferior Esq
    tras.push_back({ -t,  t, -t,   0.0f, 0.0f, -1.0f }); // Superior Esq
    tras.push_back({  t,  t, -t,   0.0f, 0.0f, -1.0f }); // Superior Dir
    todasFaces.push_back(tras);

    vector<VerticesPhong> esquerda;
    esquerda.push_back({ -t, -t, -t,  -1.0f, 0.0f, 0.0f }); // Tras Baixo
    esquerda.push_back({ -t, -t,  t,  -1.0f, 0.0f, 0.0f }); // Frente Baixo
    esquerda.push_back({ -t,  t,  t,  -1.0f, 0.0f, 0.0f }); // Frente Cima
    esquerda.push_back({ -t,  t, -t,  -1.0f, 0.0f, 0.0f }); // Tras Cima
    todasFaces.push_back(esquerda);

    vector<VerticesPhong> topo;
    topo.push_back({ -t,  t,  t,   0.0f, 1.0f, 0.0f }); // Frente Esq
    topo.push_back({  t,  t,  t,   0.0f, 1.0f, 0.0f }); // Frente Dir
    topo.push_back({  t,  t, -t,   0.0f, 1.0f, 0.0f }); // Tras Dir
    topo.push_back({ -t,  t, -t,   0.0f, 1.0f, 0.0f }); // Tras Esq
    todasFaces.push_back(topo);

    vector<VerticesPhong> base;
    base.push_back({ -t, -t, -t,   0.0f, -1.0f, 0.0f }); // Tras Esq
    base.push_back({  t, -t, -t,   0.0f, -1.0f, 0.0f }); // Tras Dir
    base.push_back({  t, -t,  t,   0.0f, -1.0f, 0.0f }); // Frente Dir
    base.push_back({ -t, -t,  t,   0.0f, -1.0f, 0.0f }); // Frente Esq
    todasFaces.push_back(base);

    return todasFaces;

}
void Cubo::draw(float x, float y, float z)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    glBegin(GL_QUADS);

    for (int i = 0; i < 6; i++)
    {
        glColor3fv(colors[i]); // define a cor por face
        glNormal3fv(normais[i]);//normal por face
        for (int j = 0; j < 4; j++)
        { // realiza o desenho das 4 vertices de cada face
            int vertexIdx = faces[i][j];
            glVertex3fv(vertices[vertexIdx]);
        }
    }
    glEnd();
    glPopMatrix();
}