#include "phong.h"
#include <glm/glm.hpp>
Phong::Phong() {}
void Phong::init(float *pos_luz, float *norms, float *pos_camera)
{
    // posicao da fonte de luz
    if (pos_luz != nullptr)
    {
        this->posicao.x = pos_luz[0];
        this->posicao.y = pos_luz[1];
        this->posicao.z = pos_luz[2];
    }
    else
    {
        this->posicao.x = this->posicao.y = 0.0f;
        this->posicao.z = 1.0f;
    }
    // normais
    if (norms == nullptr)
    {
        this->posicao.nx = 0;
        this->posicao.ny = 0;
        this->posicao.nz = 1;
    }
    else
    {
        this->posicao.nx = norms[0];
        this->posicao.ny = norms[1];
        this->posicao.nz = norms[2];
    }
    // posicao da camera
    if (pos_camera != nullptr)
    {
        this->pos_cam.x = pos_camera[0];
        this->pos_cam.y = pos_camera[1];
        this->pos_cam.z = pos_camera[2];
    }
    else
    {
        this->pos_cam.x = this->pos_cam.y = 0.0f;
        this->pos_cam.z = 1.0f;
    }

    // inicialmente, branca
    this->cor_final.r = 1.0f;
    this->cor_final.g = 1.0f;
    this->cor_final.b = 1.0f;
}
void Phong::OrdenaPorX(vector<DadosET_phong> *nivel)
{
    sort(nivel->begin(), nivel->end(),
         [](const DadosET_phong &a, const DadosET_phong &b)
         {
             return a.xMin < b.xMin;
         });
}

ET_phong *Phong::CriaET(vector<Vertices> vertices)
{
    if (vertices.empty())
        return nullptr;

    float yMin = numeric_limits<float>::max();
    float yMax = numeric_limits<float>::min();
    for (auto &ver : vertices)
    {
        if (ver.y < yMin)
            yMin = ver.y;

        if (ver.y > yMax)
            yMax = ver.y;
    }

    int yMinInt = static_cast<int>(ceil(yMin));
    int yMaxInt = static_cast<int>(floor(yMax));
    int nroNiveis = yMaxInt - yMinInt;

    if (nroNiveis <= 0 || nroNiveis > 5000)
    {
        return nullptr;
    }

    ET_phong *listaET = new ET_phong();
    listaET->yMin = yMinInt;
    listaET->nroNiveis = nroNiveis;
    listaET->lista = new vector<DadosET_phong>[nroNiveis];

    size_t n = vertices.size();
    for (size_t i = 0; i < n; i++)
    {
        Vertices ver1 = vertices[i];
        Vertices ver2 = vertices[(i + 1) % n];
        ;

        if (ver1.y > ver2.y)
        {
            swap(ver1, ver2);
        }
        if ((int)ver1.y == (int)ver2.y) // ignora as arestas horizontais
        {
            continue;
        }
        // geometria
        int indice = ceil(ver1.y) - listaET->yMin;

        if (indice < 0 || indice >= listaET->nroNiveis)
        {
            continue; // Se o índice for inválido, pula essa aresta para não travar
        }
        float dy = ver2.y - ver1.y;
        float dx = ver2.x - ver1.x;
        float incX = dx / dy;

        float dz = ver2.z - ver1.z; // variação em z
        float z_inc = dz / dy;

        // diff de normais por linha
        float dnx = ver2.nx - ver1.nx;
        float dny = ver2.ny - ver1.ny;
        float dnz = ver2.nz - ver1.nz;

        // dados de interpolação
        float dvx = ver2.vx - ver1.vx;
        float dvy = ver2.vy - ver1.vy;
        float dvz = ver2.vz - ver1.vz;

        Vertices incView;
        incView.vx = dvx / dy;
        incView.vy = dvy / dy;
        incView.vz = dvz / dy;

        Vertices incNorms;
        incNorms.x = dnx / dy;
        incNorms.y = dny / dy;
        incNorms.z = dnz / dy;

        // preenche a nova et
        DadosET_phong novo_dado;
        novo_dado.Ymax = ver2.y;
        novo_dado.xMin = ver1.x;
        novo_dado.IncX = incX;
        novo_dado.zMin = ver1.z;
        novo_dado.incZ = z_inc;
        // inicializa com o vertice 1
        novo_dado.pViewMin.x = ver1.vx;
        novo_dado.pViewMin.y = ver1.vy;
        novo_dado.pViewMin.z = ver1.vz;
        novo_dado.incPView = incView;
        // normal inicial eh a do vertice de baixo
        novo_dado.nMin.x = ver1.nx;
        novo_dado.nMin.y = ver1.ny;
        novo_dado.nMin.z = ver1.nz;
        novo_dado.incN = incNorms;

        // adiciona todas as info na lista
        listaET->lista[indice].push_back(novo_dado);
    }

    for (int i = 0; i < listaET->nroNiveis; i++)
    {
        if (!listaET->lista[i].empty())
        {
            OrdenaPorX(&(listaET->lista[i]));
        }
    }

    return listaET;
}

void Phong::scan_line(ET_phong *listaET, Cor_phong cor, float ka, float kd, float ks, Cor_phong cor_amb, Cor_phong cor_difusa, Cor_phong cor_espc)
{
    if (!listaET || listaET->nroNiveis <= 0 || listaET->lista == nullptr)
        return;

    // define cor
    glColor3f(cor.r, cor.g, cor.b);
    glPointSize(1.0f);

    // inicializa o desenho
    glBegin(GL_POINTS);
    vector<DadosET_phong> listaAET;
    for (int i = 0; i < listaET->nroNiveis; i++)
    {
        int yNivel = i + listaET->yMin;
        for (int j = 0; j < (int)listaAET.size(); j++)
        {
            // Se a iteração está no nível ou acima do y máximo da aresta
            if (listaAET[j].Ymax <= yNivel)
            {
                // Remove ela
                listaAET.erase(listaAET.begin() + j);
                j--;
                continue;
            }

            listaAET[j].xMin += listaAET[j].IncX;
            listaAET[j].zMin += listaAET[j].incZ;

            listaAET[j].nMin.nx += listaAET[j].incN.nx;
            listaAET[j].nMin.ny += listaAET[j].incN.ny;
            listaAET[j].nMin.nz += listaAET[j].incN.nz;

            listaAET[j].pViewMin.x += listaAET[j].incPView.vx;
            listaAET[j].pViewMin.y += listaAET[j].incPView.vy;
            listaAET[j].pViewMin.z += listaAET[j].incPView.vz;
        }
        // Move todos os dados do nível pra lista AET
        listaAET.insert(listaAET.end(),
                        make_move_iterator(listaET->lista[i].begin()),
                        make_move_iterator(listaET->lista[i].end()));
        // Limpa o nível original
        listaET->lista[i].clear();
        // Reordena a lista
        OrdenaPorX(&listaAET);

        for (int j = 0; j + 1 < (int)listaAET.size(); j += 2)
        {
            DadosET_phong esquerda = listaAET[j];
            DadosET_phong direita = listaAET[j + 1];

            float dx = direita.xMin - esquerda.xMin;
            if (dx == 0)
                continue;
            float dz = direita.zMin - esquerda.zMin;

            float dnx = direita.nMin.nx - esquerda.nMin.nx;
            float dny = direita.nMin.ny - esquerda.nMin.ny;
            float dnz = direita.nMin.nz - esquerda.nMin.nz;
            float dvx = direita.pViewMin.x - esquerda.pViewMin.x;
            float dvy = direita.pViewMin.y - esquerda.pViewMin.y;
            float dvz = direita.pViewMin.z - esquerda.pViewMin.z;

            // incrementos horizontais
            float stepZ = dz / dx;
            float stepNx = dnx / dx;
            float stepNy = dny / dx;
            float stepNz = dnz / dx;
            float stepVx = dvx / dx;
            float stepVy = dvy / dx;
            float stepVz = dvz / dx;

            // acumuladores
            float acu_Z = esquerda.zMin;
            float acu_Nx = esquerda.nMin.nx;
            float acu_Ny = esquerda.nMin.ny;
            float acu_Nz = esquerda.nMin.nz;
            float acu_vx = esquerda.pViewMin.x;
            float acu_vy = esquerda.pViewMin.y;
            float acu_vz = esquerda.pViewMin.z;

            for (int x = (int)esquerda.xMin; x < (int)direita.xMin; x++)
            {
                // normalizando o vetor
                glm::vec3 vetor_n = {acu_Nx, acu_Ny, acu_Nz};
                glm::vec3 normalizado = glm::normalize(vetor_n);

                // calculo da iluminacao (destino - origem)
                float lx = posicao.x - acu_vx;
                float ly = posicao.y - acu_vy;
                float lz = posicao.z - acu_vz;

                glm::vec3 luz = {lx, ly, lz};
                glm::vec3 luz_norm = glm::normalize(luz);

                // vetor visao/cam
                float vx = 0.0f - acu_vx;
                float vy = 0.0f - acu_vy;
                float vz = 0.0f - acu_vz;

                glm::vec3 cam = {vx, vy, vz};
                glm::vec3 cam_norm = glm::normalize(cam);

                // produto escalar
                float prod = abs(glm::dot(normalizado, luz_norm));

                // Variáveis de intensidade
                float fatorDifuso = 0.0f;
                float fatorEspecular = 0.0f;
                if (prod > 0)
                {
                    fatorDifuso = prod;

                    // vetor reflexo
                    glm::vec3 reflexo = (2.0f * prod) * normalizado - luz_norm;
                    reflexo = glm::normalize(reflexo);

                    // especular
                    float RprodV = glm::dot(reflexo, cam_norm);
                    if (RprodV > 0.0f)
                    {
                        fatorEspecular = pow(RprodV, 4.0f); // define brilho
                    }
                }
                // euqações de luz
                // componente do ambiente
                float rfinal = ka * cor_amb.r * cor.r;
                float gfinal = ka * cor_amb.g * cor.g;
                float bfinal = ka * cor_amb.b * cor.b;

                // componente difusa
                rfinal += kd * fatorDifuso * cor_difusa.r * cor.r;
                gfinal += kd * fatorDifuso * cor_difusa.g * cor.g;
                bfinal += kd * fatorDifuso * cor_difusa.b * cor.b;
                // componente especular
                rfinal += ks * fatorEspecular * cor_espc.r ;
                gfinal += ks * fatorEspecular * cor_espc.g ;
                bfinal += ks * fatorEspecular * cor_espc.b ;

                // limita entre 0 e 1
                if (rfinal > 1.0f)
                    rfinal = 1.0f;
                if (gfinal > 1.0f)
                    gfinal = 1.0f;
                if (bfinal > 1.0f)
                    bfinal = 1.0f;

                // Desenha o Pixel
                glColor3f(rfinal, gfinal, bfinal);
                glVertex3f(x, yNivel, acu_Z);

                // atualiza os valores
                acu_Z += stepZ;
                acu_Nx += stepNx;
                acu_Ny += stepNy;
                acu_Nz += stepNz;
                acu_vx += stepVx;
                acu_vy += stepVy;
                acu_vz += stepVz;
            }
        }
    }
    glEnd();
}
