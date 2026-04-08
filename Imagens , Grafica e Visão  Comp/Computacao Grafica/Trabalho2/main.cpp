//Luís Filipe Silva Forti 14592348
//Luiza Rodrigues Cardoso 14593332

#include <iostream>
#include <vector>
#include <array>
#include <limits>
#include <cmath>
#include <algorithm>
#include <utility>

#include "glad/glad.h"

#include "structs.h"
#include "cubo.h"
#include "esfera.h"
#include "piramide.h"
#include "iluminacao.h"
#include "camera.h"
#include "phong.h"

using namespace std;

//Epsilon para comparações com floats
#define epsilon 0.0001

// objetos e Camera
Camera camera;
Luz luz0; // direcional
Luz luz1; // pontual
Luz luz2; // spot
Phong phong_cor;
// objetos 3d
Cubo cubo;
Esfera esfera;
Piramide piramide;
vector<vector<VerticesPhong>> malha_cubo, malha_esfera, malha_piramide;

// variaves pra definir a janela
const int WINDOW_W = 800, WINDOW_H = 400;
const float ORTHO_MIN_X = -400, ORTHO_MAX_X = 400;
const float ORTHO_MIN_Y = -200, ORTHO_MAX_Y = 200;
int largura_atual = WINDOW_W;
int altura_atual = WINDOW_H;

// fatores de iluminação
float ka = 0.5f; //baixo:mostra mais as sombras
float kd = 0.8f; //a cor ressalta
float ks = 1.0f; //mutio brilho
// Transformações Geomtericas NO OBJETO 3D
float tx = 0.0, ty = 0.0, tz = 0.0;
float rxo = 0.0, ryo = 0.0, rzo = 0.0;
float scaleo = 0.1;

// Lista dinâmica - clique do usuário
vector<Ponto> g_vertices;
// cores
Color cor_preenc = {1.0f, 1.0f, 1.0f};
Color cor_contorno = {1.0f, 0.0f, 0.0f};
float tamanho_linha = 1.0f;

enum menu_opcoes
{
    COR_VERM,
    COR_VERD,
    COR_AZUL,
    COR_BRANCA,
    COR_AMARELO,
    CONTORNO_VERM,
    CONTORNO_VERD,
    CONTORNO_AZUL,
    CONTORNO_BRANCA,
    CONTORNO_AMARELO,
    LINHA_FINA,
    LINHA_MED,
    LINHA_GROSSA,
    LIMPAR_TELA,
    SAIR,
    Orto,
    Perspec,
    VER_OBJT_3D,
    VER_OBJT_2D,
    VER_EXTRUSAO,
    MD_DESENHO,  // trabalho 1
    MD_EXTRUSAO, // extrusao
    MD_OBJT,     // objetos 3d
    GOURAUD,
    FLAT,
    PHONG,
    LUZES,
    ESCURO
};
menu_opcoes modo_atual = MD_DESENHO;
menu_opcoes flagLuz = ESCURO;

void DesenhaVertices3D(vector<Ponto> vertices, float z, Color cor, float grossura)
{
    glPointSize(grossura);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POINTS);

    for (auto vert : vertices)
        glVertex3f(vert.x, vert.y, z);
    glEnd();
}

//Função para desenhar linha simples em 3D
void DesenhaLinha3D(Ponto ponto1, Ponto ponto2, float z, Color cor, float grossura)
{
    glLineWidth(tamanho_linha);
    glColor3f(cor.r, cor.g, cor.b);
    glBegin(GL_LINES);
    
    glVertex3f(ponto1.x, ponto1.y, z);
    glVertex3f(ponto2.x, ponto2.y, z);

    glEnd();
}

//Função para desenhar contorno do polígono plano 3D
void DesenhaContorno3D(vector<Ponto> vertices, float z, Color cor, float grossura)
{
    glLineWidth(grossura);
    glColor3f(cor.r, cor.g, cor.b);
    glBegin(GL_LINE_LOOP);
    
    for (auto vert : vertices)
        glVertex3f(vert.x, vert.y, z);

    glEnd();
}

//Função para ordenar um nível da lista ET por ordem de X crescente
void OrdenaPorX(vector<DadosET> *nivel)
{
    sort(nivel->begin(), nivel->end(),
         [](const DadosET &a, const DadosET &b)
         {
             return a.xMin < b.xMin;
         });
}

//Algoritmo de criação da tabela ET para preenchimento de polígonos 2D
ET *CriaET(vector<Ponto> vertices)
{
    //Coloca o maior valor possível pra yMin e o menor possível pra yMax
    float yMin = numeric_limits<float>::max();
    float yMax = numeric_limits<float>::min();

    //Encontra o menor e maior Y dos vértices
    for (auto &ver : vertices)
    {
        if (ver.y < yMin)
            yMin = ver.y;

        if (ver.y > yMax)
            yMax = ver.y;
    }

    //Como pinta dentro das "linhas reais":
    //yMin arredonda pra cima e yMax arredonda pra baixo
    int yMinInt = static_cast<int>(ceil(yMin));
    int yMaxInt = static_cast<int>(floor(yMax));
    int nroNiveis = yMaxInt - yMinInt;

    //Cria a ET
    ET *listaET = new ET();
    listaET->yMin = yMinInt;
    listaET->nroNiveis = nroNiveis;
    listaET->lista = new vector<DadosET>[nroNiveis];

    //Para cada vértice
    size_t n = vertices.size();
    for (size_t i = 0; i < n; i++)
    {
        //Pega o atual
        Ponto ver1 = vertices[i];
        //Pega o próximo
        //(i+1)%n -> se o atual (i) for o último, pega o primeiro
        Ponto ver2 = vertices[(i + 1) % n];

        //Deixa os vértices em Y crescente
        if (ver1.y > ver2.y)
        {
            swap(ver1, ver2);
        }
        //Se estiverem no mesmo y, a aresta é ignorada
        if ((int)ver1.y == (int)ver2.y)
        {
            continue;
        }

        //Qual a posição na lista da ET (qual o Y inicial)
        int indice = ceil(ver1.y) - listaET->yMin;
        float dy = ver2.y - ver1.y;
        float dx = ver2.x - ver1.x;
        float m = dy / dx;

        //Adiciona os dados da aresta à lista do nível calculado
        listaET->lista[indice].push_back({ver2.y, ver1.x, m});
    }

    //Para cada nível da ET
    for (int i = 0; i < listaET->nroNiveis; i++)
    {
        //Ordena os níveis, para as arestas ficarem com X crescente
        if (!listaET->lista[i].empty())
        {
            OrdenaPorX(&(listaET->lista[i]));
        }
    }

    return listaET;
}

//Algoritmo de preenchimento de polígonos 2D
void PreenchimentoDePoligonos(const ET *listaET, Color cor, float posicaoZ)
{
    // define cor
    glColor3f(cor.r, cor.g, cor.b);
    glPointSize(1.0f);

    // inicializa o desenho
    glBegin(GL_POINTS);

    vector<DadosET> listaAET;
    //Para cada nível na ET
    for (int i = 0; i < listaET->nroNiveis; i++)
    {
        int yNivel = i + listaET->yMin;

        //Para cada aresta na AET
        for (int j = 0; j < (int)listaAET.size(); j++)
        {
            // Se a iteração está no nível ou acima do y máximo da aresta
            if (listaAET[j].yMax <= yNivel)
            {
                // Remove ela
                listaAET.erase(listaAET.begin() + j);
                //Corrige o valor de j, pois listaAET perdeu 1 valor
                j--;
            }
            else
                //Recalcula a posição X do ponto da aresta
                listaAET[j].xMin += 1 / listaAET[j].incX;
        }

        // Move todos os dados do nível pra lista AET
        listaAET.insert(listaAET.end(),
                        make_move_iterator(listaET->lista[i].begin()),
                        make_move_iterator(listaET->lista[i].end()));
        // Reordena a lista AET
        OrdenaPorX(&listaAET);

        //Para a técnica ímpar-par
        int verticesCruzados = 0;
        //Para cada X entre o ponto da aresta mais à esquerda e a mais á direita
        for (int x = listaAET[0].xMin; x < listaAET.back().xMin; x++)
        {
            //Para toda aresta que foi cruzada entre iterações
            while (x >= listaAET[verticesCruzados].xMin)
                verticesCruzados++;

            //Se cruzou um número ímpar
            if (verticesCruzados % 2 == 1)
            {
                glVertex3f(x, yNivel, posicaoZ);
            }
        }
    }
    glEnd();
}

//Converte coordenadas do mouse para coordenadas da janela
Ponto ConverteCoords(int x_mouse, int y_mouse)
{
    int w_janela = glutGet(GLUT_WINDOW_WIDTH);
    int h_janela = glutGet(GLUT_WINDOW_HEIGHT);

    //x_mouse = 0 -> esquerda da janela
    //x_mouse / w_janela -> % da distância entre lado esquerdo e direito
    //(...) * (...) + ... -> converte para coordenadas da janela
    float x_w = ((float)x_mouse / w_janela) * (ORTHO_MAX_X - ORTHO_MIN_X) + ORTHO_MIN_X;
    //y_mouse = 0 -> topo da janela
    //(h_janela - y_mouse) / h_janela -> % da distância entre topo e base, a subtração inverte a posição
    //(...) * (...) + ... -> converte para coordenadas da janela
    float y_w = ((float)(h_janela - y_mouse) / h_janela) * (ORTHO_MAX_Y - ORTHO_MIN_Y) + ORTHO_MIN_Y;

    return {x_w, y_w};
}

//Gerencia os inputs do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
    // Se clicou com botão ESQUERDO e apertou (GLUT_DOWN)
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        //Converte de coordenadas do mouse para coordenadas da janela
        Ponto p = ConverteCoords(x, y);
        // Adiciona na lista de vértices global
        g_vertices.push_back(p);
        // Manda redesenhar
        glutPostRedisplay();
    }
}

//Faz o display 2D
void Display2D()
{
    if (g_vertices.size() > 0)
    {
        //Desenha todos os vértices
        //2*tamanho_linha para destacar
        DesenhaVertices3D(g_vertices, 0, cor_contorno, 2*tamanho_linha);

        //Se tiver 2 vértices
        if (g_vertices.size() == 2)
        {
            //Desenha a reta que os conecta
            DesenhaLinha3D(g_vertices[0], g_vertices[1], 0, cor_contorno, tamanho_linha);
        }
        //Se tiver mais que 2 vértices, é um polígono
        else if (g_vertices.size() > 2)
        {
            //Desenha as arestas do contorno
            DesenhaContorno3D(g_vertices, 0, cor_contorno, tamanho_linha);

            //Preenche o polígono
            ET* listaET = CriaET(g_vertices);
            PreenchimentoDePoligonos(listaET, cor_preenc, 0);

            //Limpa a memória
            delete[] listaET->lista;
            delete listaET;
        }
    }

    glFlush();
}

//Função para extrusão dos polígonos 2D
void ExtrusaoPoligonos()
{
    //Se ainda não fez nem um polígono
    if (g_vertices.size() < 3)
    {
        //Desenha no plano z = 0
        Display2D();
        return;
    }
    //Se já tem um polígono

    //Define uma altura pro polígono 3D
    float h = 10.0f;
    
    //z = 0 -> base
    //z = h -> topo

    //Desenha todos os vértices
    //2*tamanho_linha para destacar
    DesenhaVertices3D(g_vertices, 0, cor_contorno, 2*tamanho_linha);
    DesenhaVertices3D(g_vertices, h, cor_contorno, 2*tamanho_linha);

    //Desenha as arestas dos contornos
    DesenhaContorno3D(g_vertices, 0, cor_contorno, tamanho_linha);
    DesenhaContorno3D(g_vertices, h, cor_contorno, tamanho_linha);

    //Para conectar as arestas entre a base e o topo
    int n = g_vertices.size();

    glLineWidth(tamanho_linha);
    glColor3f(cor_contorno.r, cor_contorno.g, cor_contorno.b);
    glBegin(GL_LINES);

    for (int i = 0; i < n; i++)
    {
        Ponto a = g_vertices[i];
        
        //Desenha a reta que os conecta
        glVertex3f(a.x, a.y, 0);
        glVertex3f(a.x, a.y, h);
    }

    glEnd();

    //Preenche os polígonos
    ET* listaET = CriaET(g_vertices);
    PreenchimentoDePoligonos(listaET, cor_preenc, 0);
    PreenchimentoDePoligonos(listaET, cor_preenc, h);

    //Limpa a memória
    delete[] listaET->lista;
    delete listaET;

    //Desenha os planos entre a base e o topo
    glColor3f(cor_preenc.r, cor_preenc.g, cor_preenc.b);
    glBegin(GL_QUADS);

    for (int i = 0; i < n; i++)
    {
        Ponto a = g_vertices[i];
        Ponto b = g_vertices[(i + 1) % n];

        //Cria um plano conectando os vértices na base e no topo
        glVertex3f(a.x, a.y, 0);
        glVertex3f(b.x, b.y, 0);
        glVertex3f(b.x, b.y, h);
        glVertex3f(a.x, a.y, h);
    }

    glEnd();
}

//Muda o tamanho da janela
void Reshape(int w, int h)
{
    largura_atual = w;
    altura_atual = h;
    
    //Atualiza a janela
    glViewport(0, 0, w, h);

    //Atualiza a projecao
    camera.modo_projecao(w, h);
}

//Função de controle das luzes
void ControlaLuzes(menu_opcoes flag)
{
    //Caso as luzes estejam ativas
    if (flag == LUZES)
    {
        //Reduz a luz ambiente
        GLfloat luzCinza[] = {0.2f, 0.2f, 0.2f, 1.0f};
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzCinza);

        //TODO
        luz0.ligar();
        luz1.ligar();
        luz2.ligar();

        luz0.desenha();
        luz1.desenha();
        luz2.desenha();

        luz0.atualizar();
        luz1.atualizar();
        luz2.atualizar();
    }
    //Caso estejam desligadas
    else
    {
        //Adiciona a luz branca
        GLfloat luzBranca[] = {1.0f, 1.0f, 1.0f, 1.0f};
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzBranca);

        //Desativa as luzes
        luz0.desligar();
        luz1.desligar();
        luz2.desligar();
    }
}

//Função para configurar a tela para usar o phong
void configura_phong()
{
    Color cor_atual = {0.0f, 0.0f, 1.0f};  // Objeto azul
    Color cor_amb = {0.5f, 0.5f, 0.5f};    // Luz Ambiente (cinza)
    Color cor_difusa = {1.0f, 1.0f, 1.0f}; // Luz Difusa (Branca)
    Color cor_espc = {1.0f, 1.0f, 1.0f};   // Luz Especular (Brilho Branco)

    //Propriedades da câmera
    glm::vec3 cam_posi = camera.getCameraPosicao();
    glm::vec3 cam_front = camera.getCameraFront();
    glm::vec3 cam_up = camera.getCameraUP();
    glm::vec3 alvo = cam_posi + cam_front;

    //Cria a matriz de transformação de coordenadas para coordenadas da câmera
    glm::mat4 view = glm::lookAt(cam_posi, alvo, cam_up);

    //Cria a luz global e converte sua direção para coordenadas da câmera
    glm::vec3 luz_mundo = glm::vec3(15.0f, 10.0f, 10.0f);
    glm::vec4 luz_view = view * glm::vec4(luz_mundo, 1.0f);

    //Define a posição da luz
    float luz_view_pos[3] = {0.0f, 0.0f, 0.0f};
    //Phong comeca com luz em view-space e camera na origem
    float camera_view_pos[3] = {0.0f, 0.0f, 0.0f};

    phong_cor.init(luz_view_pos, nullptr, camera_view_pos);

    //Cria a matriz de transformação dos objetos
    glm::mat4 model_matrix = glm::mat4(1.0f);
    model_matrix = glm::translate(model_matrix, glm::vec3(tx, ty, tz));
    model_matrix = glm::rotate(model_matrix, glm::radians(rxo), glm::vec3(1, 0, 0));
    model_matrix = glm::rotate(model_matrix, glm::radians(ryo), glm::vec3(0, 1, 0));
    model_matrix = glm::rotate(model_matrix, glm::radians(rzo), glm::vec3(0, 0, 1));
    model_matrix = glm::scale(model_matrix, glm::vec3(scaleo , scaleo , scaleo ));
    
    //Cria as matrizes de translações globais dos objetos, para ficarem nas posições desejadas
    glm::mat4 m_cubo = glm::translate(model_matrix, glm::vec3(-6.0f, 0.0f, 0.0f));
    glm::mat4 m_piramide = glm::translate(model_matrix, glm::vec3(6.0f, 0.0f, 0.0f));
    glm::mat4 m_esf = glm::translate(model_matrix, glm::vec3(0.0f, 0.0f, 0.0f));

    //Para guardar as novas coordendas
    vector<vector<VerticesPhong>> nw_coord_cubo, nw_coord_esf, nw_coords_pi;

    //Função para transformar as coordenadas
    auto processa = [&](auto &malha, auto &saida, glm::mat4 matriz_indi)
    {
        //Adiciona a translação do objeto as transformações globais
        glm::mat4 model_view = view * matriz_indi;

        //Calcula as normais, levando em conta a rotação e a escala
        //glm::mat3(model_view) -> descarta a translação
        //glm::transpose(glm::inverse(...)) -> técnica para lidar com escalas não-uniformes para as normais
        glm::mat3 matriz_normais = glm::transpose(glm::inverse(glm::mat3(model_view)));

        for (auto &face : malha)
        {
            vector<VerticesPhong> aux;

            //Para cada vértice da face
            for (auto &v : face)
            {
                //Calcula a posição nas coordenadas da câmera
                glm::vec4 p_view = model_view * glm::vec4(v.x, v.y, v.z, 1.0f);
                //Calcula as normais
                glm::vec3 n_origem = glm::vec3(v.nx,v.ny,v.nz);
                glm::vec3 n_view = glm::normalize(matriz_normais * n_origem);

                //Passa para a tela
                VerticesPhong v_ndc = (camera.transf_coord_tela(v, largura_atual, altura_atual, matriz_indi));
                VerticesPhong v_pixel = camera.toPixel(v_ndc, largura_atual, altura_atual);
                v_pixel.z = p_view.z;

                //Guarda a posição na view e as normais
                v_pixel.vx = p_view.x;
                v_pixel.vy = p_view.y;
                v_pixel.vz = p_view.z;

                v_pixel.nx = n_view.x;
                v_pixel.ny = n_view.y;
                v_pixel.nz = n_view.z;
                
                aux.push_back(v_pixel);
            }
            saida.push_back(move(aux));
        }
    };
    
    //Converte todas as malhas
    processa(malha_cubo, nw_coord_cubo, m_cubo);
    processa(malha_piramide, nw_coords_pi, m_piramide);
    processa(malha_esfera, nw_coord_esf, m_esf);

    //Loop de desenho em 2D
    glMatrixMode(GL_PROJECTION);
    //Congela os outros objetos
    glPushMatrix();
    glLoadIdentity();
    //Cria uma matriz de projeção paralela
    //xMin, xMax, yMin, yMax, zPerto, zLonge
    glOrtho(0.0, largura_atual, 0.0, altura_atual, -100.0, 100.0);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    //glEnable(GL_CULL_FACE); //Não desenha o interior
    //glCullFace(GL_BACK); //Descarta costas

    //Função para desenhar os vetores
    auto rasteriza = [&](auto &lista)
    {
        for (auto &face : lista)
        {
            ET_phong *et = phong_cor.CriaET(face);

            //Se et != null
            if (et)
            {
                //Desenha a face
                phong_cor.scan_line(et, cor_atual, ka, kd, ks, cor_amb, cor_difusa, cor_espc);

                //Limpa a memória
                delete[] et->lista;
                delete et;
            }
        }
    };

    //Desenha os objetos
    rasteriza(nw_coord_cubo);
    rasteriza(nw_coords_pi);
    rasteriza(nw_coord_esf);

    glDisable(GL_CULL_FACE);

    // Restaura matrizes
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

//Função para processar o Menu de opções
void ProcessaMenu(int opcao)
{
    switch (opcao)
    {
    //Cores de preenchimento do polígono
    case COR_VERM:
        cor_preenc.r = 1.0f;
        cor_preenc.g = 0.0f;
        cor_preenc.b = 0.0f;
        break;
    case COR_VERD:
        cor_preenc.r = 0.0f;
        cor_preenc.g = 1.0f;
        cor_preenc.b = 0.0f;
        break;
    case COR_AZUL:
        cor_preenc.r = 0.0f;
        cor_preenc.g = 0.0f;
        cor_preenc.b = 1.0f;
        break;
    case COR_BRANCA:
        cor_preenc.r = 1.0f;
        cor_preenc.g = 1.0f;
        cor_preenc.b = 1.0f;
        break;
    case COR_AMARELO:
        cor_preenc.r = 1.0f;
        cor_preenc.g = 1.0f;
        cor_preenc.b = 0.0f;
        break;

    //Cores de contorno
    case CONTORNO_VERM:
        cor_contorno = {1.0f, 0.0f, 0.0f};
        break;
    case CONTORNO_VERD:
        cor_contorno = {0.0f, 1.0f, 0.0f};
        break;
    case CONTORNO_AZUL:
        cor_contorno = {0.0f, 0.0f, 1.0f};
        break;
    case CONTORNO_BRANCA:
        cor_contorno = {1.0f, 1.0f, 1.0f};
        break;
    case CONTORNO_AMARELO:
        cor_contorno = {1.0f, 1.0f, 0.0f};
        break;

    //Grossuras de linha
    case LINHA_FINA:
        tamanho_linha = 1.0f;
        break;
    case LINHA_MED:
        tamanho_linha = 3.0f;
        break;
    case LINHA_GROSSA:
        tamanho_linha = 5.0f;
        break;

    //Modos de projeção
    case Orto:
        camera.setProjecao(MODO_ORTO);
        camera.modo_projecao(largura_atual, altura_atual);
        break;
    case Perspec:
        camera.setProjecao(MODO_PERSPEC);
        camera.modo_projecao(largura_atual, altura_atual);
        break;

    //Qual funcionalidade está sendo usada
    case VER_OBJT_2D:
        modo_atual = MD_DESENHO;
        flagLuz = ESCURO;
        break;
    case VER_EXTRUSAO:
        modo_atual = MD_EXTRUSAO;
        flagLuz = ESCURO;
        break;
    case VER_OBJT_3D:
        modo_atual = MD_OBJT;
        flagLuz = ESCURO;
        break;

    //Tipos de iluminação
    case FLAT:
        modo_atual = FLAT;
        flagLuz = LUZES;
        glShadeModel(GL_FLAT);
        break;
    case GOURAUD:
        modo_atual = GOURAUD;
        flagLuz = LUZES;
        glShadeModel(GL_SMOOTH);
        break;
    case PHONG:
        modo_atual = PHONG;
        //Não ativa nenhuma função do openGL, pois não existe
        break;

    //Controle das luzes
    case LUZES:
        flagLuz = LUZES;
        break;
    case ESCURO:
        flagLuz = ESCURO;
        break;

    //Limpa os vértices
    case LIMPAR_TELA:
        g_vertices.clear();
        break;

    //Fecha o programa
    case SAIR:
        exit(0);
        break;
    }

    //Redesenha a tela -> DisplayPrincipal()
    glutPostRedisplay();
}

//Função de display principal, chama as outras conforme necessidade
void DisplayPrincipal()
{
    //Limpa a tela
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    //Modo 2D
    if (modo_atual == MD_DESENHO)
    {
        //Ativa a câmera 2D
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glOrtho(ORTHO_MIN_X, ORTHO_MAX_X, ORTHO_MIN_Y, ORTHO_MAX_Y, -1.0, 1.0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        //Acende/apaga as luzes
        ControlaLuzes(flagLuz);
    }
    //Modo 3D
    else
    {
        //Define o modo de projeção da câmera
        camera.modo_projecao(largura_atual, altura_atual);
        camera.aplica_parametro();

        //Acende/apaga as luzes
        ControlaLuzes(flagLuz);
    }

    switch (modo_atual)
    {
    //Modo de desenho 2D
    case MD_DESENHO:
        Display2D();
        break;

    //Modo de extrusão 2D->3D
    case MD_EXTRUSAO:
        glTranslatef(tx, ty, 0);
        glRotatef(rxo, 1, 0, 0);
        glRotatef(ryo, 0, 1, 0);
        glRotatef(rzo, 0, 0, 1);
        //Diminui muito a escala, pois as coordenadas ficam muito grandes na projeção 3D
        glScalef(scaleo * 0.05f, scaleo * 0.05f, scaleo * 0.05f);

        ExtrusaoPoligonos();
        break;

    //Modo de objetos 3D
    //Sem iluminação específica
    case MD_OBJT:
        //Aplica as transformações
        glTranslatef(tx, ty, 0);
        glRotatef(rxo, 1, 0, 0);
        glRotatef(ryo, 0, 1, 0);
        glRotatef(rzo, 0, 0, 1);
        glScalef(scaleo, scaleo, scaleo);

        //Desenha os objetos 3D pré-definidos
        cubo.draw(0, 0, 0);
        esfera.draw(-4.0f, 0.0f, 0.0f);
        piramide.draw(4, 4, 0);

        //Desenha um cilindro
        glTranslatef(7, 1, 0);
        glutSolidCylinder(2, 2, 20, 20);

        break;
        
    //Ilunimação flat ou GOURARD
    //Elas foram ativadas no ProcessaMenu()
    //Aqui configura os objetos
    case FLAT:
    case GOURAUD:
        //Liga as luzes normais
        ControlaLuzes(flagLuz);
        
        glTranslatef(tx, ty, 0);
        glRotatef(rxo, 1, 0, 0);
        glRotatef(ryo, 0, 1, 0);
        glRotatef(rzo, 0, 0, 1);
        glScalef(scaleo, scaleo, scaleo);

        //Desenha os objetos 3D pré-definidos
        cubo.draw(0, 0, 0);
        esfera.draw(-4.0f, 0.0f, 0.0f);
        piramide.draw(4, 4, 0);

        //Desenha um cilindro
        glTranslatef(7, 1, 0);
        glutSolidCylinder(2, 2, 20, 20);
        
        break;

    //Iluminação Phong
    case PHONG:
        configura_phong();

        break;
    }

    glutSwapBuffers();
}

//Quando uma tecla "não-texto" (setas, etc) for pressionada
void callback_teclasespeciais(int key, int x, int y)
{
    //Informa a câmera
    camera.teclas_especiais(key, x, y);
}

//Quando uma tecla "text" (wasd, +, -, etc) for pressionada
void callback_teclado(unsigned char key, int x, int y)
{
    //Teclas que controlam a camera
    if (key == 'w' || key == 'W' ||
        key == 's' || key == 'S' ||
        key == 'a' || key == 'A' ||
        key == 'd' || key == 'D' ||
        key == '+' || key == '-')
    {
        camera.teclado(key, x, y);
    }

    // teclas que controlam os objetos

    float step = 0.1;

    switch (key)
    {
    //Rotação dos objetos

    //Anti-horário ao redor de X
    case 'z':
    case 'Z':
        rxo += 5;
        break;
    //Horário ao redor de X
    case 'x':
    case 'X':
        rxo -= 5;
        break;
    //Anti-horário ao redor de Y
    case 'c':
    case 'C':
        ryo += 5;
        break;
    //Horário ao redor de Y
    case 'v':
    case 'V':
        ryo -= 5;
        break;
    //Anti-horário ao redor de Z
    case 'f':
    case 'F':
        rzo += 5;
        break;
    //Horário ao redor de Z
    case 'r':
    case 'R':
        rzo -= 5;
        break;

    //Translação dos objetos

    //Move para y positivo
    case 'g':
    case 'G':
        ty += step;
        break;
    //Move para y negativo
    case 'h':
    case 'H':
        ty -= step;
        break;
    //Move para x negativo
    case 'j':
    case 'J':
        tx -= step;
        break;
    //Move para x positivo
    case 'k':
    case 'K':
        tx += step;
        break;
    
    //Escala dos objetos

    //Aumenta a escala
    case 'b':
    case 'B':
        scaleo += 0.1f;
        break;
    //Diminui a escala, até um limite
    case 'n':
    case 'N':
        if (scaleo >= 0.2f - epsilon)
            scaleo -= 0.1f;

        break;
    }

    //Redesenha a tela -> DisplayPrincipal()
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(WINDOW_W, WINDOW_H);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow("Poligonos 3D");

    if (!gladLoadGLLoader((GLADloadproc)glutGetProcAddress))
    {
        cout << "Erro ao carregar GLAD" << endl;
        return -1;
    }

    // habilitações globais
    glEnable(GL_DEPTH_TEST);
    //Normaliza automaticamente os vetores normais para a iluminação
    glEnable(GL_NORMALIZE);
    //Ativa as configurações das luzes
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);

    // Configuração inicial da camera
    camera.init(WINDOW_W, WINDOW_H, MODO_PERSPEC);

    luz0.init(GL_LIGHT0, DIRECIONAL); // sol
    luz0.set_posicao(0.0f, 6.0f, -4.0f);
    luz0.set_cor(1.0f, 0.95f, 0.8f);
    luz0.set_direcao(-1.0f, -1.0f, 1.0f);
    luz0.set_intensidade(0.8f);

    luz1.init(GL_LIGHT1, PONTUAL); // luz azul
    luz1.set_posicao(0.0f, -6.0f, 0.0f);
    luz1.set_cor(0.2f, 0.2f, 1.0f);
    luz1.set_intensidade(0.6f);

    luz2.init(GL_LIGHT2, SPOT); // luz magenta
    luz2.set_posicao(10.0f, 0.0f, 0.0f);
    luz2.set_cor(1.0f, 0.0f, 1.0f);
    luz2.set_direcao(-1.0f, 0.0f, 0.0f);
    luz2.set_Spot_configuracao(25.0f, 2.0f);
    luz2.set_intensidade(1.0f);

    //Inicializa os objetos
    cubo.init(5);           // tamanho
    esfera.init(2, 20, 20); // raio
    piramide.init(2);       // tamanho

    //Gera as malhas
    malha_cubo = cubo.gera_malhas(5.0f);
    malha_esfera = esfera.gera_malhas(2.0f, 20, 20);
    malha_piramide = piramide.gera_malhas();

    //Configura as funções de leitura do teclado
    glutKeyboardFunc(callback_teclado);
    glutSpecialFunc(callback_teclasespeciais);

    //Menu de opções (botão direito)
    //Cores de preenchimento
    int subCor = glutCreateMenu(ProcessaMenu);
    glutAddMenuEntry("Vermelho", COR_VERM);
    glutAddMenuEntry("Verde", COR_VERD);
    glutAddMenuEntry("Azul", COR_AZUL);
    glutAddMenuEntry("Amarelo", COR_AMARELO);
    glutAddMenuEntry("Branco", COR_BRANCA);
    //Cores de contorno
    int subContorno = glutCreateMenu(ProcessaMenu);
    glutAddMenuEntry("Vermelho", CONTORNO_VERM);
    glutAddMenuEntry("Verde", CONTORNO_VERD);
    glutAddMenuEntry("Azul", CONTORNO_AZUL);
    glutAddMenuEntry("Amarelo", CONTORNO_AMARELO);
    glutAddMenuEntry("Branco", CONTORNO_BRANCA);
    //Grossuras da linha
    int subLinha = glutCreateMenu(ProcessaMenu);
    glutAddMenuEntry("Fina", LINHA_FINA);
    glutAddMenuEntry("Media", LINHA_MED);
    glutAddMenuEntry("Grossa", LINHA_GROSSA);
    //Tipos de projeção
    int subProjec = glutCreateMenu(ProcessaMenu);
    glutAddMenuEntry("Orto", Orto);
    glutAddMenuEntry("Perspec", Perspec);
    //Tipos de iluminação
    int subLuz = glutCreateMenu(ProcessaMenu);
    glutAddMenuEntry("Flat", FLAT);
    glutAddMenuEntry("Gouraud", GOURAUD);
    glutAddMenuEntry("Phong", PHONG);
    //Controlador das luzes
    int addLuz = glutCreateMenu(ProcessaMenu);
    glutAddMenuEntry("Acender Luzes", LUZES);
    glutAddMenuEntry("Apagar Luzes", ESCURO);
    //Modos
    int subModos = glutCreateMenu(ProcessaMenu);
    glutAddMenuEntry("Modo Desenho", VER_OBJT_2D);
    glutAddMenuEntry("Modo Extrusao", VER_EXTRUSAO);
    glutAddMenuEntry("Modo OBJETOS 3D", VER_OBJT_3D);
    //Estrutura
    glutCreateMenu(ProcessaMenu);
    //Opções de rendering
    glutAddSubMenu("Modos", subModos);
    glutAddSubMenu("Projecao", subProjec);
    glutAddSubMenu("Forma de Iluminacao", subLuz);
    glutAddSubMenu("Configuracao das luzes", addLuz);
    //Separador
    glutAddMenuEntry("*** Estilos ***", -1);
    //Configurador 2D (e extrusão)
    glutAddSubMenu("Cor de Preenchimento", subCor);
    glutAddSubMenu("Cor de Contorno", subContorno);
    glutAddSubMenu("Espessura de linha", subLinha);
    //Ações
    glutAddMenuEntry("Limpar Tela", LIMPAR_TELA);
    glutAddMenuEntry("Sair", SAIR);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    //Configura a função de leitura do mouse
    glutMouseFunc(GerenciaMouse);
    //Configura a função de redimensionamento da janela
    glutReshapeFunc(Reshape);

    //Define a função de renderização principal
    glutDisplayFunc(DisplayPrincipal);
    //Loop principal
    glutMainLoop();
    return 0;
}