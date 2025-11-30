#include <iostream>
#include <stdio.h>
#include <utility>
#include <GLFW/glfw3.h>
#include <algorithm>
#include <cmath>


int cria_janela(GLFWwindow** window, int largura, int altura){
     //inicializando a biblioteca glfw
    if (!glfwInit()){
        return -1;
    }
    //Cria uma janela - no modo janela - e seu cntexto OpenGL
    
    *window = glfwCreateWindow(largura, altura, "Desenhando retas - met analitico", NULL, NULL);
    
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
//desenhando uma reta de forma analitica

/*
std::pair<float, float> convert_coord(int x, int y, int largura, int altura){
    float x_ndc = (2.0f * x /largura ) - 1.0f;
    float y_ndc = (2.0f * y/ altura) - 1.0f;
    return {x_ndc, y_ndc};
}*/

int main(){
    int x, x1, x2;
    int y, y1, y2;
     
    int altura = 600;
    int largura = 800;
    std::cin >> x1 >> y1 >> x2 >> y2;
   
   
    //criando a janela
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
         
         int var_x = x2 - x1;
         int var_y = y2 - y1;

         
        if(std::abs(var_y) >= std::abs(var_x)){
            if(y1 > y2){
                std::swap(x1,x2);
                std::swap(y1,y2);
            }
            if (var_y == 0){
                glVertex2f(x1, y1);
            }
            else if (var_x == 0)
            { //uma reta vertical
                for(y=y1; y<= y2; y++){
                    
                    glVertex2f(x1, y);
                }
        }
        else
            {
                float a = (float)var_x/(float)var_y;
                float b = x1 - a * y1;
                for(y=y1; y<= y2; y++)
                {
                x = (int)round(a*y+b);
                    
                    glVertex2f(x, y);
                }

                
                }
            }
            else{
                if(x1 > x2){
                    std::swap(x1,x2);
                    std::swap(y1,y2);
                }
                var_x = x2 - x1;
                var_y = y2 - y1;
                
                float a  = (float)var_y / (float)var_x;
                float b = y1 - a*x1;

                for(x=x1; x<= x2; x++)
                {
                    y = (int)(round(a*x + b));
                    
                    glVertex2f(x, y);
                }
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

