#include <iostream>
#include <GLFW/glfw3.h>
//tutorial básico de como rodar uma janela no opnegl por C++
//float purple[3] = {1.0f, 0.0f, 1.0f};
float color[3] = {0.0f,0.0f,0.0f};

void change_window(GLFWwindow* window,int button,  int action, int mode){
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        if (color[0] == 0.0f){//se pressioionado, fica roxo
            color[0] = 1.0f;
            color[2] = 1.0f;
        }
        else{//se roxa, fica preto
            color[0] = 0.0f;
            color[2] = 0.0f;
        }
    }
}
int main(){

    //inicializando a biblioteca glfw
    if (!glfwInit()){
        return -1;
    }

    //Cria uma janela - no modo janela - e seu cntexto OpenGL
    int altura = 450;
    int largura = 800;
    GLFWwindow* window = glfwCreateWindow(largura, altura, "C++ OpenGL", NULL, NULL);

    //verificando a integridade
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // o contexto da janela passa a ser o atual - var window
    glfwMakeContextCurrent(window);

    //escuta o mouse
    glfwSetMouseButtonCallback(window, change_window);
    
    //loop até que o user feche a janela
    while(!glfwWindowShouldClose(window))
    {
        //definindo color
        glClearColor(color[0], color[1], color[2], 1.0f);
        //renderizando
        glClear(GL_COLOR_BUFFER_BIT);

        //troca os buffer de cor para exibição correta
        glfwSwapBuffers(window);

        //escuta eventos: mouse, teclado, fechar janela e etc
        glfwPollEvents();
    }

    //exclui os ponteiros
    glfwTerminate();
    return 0;
}

// g++ main.cpp -lglfw -lGL -lX11 -lpthread -lXrandr -ldl
// g++ main.cpp $(pkg-config --libs --cflags glfw3) -lGL
