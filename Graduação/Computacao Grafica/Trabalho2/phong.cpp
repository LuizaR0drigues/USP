#include "phong.h"
#include <glm/glm.hpp>
Phong::Phong() {}
void Phong::init(float* pos_luz, float* norms, float* pos_camera)
{
    this->posicao.x = pos_luz[0];
    this->posicao.y = pos_luz[1];
    this->posicao.z = pos_luz[2];

    if (norms == nullptr)
    {
        this->posicao.nx = 0;
        this->posicao.ny = 0;
        this->posicao.nz = 1;
    }
    this->posicao.nx = norms[0];
    this->posicao.ny = norms[1];
    this->posicao.nz = norms[2];

    this->pos_cam.x = pos_camera[0];
    this->pos_cam.y = pos_camera[1];
    this->pos_cam.z = pos_camera[2];

    //adotar o padrao pra camera
    this->posicao.nx = 0;
    this->posicao.ny = 0;
    this->posicao.nz = 1;

    //inicialmente, branca
    this->cor_final.r = 1.0f;
    this->cor_final.g = 1.0f;
    this->cor_final.b = 1.0f;
}
void Phong::OrdenaPorX(vector<DadosET> *nivel)
{
    sort(nivel->begin(), nivel->end(),
         [](const DadosET &a, const DadosET &b)
         {
             return a.zMin < b.zMin;
         });
}

ET *Phong::CriaET(vector<Vertices> vertices)
{
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

    ET *listaET = new ET();
    listaET->yMin = yMinInt;
    listaET->nroNiveis = nroNiveis;
    listaET->lista = new vector<DadosET>[nroNiveis];

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
        if ((int)ver1.y == (int)ver2.y)//ignora as arestas horizontais
        {
            continue;
        }
        //geometria
        int indice = ceil(ver1.y) - listaET->yMin;
        float dy = ver2.y - ver1.y;
        float dx = ver2.x - ver1.x;
        float incX =  dx/dy;

        float dz = ver2.z - ver1.z; //variação em z
        float z_inc = dz/dy; 

        //diff de normais por linha
        float dnx = ver2.nx - ver1.nx;
        float dny = ver2.ny - ver1.ny;
        float dnz = ver2.nz - ver1.nz;

        Vertices incNorms;
        incNorms.x  =  dnx/dy;
        incNorms.y  =  dny/dy;
        incNorms.z  =  dnz/dy;

        //preenche a nova et
        DadosET novo_dado;
        novo_dado.Ymax = ver2.y;
        novo_dado.xMin = ver1.x;
        novo_dado.IncX = incX;
        novo_dado.zMin = ver1.z;
        novo_dado.incZ = z_inc;

        //normal inicial eh a do vertice de baixo
        novo_dado.nMin.x = ver1.nx;
        novo_dado.nMin.y = ver1.ny;
        novo_dado.nMin.z = ver1.nz;
        novo_dado.incN = incNorms;

        //adiciona todas as info na lista
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

void Phong::scan_line(ET *listaET, Cor_phong cor, float ka, float kd, float ks, Cor_phong cor_amb, Cor_phong cor_difusa, Cor_phong cor_espc)
{
    // define cor
    glColor3f(cor.r, cor.g, cor.b);
    glPointSize(1.0f);

    // inicializa o desenho
    glBegin(GL_POINTS);
    float LAMB, LDIF, LESP;
    vector<DadosET> listaAET;
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
            listaAET[j].zMin +=  listaAET[j].incZ;
            listaAET[j].incN.nx +=  listaAET[j].incN.nx;
            listaAET[j].incN.ny +=  listaAET[j].incN.ny;
            listaAET[j].incN.nz +=  listaAET[j].incN.nz;
        }
        // Move todos os dados do nível pra lista AET
        listaAET.insert(listaAET.end(),
                        make_move_iterator(listaET->lista[i].begin()),
                        make_move_iterator(listaET->lista[i].end()));
        // Limpa o nível original
        listaET->lista[i].clear();
        // Reordena a lista
        OrdenaPorX(&listaAET);

        for(int j=0; j< listaAET.size(); j+=2)
        {
            DadosET esquerda =  listaAET[j];
            DadosET direita = listaAET[j+1];

            float dx = direita.xMin - esquerda.xMin;
            if(dx == 0) dx = 1;
            float dz = direita.zMin - esquerda.zMin;

            float dnx = direita.nMin.nx - esquerda.nMin.nx;
            float dny = direita.nMin.ny - esquerda.nMin.ny;
            float dnz = direita.nMin.nz - esquerda.nMin.nz;

            //incrementos horizontais
            float stepZ = dz/dx;
            float stepNx = dnx / dx;
            float stepNy = dny / dx;
            float stepNz = dnz / dx;
            
            //acumuladores
            float acu_Z = esquerda.zMin;
            float acu_Nx = esquerda.nMin.nx;
            float acu_Ny = esquerda.nMin.ny;
            float acu_Nz = esquerda.nMin.nz;
            
           
            for(int x=(int)esquerda.xMin; x<(int)direita.xMin; x++){
                //normalizando o vetor
                glm::vec3 vetor_n = {acu_Nx, acu_Ny, acu_Nz};
                glm::vec3 normalizado  = glm::normalize(vetor_n);
                
                //calculo da iluminacao (destino - origem)
                float lx = posicao.x - x;
                float ly = posicao.y - yNivel;
                float lz = posicao.z - acu_Z;

                glm::vec3 luz = {lx, ly, lz};
                glm::vec3 luz_norm = glm::normalize(luz);

                //vetor visao/cam
                float vx = pos_cam.x - x;
                float vy = pos_cam.y - yNivel;
                float vz = pos_cam.z - acu_Z;

                glm::vec3 cam = {vx, vy, vz};
                glm::vec3 cam_norm = glm::normalize(cam);

                //produto escalar
                float  prod = glm::dot(normalizado, luz_norm);

                // Variáveis de intensidade
                float fatorDifuso = 0.0f;
                float fatorEspecular = 0.0f;
                if(prod > 0){
                    fatorDifuso = prod;

                    //vetor reflexo
                    glm::vec3 reflexo = (2.0f * prod) * normalizado - luz_norm;
                    reflexo = glm::normalize(reflexo);

                    //especular
                    float RprodV = glm::dot(reflexo, cam_norm);
                    if(RprodV > 0.0f){
                        fatorEspecular = pow(RprodV, 10.0f);//define brilho
                    }
                }
                //euqações de luz
                //componente do ambiente
                float rfinal =  ka *  cor_amb.r;
                float gfinal =  ka *  cor_amb.g;
                float bfinal =  ka *  cor_amb.b;

                //componente difusa
                rfinal += ks * fatorEspecular * cor_espc.r;
                gfinal += ks * fatorEspecular * cor_espc.g;
                bfinal += ks * fatorEspecular * cor_espc.b;

                //limita entre 0 e 1
                if(rfinal > 1.0f) rfinal = 1.0f;
                if(gfinal > 1.0f) gfinal = 1.0f;
                if(bfinal > 1.0f) bfinal = 1.0f;

                // Desenha o Pixel
                glColor3f(rfinal, gfinal, bfinal);
                glVertex3f(x, yNivel, acu_Z);

                //atualiza os valores
                acu_Z += stepZ;
                acu_Nx += stepNx;
                acu_Ny += stepNy;
                acu_Nz += stepNz;
            }
        }
    }
    glEnd();
}