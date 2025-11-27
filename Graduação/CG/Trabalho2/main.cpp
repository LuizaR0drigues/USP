#include <iostream>
#include <vector>
#include <array>
#include <limits>
#include <cmath>
#include <algorithm>
#include <utility>

#include "include/glad/glad.h"
#include <GL/freeglut.h>

#include <iostream>
#include <vector>
#include <array>
#include <limits>
#include <cmath>
#include <algorithm>
#include <utility>

#include "include/glad/glad.h"
#include <GL/freeglut.h>


using namespace std;

//variaveis de cor e linha
float cor_R = 1.0f, cor_G = 1.0f, cor_B = 1.0f;
float tamanho_linha = 1.0f;

//variaves pra definir a janela
const float ORTHO_MIN_X = -400, ORTHO_MAX_X = 400;
const float ORTHO_MIN_Y = -200, ORTHO_MAX_Y = 200;
const int WINDOW_W = 800, WINDOW_H = 400;

struct Ponto
{
    float x, y;
};



struct Color {
    float r,g,b;
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
    vector<DadosET>* lista;
};
struct Poligono{
    vector<Ponto> vertices;
    Color corPrenchimento;
    Color cor_Contorno;
    float espessura;
};

// Lista dinâmica - clique do user
vector<Ponto> g_vertices;
//cores
Color cor_preenc = {1.0f, 1.0f, 1.0f};
Color cor_contorno = {1.0f, 0.0f, 0.0f};


void plot_pixel(int x, int y) {
    glVertex2i(x, y);
}

void draw_point(int x, int y, Color color, float grossura) {
    
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

//O eixo X é dominante, i. e., para retas mais horizontais
void desenha_oct1(int x1, int y1, int x2, int y2){
    int x, y, dx, dy, d, incE, incNE, incY = 1;

    //variação em x e y
    dx = x2 - x1;
    dy = y2 - y1;

    //Se a reta diminui em Y
    if(dy < 0)
    {
        //Inverte a direção de crescimento
        incY = -1;
        //Inverte dy para não atrapalhar as contas
        dy *= -1;
    }

    //valor inicial da variavel de decisao
    d = 2 * dy - dx;
    incE = 2 * dy;
    incNE = 2 * (dy - dx);
    x = x1;
    y = y1;

    //desenha o ponto inicial
    plot_pixel(x, y);


    while(x < x2){
        if (d <= 0) {
            //escolhe E
            d += incE;
            x++; //anda 1 unidade em X
        }
        else { //escolhe NE
            d += incNE;
            x++;
            y += incY;
        }

        plot_pixel(x, y);
    }
}

//EIxo Y é o dominante, i.e., retas mais verticiais.
void desenha_oct2(int x1, int y1, int x2, int y2){
    int x, y, dx, dy, d, incE, incNE, incX = 1;

    //variação em x e y
    dx = x2 - x1;
    dy = y2 - y1;

    //Se a reta diminui em X
    if(dx < 0)
    {
        //Inverte a direção de crescimento
        incX = -1;
        //Inverte dy para não atrapalhar as contas
        dx *= -1;
    }

    //valor inicial da variavel de decisao
    d = 2 * dx - dy;
    incE = 2 * dx;
    incNE = 2 * (dx - dy);
    x = x1;
    y = y1;

    //desenha o ponto inicial
    plot_pixel(x, y);

    while(y < y2){
        if (d <= 0) {
            //escolhe E
            d += incE;
            y++; //anda 1u em X
        }
        else { //escolhe NE
            d += incNE;
            x += incX;
            y++;
        }

        plot_pixel(x, y);
    }
}

void draw_line(Ponto ponto1, Ponto ponto2, Color cor, float grossura){
    //define cor e espessura
    glColor3f(cor.r, cor.g, cor.b);
    glPointSize(grossura);

    //inicializa
    glBegin(GL_POINTS);

    int x1 = ponto1.x;
    int y1 = ponto1.y;
    int x2 = ponto2.x;
    int y2 = ponto2.y;

    //variação
    int dx = x2 - x1;
    int dy = y2 - y1;

    if (x1 == x2 && y1 == y2){ //um ponto no plano
        draw_point(x1, y1, cor, grossura);
        return;
    }

    if (dx  == 0){ //reta vertical
        if (y1 > y2){
            std::swap(y1, y2);
        }
        for(int y = y1; y<=y2; y++)
        {
            draw_point(x1, y, cor, grossura);
        }

        return;
    }

    if (dy  == 0){ //reta horizontal
        if (x1 > x2){
            std::swap(x1, x2);
        }
        for(int x = x1; x<=x2; x++)
        {
            draw_point(x, y1, cor, grossura);
        }
        return;
    }

    if (abs(dy) == abs(dx)){ //retas de 45 e 135
        int inc_x = 1, inc_y = 1;
        if(x2 < x1)
        {
            inc_x = -1;
        }
        if(y2 < y1){
            inc_y = -1;
        }

        for(int i = 0; i <= abs(dx); i++){
            draw_point(x1, y1, cor, grossura);
            x1 += inc_x;
            y1+= inc_y;
        }
        return;
    }

    float m = (float)dy/(float)dx;

    if (m <= 1 && m >= -1)
    {
        if (dx >= 0){
            desenha_oct1(x1, y1, x2, y2);
        }
        else{
            desenha_oct1(x2, y2, x1, y1);
        }
    }
    else
    {
        if (dy >= 0){
            desenha_oct2(x1, y1, x2, y2);
        }
        else{
            desenha_oct2(x2, y2, x1, y1);
        }
    }

    glEnd();
}

void OrdenaPorX(vector<DadosET>* nivel)
{
    sort(nivel->begin(), nivel->end(),
                 [](const DadosET &a, const DadosET &b)
                 {
                     return a.xMin < b.xMin;
                 });
}

ET* CriaET(vector<Ponto> vertices)
{
    float yMin = numeric_limits<float>::max();
    float yMax = numeric_limits<float>::min();
    for(auto& ver : vertices)
    {
        if(ver.y < yMin)
            yMin = ver.y;

        if(ver.y > yMax)
            yMax = ver.y;
    }

    int yMinInt = static_cast<int>(ceil(yMin));
    int yMaxInt = static_cast<int>(floor(yMax));
    int nroNiveis = yMaxInt - yMinInt;

    ET* listaET = new ET();
    listaET->yMin = yMinInt;
    listaET->nroNiveis = nroNiveis;
    listaET->lista = new vector<DadosET>[nroNiveis];

    size_t n = vertices.size();
    for(size_t i=0; i<n; i++)
    {
        Ponto ver1 = vertices[i];
        Ponto ver2 = vertices[(i + 1) % n];;

        if(ver1.y > ver2.y)
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
        float m = dy/ dx;
        
        listaET->lista[indice].push_back({ver2.y, ver1.x, m});  
    }

    for(int i = 0; i < listaET->nroNiveis; i++)
    {
        if(!listaET->lista[i].empty())
        {
            OrdenaPorX(&(listaET->lista[i]));
        }
    }

    return listaET;
}

void PreenchimentoDePoligonos(ET* listaET, Color cor)
{
    //define cor 
    glColor3f(cor.r, cor.g, cor.b);
    glPointSize(1.0f);

    //inicializa o desenho
    glBegin(GL_POINTS);

    vector<DadosET> listaAET;
    for(int i = 0; i < listaET->nroNiveis; i++)
    {
        int yNivel = i + listaET->yMin;
        for(int j = 0; j < (int)listaAET.size(); j++)
        {
            //Se a iteração está no nível ou acima do y máximo da aresta
            if(listaAET[j].yMax <= yNivel)
            {
                //Remove ela
                listaAET.erase(listaAET.begin() + j);
                j--;
                continue;
            }

            listaAET[j].xMin += 1/listaAET[j].incX;
        }
        //Move todos os dados do nível pra lista AET
        listaAET.insert(listaAET.end(),
                        make_move_iterator(listaET->lista[i].begin()),
                        make_move_iterator(listaET->lista[i].end()));
        //Limpa o nível original
        listaET->lista[i].clear();
        //Reordena a lista
        OrdenaPorX(&listaAET);

        int verticesCruzados = 0;
        for(int x = listaAET[0].xMin; x < listaAET.back().xMin; x++)
        {
            while(x >= listaAET[verticesCruzados].xMin)
                verticesCruzados++;

            if(verticesCruzados % 2 == 1)
            {
                glVertex2f(x, yNivel);
            }
        }
    }
    glEnd();
}

Ponto converte_coords(int x_mouse, int y_mouse){
    float x_w, y_w;
    int w_janela = glutGet(GLUT_WINDOW_WIDTH);
    int h_janela = glutGet(GLUT_WINDOW_HEIGHT);

    x_w = ((float)x_mouse / w_janela) * (ORTHO_MAX_X - ORTHO_MIN_X) + ORTHO_MIN_X;

    y_w = ((float)(h_janela - y_mouse) / h_janela) * (ORTHO_MAX_Y - ORTHO_MIN_Y) + ORTHO_MIN_Y;

    return {x_w, y_w};
}

void gerenciaMouse(int button, int state, int x, int y) {
    // Se clicou com botão ESQUERDO e soltou (GLUT_UP) ou apertou (GLUT_DOWN)
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        Ponto p = converte_coords(x, y);
        g_vertices.push_back(p); // Adiciona na lista global
        glutPostRedisplay();     // Manda redesenhar
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Define cor baseada nas variáveis globais do menu
    Color corAtual = { cor_R, cor_G, cor_B };
    Color corLinha = cor_contorno;
    //sao necessarios no min 3 pontos
    if(g_vertices.size() >= 3){
        ET* listaET = CriaET(g_vertices);
        PreenchimentoDePoligonos(listaET, corAtual);

        delete[] listaET->lista;
        delete listaET;
    }


    //contorno
    if(g_vertices.size() >0)
    {
        glPointSize(5.0f);
        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_POINTS);

        for(auto p : g_vertices) glVertex2f(p.x, p.y);
        glEnd();
        // Linhas conectando
        if (g_vertices.size() >= 3) {
            for (size_t i = 0; i < g_vertices.size() - 1; i++) {
                draw_line(g_vertices[i], g_vertices[i+1], corLinha, tamanho_linha);
            }
            //mais de 2 pontos, fecha o polígono visualmente
            if(g_vertices.size() > 2) {
                draw_line(g_vertices.back(), g_vertices[0], corLinha, tamanho_linha);
            }
        }
    }
    
    glFlush();
}
enum menu_opcoes{
    COR_VERM, COR_VERD, COR_AZUL, COR_BRANCA, COR_AMARELO, 
    CONTORNO_VERM, CONTORNO_VERD, CONTORNO_AZUL, CONTORNO_BRANCA, CONTORNO_AMARELO, 
    LINHA_FINA, LINHA_MED, LINHA_GROSSA,
     LIMPAR_TELA, 
     SAIR
};

void processa_menu(int opcao){
    switch (opcao)
    {
    //cores
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
    //contorno
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

    //opcoes de linha
    case LINHA_FINA:
        tamanho_linha = 1.0f;
        break;
    case LINHA_MED:
        tamanho_linha = 3.0f;
        break;
    case LINHA_GROSSA:
        tamanho_linha = 5.0f;
        break;
        
    case LIMPAR_TELA: 
        g_vertices.clear(); 
        break;
    case SAIR:
        exit(0);
        break;

    }
    //redesenha a tela
    glutPostRedisplay();
}


//Transformações Geomtericas 
float tx = 0.0, ty = 0.0, tz= 0.0;
float rx = 0.0, ry = 0.0;
float scale = 1.0;


//desenho 3d
void drawCube(Color cor)
{
    glBegin(GL_QUADS);
    

    // Frente 
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.5, -0.5,  0.5);
    glVertex3f(-0.5,  0.5,  0.5);
    glVertex3f( 0.5,  0.5,  0.5);
    glVertex3f( 0.5, -0.5,  0.5);

    // Trás 
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(-0.5,  0.5, -0.5);
    glVertex3f( 0.5,  0.5, -0.5);
    glVertex3f( 0.5, -0.5, -0.5);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-0.5,  0.5, -0.5);
    glVertex3f(-0.5,  0.5,  0.5);
    glVertex3f( 0.5,  0.5,  0.5);
    glVertex3f( 0.5,  0.5, -0.5);

    // Baixo 
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(-0.5, -0.5,  0.5);
    glVertex3f( 0.5, -0.5,  0.5);
    glVertex3f( 0.5, -0.5, -0.5);

    // Direita 
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f( 0.5, -0.5, -0.5);
    glVertex3f( 0.5, -0.5,  0.5);
    glVertex3f( 0.5,  0.5,  0.5);
    glVertex3f( 0.5,  0.5, -0.5);

    // Esquerda 
    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(-0.5, -0.5,  0.5);
    glVertex3f(-0.5,  0.5,  0.5);
    glVertex3f(-0.5,  0.5, -0.5);

    glEnd();
}
void drawPiramide(Color cor)
{

    //base quadrada
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(-0.5f, -0.5f,  0.5f); 
    glVertex3f( 0.5f, -0.5f,  0.5f); 
    glVertex3f( 0.5f, -0.5f, -0.5f); 
    glVertex3f(-0.5f, -0.5f, -0.5f); 
    glEnd();

    //faces
    glBegin(GL_TRIANGLES);

    // Frente 
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f( 0.0f,  0.5f,  0.0f);
    glVertex3f(-0.5f, -0.5f,  0.5f); 
    glVertex3f( 0.5f, -0.5f,  0.5f);

    // direita
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f( 0.0f,  0.5f,  0.0f); 
    glVertex3f( 0.5f, -0.5f,  0.5f); 
    glVertex3f( 0.5f, -0.5f, -0.5f);

    //tras
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f( 0.0f,  0.5f,  0.0f); 
    glVertex3f( 0.5f, -0.5f, -0.5f); 
    glVertex3f(-0.5f, -0.5f, -0.5f);

    //esquerda
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f( 0.0f,  0.5f,  0.0f); 
    glVertex3f(-0.5f, -0.5f, -0.5f); 
    glVertex3f(-0.5f, -0.5f,  0.5f);
    
    glEnd();
}


void teclas_especiais(int key, int x, int y)
{
    float step = 0.1;
    switch (key)
    {
    case GLUT_KEY_UP:
        ty += step;
        break;
    case GLUT_KEY_DOWN:
        ty -= step;
        break;
    case GLUT_KEY_LEFT:
        tx -= step;
        break;
    case GLUT_KEY_RIGHT:
        tx += step;
        break;
    default:
        break;
    }
    
    glutPostRedisplay();
}

void teclado(unsigned char key,  int x, int y){

    //Rotação WASD
    switch (key)
    {
        case 'w':
        case 'W':
            rx += 5;
            break;
        case 's':
        case 'S':
            rx -= 5;
            break;
        case 'a':
        case 'A':
            ry += 5;
            break;
        case 'd':
        case 'D':
            ry -= 5;
            break;
        
        case '+':
            scale += 0.1f;
            break;
        case '-':
        if(scale > 0.1f)
                scale -= 0.1f;
        break;
    }
    glutPostRedisplay();
    
} 

//realizando a extrusão dos poligonos
void extrusao_poligonos(){
    //definindo uma altura padrao
    float h = 5.0f;

    glBegin(GL_POLYGON);

    //desenhando a base
    for(auto base: g_vertices) 
        glVertex3f(base.x, base.y, 0.0f);
    glEnd();

    //desenhando o topo
    for(auto topo: g_vertices) 
        glVertex3f(topo.x, topo.y, h);
    glEnd();

    //construindo as paredes
    glBegin(GL_QUADS);
    for(int i = 0; i< g_vertices.size()-1; i++)
        {
            auto a = g_vertices[i];
            auto b = g_vertices[i+1];
            glColor3f(1.0f, 0.0f, 1.0f);
            glVertex3f(a.x, a.y, 0);
            glVertex3f(b.x, b.y, 0);
            glVertex3f(b.x, b.y, h);
            glVertex3f(a.x, a.y, h);
           

            if(g_vertices.size()-1 == i) //ultimo ponto
            {   auto c = g_vertices[0];
                glVertex3f(a.x, a.y, 0);
                glVertex3f(a.x, a.y, h);
                glVertex3f(c.x, c.y, 0);
                glVertex3f(c.x, c.y, h);
            }

        }
    glEnd();

}
void display_3d(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//limpar cor e pronfundidade
    glLoadIdentity();

    //cam (olhoX, olhoY, olhoZ, alvoX, alvoY, alvoZ, upX, upY, upZ)
    gluLookAt(0, 0, tz=15.0, 0.0, 0., 0.0, 0, 1, 0);

    //Aplicando transformações
    glTranslatef(tx, ty, 0);
    
    glRotatef(rx, 1, 0, 0);//rotaciona eixo x
    glRotatef(ry, 0, 1, 0); //rotacao eixo y
    glScalef(scale, scale, scale); //escala
    //drawPiramide(cor_preenc);
    if(g_vertices.size() >= 3) {
        // Talvez você queira definir uma cor antes
        glColor3f(cor_preenc.r, cor_preenc.g, cor_preenc.b); 
        extrusao_poligonos(); 
    }
    glutSwapBuffers();
}
void init(){
    glEnable(GL_DEPTH_TEST);//profundidade
    glClearColor(0.5, 0.5, 0.5, 1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45, (float)WINDOW_W/WINDOW_H, 0.1, 50.0);
    glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(WINDOW_W, WINDOW_H);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow("Poligonos 3D");

    if (!gladLoadGLLoader((GLADloadproc)glutGetProcAddress)) {
        cout << "Erro ao carregar GLAD" << endl;
        return -1;
    }
   //leitura do teclado e setas
    glutKeyboardFunc(teclado);        
    glutSpecialFunc(teclas_especiais);
    // Menus
    int menuCor = glutCreateMenu(processa_menu);
    glutAddMenuEntry("Vermelho", COR_VERM);
    glutAddMenuEntry("Verde", COR_VERD);
    glutAddMenuEntry("Azul", COR_AZUL);
    glutAddMenuEntry("Amatelo", COR_AMARELO);
    glutAddMenuEntry("Branco", COR_BRANCA);
    
    int menuContorno = glutCreateMenu(processa_menu);
    glutAddMenuEntry("Vermelho", CONTORNO_VERM);
    glutAddMenuEntry("Verde", CONTORNO_VERD);
    glutAddMenuEntry("Azul", CONTORNO_AZUL);
    glutAddMenuEntry("Amatelo", CONTORNO_AMARELO);
    glutAddMenuEntry("Branco", CONTORNO_BRANCA);
    
    int menuLinha = glutCreateMenu(processa_menu);
    glutAddMenuEntry("Fina", LINHA_FINA);
    glutAddMenuEntry("Media", LINHA_MED);
    glutAddMenuEntry("Grossa", LINHA_GROSSA);

    glutCreateMenu(processa_menu);
    glutAddSubMenu("Cor", menuCor);
    glutAddSubMenu("Cotorno", menuContorno);
    glutAddSubMenu("Linha", menuLinha);
    glutAddMenuEntry("LIMPAR TELA", LIMPAR_TELA); //
    glutAddMenuEntry("Sair", SAIR);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    //mouse
    glutMouseFunc(gerenciaMouse);

    init();

    glutDisplayFunc(display_3d);
    glutMainLoop();
    return 0;
}