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
    int raioMin = 2;
    int raioMax = 300;
    int* raios = (int*)malloc(nroVal * sizeof(int));

    float** tempos = (float**)malloc(2 * sizeof(float*));
    tempos[0] = (float*)malloc(nroVal * sizeof(float));
    tempos[1] = (float*)malloc(nroVal * sizeof(float));

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
    //trocando a cor da janela 
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(01.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //renderizando
    glClear(GL_COLOR_BUFFER_BIT);

    //pixel vermelho
    glPointSize(3.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    
    glBegin(GL_POINTS);
    int qtd = 10000;
    int soma_inc = 0;
    int soma_trig = 0;
    for (int i=0; i < nroVal; i++){
        const auto tempo_iinc_0 = std::chrono::high_resolution_clock::now(); //inicio 

        for(int j = 0; j < qtd; j++)
        {   //std::cout <<"I: "<< i << std::endl;
            MidPointCircleInt(raios[i], largura/2, altura/2);
        }

        const auto tempo_iinc_1 = std::chrono::high_resolution_clock::now(); //final 
        tempos[0][i] = (float)std::chrono::duration_cast<std::chrono::microseconds>(tempo_iinc_1 -tempo_iinc_0).count()/(float)qtd; 

        const auto tempo_trig_0 = std::chrono::high_resolution_clock::now(); //inicio 
        for(int i = 0; i < nroVal; i++){
            CirculoPorTrigonometria(raios[i], largura/2, altura/2);
        }
        const auto tempo_trig_1 = std::chrono::high_resolution_clock::now(); //final 
        tempos[1][i] = (float)std::chrono::duration_cast<std::chrono::microseconds>(tempo_trig_1 -tempo_trig_0).count()/(float)qtd; 
        std::cout <<"Tempo Inc: " << tempos[0][i] << " - Tempo trig: " << tempos[1][i] << " - Raio: " << raios[i] << std::endl;

        //acumuladores 
        soma_inc += tempos[0][i];
        soma_trig += tempos[1][i];
    }
    glEnd();

    std::cout <<"Soma dos tempos totais para " << qtd << " repetições \n";
    std::cout<< soma_inc << " e  "<<  soma_trig << std::endl;
    float med_inc  = (float)soma_inc /(float)qtd;
    float med_trig = (float)soma_trig/(float)qtd;

    std::cout << "Tempo Médio Incremental: " << med_inc << std::endl;
    std::cout << "Tempo Médio Trigonometrico: "<< med_trig << std::endl;

    //troca os buffer de cor para exibição correta
    glfwSwapBuffers(window);

    while(!glfwWindowShouldClose(window))
    {
        //escuta eventos: mouse, teclado, fechar janela e etc
        glfwPollEvents();
    }
    
    //exclui os ponteiros
    glfwTerminate();
    free(tempos[0]);
    free(tempos[1]);
    
    return 0;
}

// g++ alg_circ.cpp $(pkg-config --libs --cflags glfw3) -lGL