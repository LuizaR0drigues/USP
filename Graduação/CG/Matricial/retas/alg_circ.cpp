#include <iostream>
#include <stdio.h>
#include <utility>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <cmath>
#include <chrono>

# define PI 3.14159265358979323846  /* pi */


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

void MidPointCircleInt(int r, int x_meio_tela, int y_meio_tela){
    int x = 0;
    int y = r;
    int d = 1 - r;
    int deltaE = 3;
    int deltaSE = -2*r+5;

    glVertex2i(x, y);
    while(y > x){
        if(d < 0){
            d += deltaE;
            deltaE += 2;
            deltaSE += 2;
        }
        else{
            d += deltaSE;
            deltaE += 2;
            deltaSE += 4;
            y--;
        }
        x++;
        
        glVertex2i(y + x_meio_tela, x + y_meio_tela); //1º Octante
        glVertex2i(x + x_meio_tela, y + y_meio_tela); //2º Octante
        glVertex2i(-x + x_meio_tela, y + y_meio_tela); //3º Octante
        glVertex2i(-y + x_meio_tela, x + y_meio_tela); //4º Octante
        glVertex2i(-y + x_meio_tela, -x + y_meio_tela); //5º Octante
        glVertex2i(-x + x_meio_tela, -y + y_meio_tela); //6º Octante
        glVertex2i(x + x_meio_tela, -y + y_meio_tela); //7º Octante
        glVertex2i(y + x_meio_tela, -x + y_meio_tela); //8º Octante
    }
}

void CirculoPorTrigonometria(int r, int x_meio_tela, int y_meio_tela)
{
    float ang = 0;
    int x, y = 0;
    while(ang < PI / 4)
    {
        ang = std::asin((float)y/(float)r);
        x = r * std::cos(ang);

        glVertex2i(x + x_meio_tela, y + y_meio_tela); //1º Octante
        glVertex2i(y + x_meio_tela, x + y_meio_tela); //2º Octante
        glVertex2i(-y + x_meio_tela, x + y_meio_tela); //3º Octante
        glVertex2i(-x + x_meio_tela, y + y_meio_tela); //4º Octante
        glVertex2i(-x + x_meio_tela, -y + y_meio_tela); //5º Octante
        glVertex2i(-y + x_meio_tela, -x + y_meio_tela); //6º Octante
        glVertex2i(y + x_meio_tela, -x + y_meio_tela); //7º Octante
        glVertex2i(x + x_meio_tela, -y + y_meio_tela); //8º Octante

        y++;
    }
}

int main(){
    int altura = 600;
    int largura = 800;
    int nroVal = 10;
    int raioMin = 5;
    int raioMax = 200;
    int* raios = (int*)malloc(nroVal * sizeof(int));

    int** tempos = (int**)malloc(2 * sizeof(int*));
    tempos[0] = (int*)malloc(nroVal * sizeof(int));
    tempos[1] = (int*)malloc(nroVal * sizeof(int));

    for(int i = 0; i < nroVal; i++)
    {
        raios[i] = raioMin + i * (raioMax - raioMin)/nroVal;
    }

    GLFWwindow* window = nullptr; //cria um ponteiro nulo do tipo GLFW

    if(cria_janela(&window, largura, altura) != 0){
        std::cerr << "erro ao criar a janela" << std::endl;
        return -1;
    }

    //loop principal
    while(!glfwWindowShouldClose(window))
    {
        //renderizando
        glClear(GL_COLOR_BUFFER_BIT);

        //pixel vermelho
        glPointSize(3.0f);
        glColor3f(1.0f, 0.0f, 0.0f);
        
        glBegin(GL_POINTS);
        
        for(int i = 0; i < nroVal; i++)
        {        
            MidPointCircleInt(raios[i], largura/2, altura/2);
            CirculoPorTrigonometria(raios[i], largura/2, altura/2);
        }
        
        glEnd();
        //troca os buffer de cor para exibição correta
        glfwSwapBuffers(window);

        //escuta eventos: mouse, teclado, fechar janela e etc
        glfwPollEvents();
    }

    //exclui os ponteiros
    glfwTerminate();
    
    return 0;
}

// g++ alg_circ.cpp $(pkg-config --libs --cflags glfw3) -lGL