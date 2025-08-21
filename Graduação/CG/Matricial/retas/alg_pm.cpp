#include <iostream>
#include <stdio.h>
#include <utility>
#include <GLFW/glfw3.h>
#include <GL/gl.h>


int cria_janela(GLFWwindow** window, int largura, int altura){
     //inicializando a biblioteca glfw
    if (!glfwInit()){
        return -1;
    }
    //Cria uma janela - no modo janela - e seu contexto OpenGL
    
    *window = glfwCreateWindow(largura, altura, "Desenhando retas - met Bresenham", NULL, NULL);
    
    //verificando a integridade
    if (!*window) {
        glfwTerminate();
        return -1;
    }

    // o contexto da janela passa a ser o atual - var window
    glfwMakeContextCurrent(*window);

    //definindo a area de desenho
    glViewport(0,0, largura, altura);

    //sistema de coord
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); //reseta 

    glOrtho(0.0, largura, 0.0, altura, -1.0,1.0); //canto inf esquedo é (0,0)

    //matriz de desenho
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    return 0;
}


void desenha_oct1(int x1, int y1, int x2, int y2){
    int x, y, dx, dy, d, incE, incNE, incY = 1;

    //variação em x e y
    dx = x2 - x1;
    dy = y2 - y1;

    if(dy < 0)
    {
        incY = -1;
        dy *= -1;
    }

    //valor inicial da variavel de decisao
    d = 2 * dy - dx;
    incE = 2 * dy;
    incNE = 2 * (dy - dx);
    x = x1;
    y = y1;

    //desenha o ponto inicial
    glVertex2i(x1, y1);

    
    while(x < x2){
        if (d <= 0) {
            //escolhe E
            d += incE;
            x++; //anda 1u em X
        }
        else { //escolhe NE
            d += incNE;
            x++;
            y += incY;
        }

        glVertex2i(x, y);
    }
}

void desenha_oct2(int x1, int y1, int x2, int y2){
    int x, y, dx, dy, d, incE, incNE, incX = 1;

    //variação em x e y
    dx = x2 - x1;
    dy = y2 - y1;

    if(dx < 0)
    {
        incX = -1;
        dx *= -1;
    }

    //valor inicial da variavel de decisao
    d = 2 * dx - dy;
    incE = 2 * dx;
    incNE = 2 * (dx - dy);
    x = x1;
    y = y1;

    //desenha o ponto inicial
    glVertex2i(x1, y1);

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

        glVertex2i(x, y);
    }
}

void alg_geral(int x1, int y1, int x2, int y2){
    //variação
    int dx = x2 - x1;
    int dy = y2 - y1;
    
    if (x1 == x2 && y1 == y2){ //um ponto no plano
        glVertex2i(x1, y1);
        return;
    }

    if (dx  == 0){ //reta vertical
        if (y1 > y2){
            std::swap(y1, y2);
        }
        for(int y = y1; y<=y2; y++)
        {
            glVertex2i(x1, y);
        }
        return;
    }

    if (dy  == 0){ //reta horizontal
        if (x1 > x2){
            std::swap(x1, x2);
        }
        for(int x = x1; x<=x2; x++)
        {
            glVertex2i(x, y1);
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
            glVertex2i(x1, y1);
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
}
int main(){
    int  x1, x2;
    int  y1, y2;
     
    int altura = 600;
    int largura = 800;
    //std::cin >> x1 >> y1 >> x2 >> y2;
   
   
    //criando a janela
    GLFWwindow* window = nullptr; //cria um ponteiro nulo do tipo GLFW

    if(cria_janela(&window, largura, altura) != 0){
        std::cerr << "erro ao criar a janela" << std::endl;
        return -1;
    }
    //renderizando
    glClear(GL_COLOR_BUFFER_BIT);

    //pixel vermelho
    glPointSize(3.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    
    glBegin(GL_POINTS);
    
    //Eixos
    glColor3f(1.0f, 1.0f, 1.0f);
    alg_geral(800, 300, 0, 300);
    alg_geral(400, 600, 400, 0);

    //45 graus
    glColor3f(1.0f, 0.0f, 0.0f);
    alg_geral(400, 300, 500, 400);
    alg_geral(400, 300, 500, 200);
    alg_geral(400, 300, 300, 400);
    alg_geral(400, 300, 300, 200);

    //Primeiro quadrante
    glColor3f(0.0f, 1.0f, 0.0f);
    alg_geral(400, 300, 500, 350);
    alg_geral(400, 300, 500, 450);

    //Segundo quadrante
    glColor3f(0.0f, 0.0f, 1.0f);
    alg_geral(400, 300, 300, 350);
    alg_geral(400, 300, 300, 450);

    //Terceiro quadrante
    glColor3f(1.0f, 1.0f, 0.0f);
    alg_geral(400, 300, 300, 250);
    alg_geral(400, 300, 300, 150);

    //Quarto quadrante
    glColor3f(0.0f, 1.0f, 1.0f);
    alg_geral(400, 300, 500, 250);
    alg_geral(400, 300, 500, 150);
    
    glEnd();
    //troca os buffer de cor para exibição correta
    glfwSwapBuffers(window);

    
    //loop principal
    while(!glfwWindowShouldClose(window))
    {
        
        //escuta eventos: mouse, teclado, fechar janela e etc
        glfwPollEvents();
    }

    //exclui os ponteiros
    glfwTerminate();
    return 0;
}

