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
    int x, y, dx, dy, d, incE, incNE;
    //variação em x e y
    dx = x2 - x1;
    dy = y2 - y1;

    
    //valor inicial da variavel de decisao
    d = 2 * dy - dx;
    incE = 2 * dy;
    incNE = 2 * (dy - dx);
    x = x1;
    y = y1;

    //desenha o ponto inicial
    glVertex2i(x, y);
    
    while(x < x2){
        if (d <= 0) {
            //escolhe E
            d = d + incE;
            x = x + 1; //anda 1u em X

            }
        else { //escolhe NE
            d = d + incNE;
            y = y + 1;
        }
        glVertex2i(x, y);
    }
}

void alg_geral(int x1, int y1, int x2, int y2){
    //variação
    int dx = x2 - x1;
    int dy = y2 - y1;

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
        int inc_x, inc_y;
        if( x2 > x1)
        {
            inc_x = 1;
        }
        else{
            inc_x = -1;
        }
        if(y2 > y1){
            inc_y = 1;
        }
        else{
            inc_y = -1;
        }
        int aux_x = x1;
        int aux_y = y1;
        for(int i = 0; i <= abs(dx); i++){
            glVertex2i(aux_x, aux_y);
            aux_x += inc_x;
            aux_y+= inc_y;
        }
        return;
    }
    if (dx < 0) { // x é negativo
        std::swap(x1,x2);
        std::swap(y1,y2);
        dx = - dx;
        dy = -dy;
    }
    dx = x2 - x1;
    dy = y2 - y1;

    if (dy >= 0){ // oct 1 e 2
        if (dy <= dx){ // primeiro octante 0 < a <= 1
            desenha_oct1(x1, y1, x2, y2);
        
        }
        else{ // a > 1
            desenha_oct1(y1, x1, y2,x2); //refletimos os pontos sobre a identidade
        }
    
    }
    else{ //dy < 0 
        if(-dy <= dx){ // inclinação entre -1 < a < 0 _> reflexao sobre o eixo x
            desenha_oct1(x1, -y1, x2, -y2);
        }
        else{ // a < -1 -> refletimos sobre a segunda identidade y = -x
            desenha_oct1(y1, -x1, y2, -x2); //refeltimo o segundo octante
        }

    }

}
int main(){
    int  x1, x2;
    int  y1, y2;
     
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
         
         alg_geral(x1, y1, x2, y2);
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

