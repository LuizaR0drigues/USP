#include <iostream>
#include <vector>
#include <array>
#include <limits>
#include <cmath>
#include <algorithm>
#include <utility>
#include <iostream>
#include <vector>
#include <array>
#include <limits>
#include <cmath>
#include <algorithm>
#include <utility>

#include "include/glad/glad.h"
#include <GL/freeglut.h>
//objetos3d
#include "cubo.h"
#include "esfera.h"
#include "piramide.h"
#include "iluminacao.h"
#include "camera.h"//camera
#include "phong.h"
using namespace std;

#define MODO_ORTO false
#define MODO_PERSPEC true
//objetos e Camera 
Camera camera;
Luz luz0;//direcional
Luz luz1; //pontual
Luz luz2; //spot
Phong phong_cor;
//objetos 3d
Cubo cubo;
Esfera esfera;
Piramide piramide;

// variaveis de cor e linha
float cor_R = 1.0f, cor_G = 1.0f, cor_B = 1.0f;
float tamanho_linha = 1.0f;

// variaves pra definir a janela
const int WINDOW_W =  800,  WINDOW_H = 400;
const float ORTHO_MIN_X = -400, ORTHO_MAX_X = 400;
const float ORTHO_MIN_Y = -200, ORTHO_MAX_Y = 200;
int largura_atual = WINDOW_W;
int altura_atual = WINDOW_H;

// Transformações Geomtericas NO OBJETO 3D
float tx = 0.0, ty = 0.0, tz = 0.0;
float rxo = 0.0, ryo = 0.0, rzo = 0.0;
float scaleo = 1.0;

struct Ponto
{
    float x, y;
};

struct Color
{
    float r, g, b;
};

struct DadosET
{
    float yMax;
    float xMin;
    float incX;
};

struct ET
{
    int yMin, nroNiveis;
    vector<DadosET> *lista;
};
struct Poligono
{
    vector<Ponto> vertices;
    Color corPrenchimento;
    Color cor_Contorno;
    float espessura;
};

// Lista dinâmica - clique do user
vector<Ponto> g_vertices;
// cores
Color cor_preenc = {1.0f, 1.0f, 1.0f};
Color cor_contorno = {1.0f, 0.0f, 0.0f};

void plot_pixel(int x, int y)
{
    glVertex2i(x, y);
}

void draw_point(int x, int y, Color color, float grossura)
{

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

    // Define a cor e o tamanho
    glColor3f(color.r, color.g, color.b);
    glPointSize(grossura); // Substitui os loops 'for' de raio

    // Manda desenhar
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();

    glDisable(GL_POINT_SMOOTH);
    glDisable(GL_BLEND);
}

// O eixo X é dominante, i. e., para retas mais horizontais
void desenha_oct1(int x1, int y1, int x2, int y2)
{
    int x, y, dx, dy, d, incE, incNE, incY = 1;

    // variação em x e y
    dx = x2 - x1;
    dy = y2 - y1;

    // Se a reta diminui em Y
    if (dy < 0)
    {
        // Inverte a direção de crescimento
        incY = -1;
        // Inverte dy para não atrapalhar as contas
        dy *= -1;
    }

    // valor inicial da variavel de decisao
    d = 2 * dy - dx;
    incE = 2 * dy;
    incNE = 2 * (dy - dx);
    x = x1;
    y = y1;

    // desenha o ponto inicial
    plot_pixel(x, y);

    while (x < x2)
    {
        if (d <= 0)
        {
            // escolhe E
            d += incE;
            x++; // anda 1 unidade em X
        }
        else
        { // escolhe NE
            d += incNE;
            x++;
            y += incY;
        }

        plot_pixel(x, y);
    }
}

// EIxo Y é o dominante, i.e., retas mais verticiais.
void desenha_oct2(int x1, int y1, int x2, int y2)
{
    int x, y, dx, dy, d, incE, incNE, incX = 1;

    // variação em x e y
    dx = x2 - x1;
    dy = y2 - y1;

    // Se a reta diminui em X
    if (dx < 0)
    {
        // Inverte a direção de crescimento
        incX = -1;
        // Inverte dy para não atrapalhar as contas
        dx *= -1;
    }

    // valor inicial da variavel de decisao
    d = 2 * dx - dy;
    incE = 2 * dx;
    incNE = 2 * (dx - dy);
    x = x1;
    y = y1;

    // desenha o ponto inicial
    plot_pixel(x, y);

    while (y < y2)
    {
        if (d <= 0)
        {
            // escolhe E
            d += incE;
            y++; // anda 1u em X
        }
        else
        { // escolhe NE
            d += incNE;
            x += incX;
            y++;
        }

        plot_pixel(x, y);
    }
}

void draw_line(Ponto ponto1, Ponto ponto2, Color cor, float grossura)
{
    // define cor e espessura
    glColor3f(cor.r, cor.g, cor.b);
    glPointSize(grossura);

    // inicializa
    glBegin(GL_POINTS);

    int x1 = ponto1.x;
    int y1 = ponto1.y;
    int x2 = ponto2.x;
    int y2 = ponto2.y;

    // variação
    int dx = x2 - x1;
    int dy = y2 - y1;

    if (x1 == x2 && y1 == y2)
    { // um ponto no plano
        draw_point(x1, y1, cor, grossura);
        return;
    }

    if (dx == 0)
    { // reta vertical
        if (y1 > y2)
        {
            std::swap(y1, y2);
        }
        for (int y = y1; y <= y2; y++)
        {
            draw_point(x1, y, cor, grossura);
        }

        return;
    }

    if (dy == 0)
    { // reta horizontal
        if (x1 > x2)
        {
            std::swap(x1, x2);
        }
        for (int x = x1; x <= x2; x++)
        {
            draw_point(x, y1, cor, grossura);
        }
        return;
    }

    if (abs(dy) == abs(dx))
    { // retas de 45 e 135
        int inc_x = 1, inc_y = 1;
        if (x2 < x1)
        {
            inc_x = -1;
        }
        if (y2 < y1)
        {
            inc_y = -1;
        }

        for (int i = 0; i <= abs(dx); i++)
        {
            draw_point(x1, y1, cor, grossura);
            x1 += inc_x;
            y1 += inc_y;
        }
        return;
    }

    float m = (float)dy / (float)dx;

    if (m <= 1 && m >= -1)
    {
        if (dx >= 0)
        {
            desenha_oct1(x1, y1, x2, y2);
        }
        else
        {
            desenha_oct1(x2, y2, x1, y1);
        }
    }
    else
    {
        if (dy >= 0)
        {
            desenha_oct2(x1, y1, x2, y2);
        }
        else
        {
            desenha_oct2(x2, y2, x1, y1);
        }
    }

    glEnd();
}

void OrdenaPorX(vector<DadosET> *nivel)
{
    sort(nivel->begin(), nivel->end(),
         [](const DadosET &a, const DadosET &b)
         {
             return a.xMin < b.xMin;
         });
}

ET *CriaET(vector<Ponto> vertices)
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
        Ponto ver1 = vertices[i];
        Ponto ver2 = vertices[(i + 1) % n];
        ;

        if (ver1.y > ver2.y)
        {
            swap(ver1, ver2);
        }
        if ((int)ver1.y == (int)ver2.y)
        {
            continue;
        }
        int indice = ceil(ver1.y) - listaET->yMin;
        float dy = ver2.y - ver1.y;
        float dx = ver2.x - ver1.x;
        float m = dy / dx;

        listaET->lista[indice].push_back({ver2.y, ver1.x, m});
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

void PreenchimentoDePoligonos(ET *listaET, Color cor)
{
    // define cor
    glColor3f(cor.r, cor.g, cor.b);
    glPointSize(1.0f);

    // inicializa o desenho
    glBegin(GL_POINTS);

    vector<DadosET> listaAET;
    for (int i = 0; i < listaET->nroNiveis; i++)
    {
        int yNivel = i + listaET->yMin;
        for (int j = 0; j < (int)listaAET.size(); j++)
        {
            // Se a iteração está no nível ou acima do y máximo da aresta
            if (listaAET[j].yMax <= yNivel)
            {
                // Remove ela
                listaAET.erase(listaAET.begin() + j);
                j--;
                continue;
            }

            listaAET[j].xMin += 1 / listaAET[j].incX;
        }
        // Move todos os dados do nível pra lista AET
        listaAET.insert(listaAET.end(),
                        make_move_iterator(listaET->lista[i].begin()),
                        make_move_iterator(listaET->lista[i].end()));
        // Limpa o nível original
        listaET->lista[i].clear();
        // Reordena a lista
        OrdenaPorX(&listaAET);

        int verticesCruzados = 0;
        for (int x = listaAET[0].xMin; x < listaAET.back().xMin; x++)
        {
            while (x >= listaAET[verticesCruzados].xMin)
                verticesCruzados++;

            if (verticesCruzados % 2 == 1)
            {
                glVertex2f(x, yNivel);
            }
        }
    }
    glEnd();
}

Ponto converte_coords(int x_mouse, int y_mouse)
{
    float x_w, y_w;
    int w_janela = glutGet(GLUT_WINDOW_WIDTH);
    int h_janela = glutGet(GLUT_WINDOW_HEIGHT);

    x_w = ((float)x_mouse / w_janela) * (ORTHO_MAX_X - ORTHO_MIN_X) + ORTHO_MIN_X;
    y_w = ((float)(h_janela - y_mouse) / h_janela) * (ORTHO_MAX_Y - ORTHO_MIN_Y) + ORTHO_MIN_Y;

    return {x_w, y_w};
}

void gerenciaMouse(int button, int state, int x, int y)
{
    // Se clicou com botão ESQUERDO e soltou (GLUT_UP) ou apertou (GLUT_DOWN)
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        Ponto p = converte_coords(x, y);
        g_vertices.push_back(p); // Adiciona na lista global
        glutPostRedisplay();     // Manda redesenhar
    }
}

void display()
{
    // Define cor baseada nas variáveis globais do menu
    Color corAtual = {cor_R, cor_G, cor_B};
    Color corLinha = cor_contorno;
    // sao necessarios no min 3 pontos
    if (g_vertices.size() >= 3)
    {
        ET *listaET = CriaET(g_vertices);
        PreenchimentoDePoligonos(listaET, corAtual);

        delete[] listaET->lista;
        delete listaET;
    }

    // contorno
    if (g_vertices.size() > 0)
    {
        glPointSize(5.0f);
        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_POINTS);

        for (auto p : g_vertices)
            glVertex2f(p.x, p.y);
        glEnd();
        // Linhas conectando
        if (g_vertices.size() >= 3)
        {
            for (size_t i = 0; i < g_vertices.size() - 1; i++)
            {
                draw_line(g_vertices[i], g_vertices[i + 1], corLinha, tamanho_linha);
            }
            // mais de 2 pontos, fecha o polígono visualmente
            if (g_vertices.size() > 2)
            {
                draw_line(g_vertices.back(), g_vertices[0], corLinha, tamanho_linha);
            }
        }
    }

    glFlush();
}

// realizando a extrusão dos poligonos
void extrusao_poligonos()
{
    // definindo uma altura padrao
    float h = 10.0f;

    glBegin(GL_POLYGON);

    // desenhando a base
    glColor3f(cor_R, cor_G, cor_B);
    for (auto base : g_vertices)
        glVertex3f(base.x, base.y, 0.0f);
    glEnd();

    // construindo as paredes
    glBegin(GL_QUADS);
    for (int i = 0; i < g_vertices.size() - 1; i++)
    {
        auto a = g_vertices[i];
        auto b = g_vertices[i + 1];
        glColor3f(1.0f, 0.0f, 1.0f);
        glVertex3f(a.x, a.y, 0);
        glVertex3f(b.x, b.y, 0);
        glVertex3f(b.x, b.y, h);
        glVertex3f(a.x, a.y, h);
    }
    // ultimo ponto
    auto a = g_vertices[0]; // primeiro
    int tam = g_vertices.size() - 1;
    auto c = g_vertices[tam]; // ultimo
    glVertex3f(c.x, c.y, 0);
    glVertex3f(a.x, a.y, 0);
    glVertex3f(a.x, a.y, h);
    glVertex3f(c.x, c.y, h);

    glEnd();

    // desenhando o topo
    glBegin(GL_POLYGON);
    glColor3f(cor_R, cor_G, cor_B);
    for (auto topo : g_vertices)
        glVertex3f(topo.x, topo.y, h);
    glEnd();
}

void reshape(int w, int h){
    largura_atual = w;
    altura_atual = h;
    //atualiza
    glViewport(0,0, w, h);

    //atualiza a projecao
    camera.modo_projecao(w, h);
}

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
    Orto ,
    Perspec ,
    VER_OBJT_3D,
    VER_OBJT_2D,
    VER_EXTRUSAO,
    MD_EXTRUSAO, //extrusao
    MD_DESENHO,//trabalho 1
    MD_OBJT,//objetos 3d
    GOURAUD,
    FLAT,
    PHONG
};
menu_opcoes modo_atual = MD_DESENHO;
 
void recupera_dados(GLfloat* pos_obs, GLfloat* pos_fonte){
    
    for(int i=0; i<3; i++){
        cout << "Digite a posicao do observador(x, y, z): " << endl;
        cin >> pos_obs[i];
        
    }

    for(int i=0; i<3; i++){
        cout << "Digite a posicao da FOnte de Luz(x, y, z): " << endl;
        cin >> pos_fonte[i];
        
    }
}
void processa_menu(int opcao)
{
    switch (opcao)
    {
    // cores
    case COR_VERM:
        cor_R = 1.0f;
        cor_G = 0.0f;
        cor_B = 0.0f;
        break;
    case COR_VERD:
        cor_R = 0.0f;
        cor_G = 1.0f;
        cor_B = 0.0f;
        break;
    case COR_AZUL:
        cor_R = 0.0f;
        cor_G = 0.0f;
        cor_B = 1.0f;
        break;
    case COR_BRANCA:
        cor_R = 1.0f;
        cor_G = 1.0f;
        cor_B = 1.0f;
        break;
    case COR_AMARELO:
        cor_R = 1.0f;
        cor_G = 1.0f;
        cor_B = 0.0f;
        break;
    // contorno
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
    
    // opcoes de linha
    case LINHA_FINA:
        tamanho_linha = 1.0f;
        break;
    case LINHA_MED:
        tamanho_linha = 3.0f;
        break;
    case LINHA_GROSSA:
        tamanho_linha = 5.0f;
        break;
    //modos de projecao 
    case Orto:
        camera.setProejcao(MODO_ORTO);
        camera.modo_projecao(largura_atual, altura_atual);
        
        break;
    case Perspec:
        camera.setProejcao(MODO_PERSPEC);
        camera.modo_projecao(largura_atual, altura_atual);
        break;
    
    case VER_EXTRUSAO:
        modo_atual= MD_EXTRUSAO;
        break;
    case VER_OBJT_2D:
        modo_atual = MD_DESENHO;
        break;
    case VER_OBJT_3D:
        modo_atual = MD_OBJT;
        break;

    case GOURAUD:
        //calcula a cor em cada vértice e interpola (mistura) os pixels no meio
        glShadeModel(GL_SMOOTH);
        break;
    case FLAT:
        //pega a cor de um único vértice e pinta a face inteira com aquela cor sólida.
        glShadeModel(GL_FLAT);
        break;
    case PHONG:
        phong_cor.init();
        break;
    case LIMPAR_TELA:
        g_vertices.clear();
        break;
    case SAIR:
        exit(0);
        break;
    }
    // redesenha a tela
    glutPostRedisplay();
}


void display_principal(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // limpar cor e pronfundidade
    glLoadIdentity();

    GLfloat cor_amb[3] = {0.5, 0.5, 0.5};
    GLfloat pos[3] = {0,10,0};
    GLfloat cor_luz[3] = {1.0f, 1.0f,1.0f};
    GLfloat pos_spot[3] = {0,5,15};
    GLfloat direcao_spot[3] = {1,-0.2, -1};
    GLfloat cor_spot[3] = {0.5f, 0.0f,0.5f};
    if(modo_atual == MD_DESENHO)
    {   
        //modo 2D
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glOrtho(ORTHO_MIN_X, ORTHO_MAX_X, ORTHO_MIN_Y, ORTHO_MAX_Y, -1.0,1.0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }
    else{
        //parametros 3d 
        camera.modo_projecao(largura_atual, altura_atual);
        camera.aplica_paramtero();
    }

    switch (modo_atual)
    {
    case MD_OBJT:
        //ILUMINAÇÂO
        //modo iluminação
        glEnable(GL_LIGHTING);//ativa o modo iluminação
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_COLOR_MATERIAL);
        glColorMaterial(GL_FRONT, GL_DIFFUSE);

        //desenhando as luzes
        luz0.atualizar(); 
        luz0.desenha();  

        luz1.atualizar();
        luz1.desenha(); 

        luz2.atualizar();
        luz2.desenha();
        //TG nos objtos
        glPushMatrix();
        glTranslatef(tx, ty, 0);
        glRotatef(rxo, 1,0,0);
        glRotatef(ryo, 0,1, 0);
        glRotatef(rzo, 0,0, 1);
        glScalef(scaleo, scaleo, scaleo);

        //desenho dos objtos
        cubo.draw(0,0,0);
        esfera.draw(4,4,4);
        piramide.draw(6,6,6);
        
        //objeto pr=e-definifo
        glTranslatef(7, 1, 0);
        glutSolidCylinder(2, 2, 20, 20);
        glPopMatrix();
        break;
    case MD_EXTRUSAO:
        
        if(g_vertices.size() >= 3){
            glPushMatrix();
            float scale_objt = scaleo * 0.005f;
            //TG nos objtos
            glTranslatef(tx, ty, 0);
            glRotatef(rxo, 1,0,0);
            glRotatef(ryo, 0,1, 0);
            glRotatef(rzo, 0,0, 1);
            glScalef(scale_objt, scale_objt, scale_objt);

            extrusao_poligonos();
            glPopMatrix();
        }
        break;
    case MD_DESENHO:
        display();
        break;
    }

    glutSwapBuffers();
}

void callback_teclasespeciais(int key, int x, int y){
    
    camera.teclas_especiais(key, x, y);
    
}

void callback_teclado(unsigned char key, int x, int y){
    //teclas que controlam a camera
    if (key == 'w' || key == 'W' || 
        key == 's' || key == 'S' || 
        key == 'a' || key == 'A' || 
        key == 'd' || key == 'D' ||
        key == '+' || key == '-')
    {
        camera.teclado(key, x, y);
    }
    //teclas que controlam os objetos 
    float step = 0.1;
    // Rotação zxcvrf
    switch (key)
    {
    case 'z': case 'Z':
        rxo += 5;
        break;
    case 'x': case 'X':
        rxo -= 5;
        break;
    case 'c':case 'C':
        ryo += 5;
        break;
    case 'v':case 'V':
        ryo -= 5;
        break;
    case 'f': case 'F':
        rzo += 5;
        break;
    case 'r': case 'R':
        rzo -= 5;
        break;

    //translação
    case 'g':case 'G':
        ty += step;
        break;
    case 'h': case 'H':
        ty -= step;
        break;
    case 'j': case 'J':
        tx -= step;
        break;
    case 'k': case 'K':
        tx += step;
        break;
    //zoom bn
    case 'b': case 'B':
        scaleo += 0.1f;
        break;
    case 'n':case 'N':
        if (scaleo > 0.2f)
            scaleo -= 0.1f;
        break;
    }
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
    //habilitações globais
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);//lida com a normalização apesar do tamanho do objetos

    //Configuração inicial da camera
    camera.init(WINDOW_W, WINDOW_H, Perspec);
    
    luz0.init(GL_LIGHT0, DIRECIONAL);//sol
    luz0.set_posicao(15.0f, 10.0f, 10.0f);
    luz0.set_cor(1.0f, 0.95f, 0.8f);
    luz0.set_intensidade(0.8f); 
    luz0.ligar();

    luz1.init(GL_LIGHT1, PONTUAL);//luz azul
    luz1.set_posicao(-10.0f, 10.0f, 0.0f);
    luz1.set_cor(0.2f, 0.2f, 1.0f);
    luz1.set_intensidade(0.6f);
    luz1.ligar();

    luz2.init(GL_LIGHT2, SPOT);//luz magenta
    luz2.set_posicao(1.0f, 7.0f, 0.0f);
    luz2.set_cor(1.0f, 0.0f, 1.0f); 
    luz2.set_direcao(0.0f, -1.0f, 0.0f); //aponta para baixo
    luz2.set_Spot_configuracao(25.0f, 2.0f);
    luz2.set_intensidade(1.0f);
    luz2.ligar();

    //inicializo os objtos
    cubo.init(5);//tamanho 5
    esfera.init(1, 20, 20); //raio = 10
    piramide.init(2); //tamanho 5

    
    // leitura do teclado e setas
    glutKeyboardFunc(callback_teclado);
    glutSpecialFunc(callback_teclasespeciais);
    
    //menu de desenho 
    //cores
    int subCor = glutCreateMenu(processa_menu);
    glutAddMenuEntry("Vermelho", COR_VERM);
    glutAddMenuEntry("Verde", COR_VERD);
    glutAddMenuEntry("Azul", COR_AZUL);
    glutAddMenuEntry("Amatelo", COR_AMARELO);
    glutAddMenuEntry("Branco", COR_BRANCA);
    //contorno
    int subContorno = glutCreateMenu(processa_menu);
    glutAddMenuEntry("Vermelho", CONTORNO_VERM);
    glutAddMenuEntry("Verde", CONTORNO_VERD);
    glutAddMenuEntry("Azul", CONTORNO_AZUL);
    glutAddMenuEntry("Amatelo", CONTORNO_AMARELO);
    glutAddMenuEntry("Branco", CONTORNO_BRANCA);
    //linhas
    int subLinha = glutCreateMenu(processa_menu);
    glutAddMenuEntry("Fina", LINHA_FINA);
    glutAddMenuEntry("Media", LINHA_MED);
    glutAddMenuEntry("Grossa", LINHA_GROSSA);

    //Menu que lida com as porjeções
    int subProjec = glutCreateMenu(processa_menu);
    glutAddMenuEntry("Orto", Orto);
    glutAddMenuEntry("Perspec", Perspec);

    int subLuz = glutCreateMenu(processa_menu);
    glutAddMenuEntry("Gouraud", GOURAUD);
    glutAddMenuEntry("Flat", FLAT);
    glutAddMenuEntry("Phong", PHONG);
    
    // Menus
    int subModos = glutCreateMenu(processa_menu);
    glutAddMenuEntry("Modo Desenho", VER_OBJT_2D);
    glutAddMenuEntry("Modo Extrusao", VER_EXTRUSAO);
    glutAddMenuEntry("Modo OBJETOS 3D", VER_OBJT_3D);

    //tronco
    //menu de desenho
    glutCreateMenu(processa_menu);
   
    glutAddSubMenu("Modos", subModos);
    glutAddSubMenu("Projecao", subProjec);
    glutAddSubMenu("Met Iluminacao", subLuz);

    glutAddMenuEntry("*** Estilos ***", -1);
    glutAddSubMenu("Cor de Preenchimento", subCor);
    glutAddSubMenu("Cor de Contorno", subContorno);
    glutAddSubMenu("Espessura de linha", subLinha);

    glutAddMenuEntry("LIMPAR TELA", LIMPAR_TELA); //
    glutAddMenuEntry("Sair", SAIR);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    // mouse
    glutMouseFunc(gerenciaMouse);
    glutReshapeFunc(reshape);
    //seleciona os modos
    glutDisplayFunc(display_principal);
    glutMainLoop();
    return 0;
}