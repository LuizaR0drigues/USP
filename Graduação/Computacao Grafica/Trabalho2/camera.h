#ifndef CAMERA_H
#define CAMERA_H

#include "vertices.h"
#include "include/glad/glad.h"
#include <GL/freeglut.h>
#include <glm/glm.hpp>//realiza calculos matematicaos pro gl
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include <vector>



class Camera{
    public:
    Camera();
    void init(int width, int height,  bool modo);
    void modo_projecao(int width, int height);
    void teclado(unsigned char key, int x, int y);
    void teclas_especiais(int key, int x, int y);
    void processa_mouse(float window, float xpos, float ypos);
    void aplica_paramtero();
    Vertices transf_coord_tela(const Vertices V, int largura, int altura, glm::mat4 model_matriz);
    Vertices toPixel(const Vertices v, int largura, int altura);
    void setProejcao(bool NovoModo);
    glm::vec3 getCameraPosicao();
    glm::vec3 getCameraFronte();
    glm::vec3 getCameraUP();

    private:
    //posicao e orientação
     glm::vec3 camera_posic;
     glm::vec3 camera_front; //visao do obsv
     glm::vec3 camera_up;
     float camera_veloc = 0.01f;
     float rx, ry;
     bool first_mouse, modo_perspec = true;
     float sensibilidade, last_x,last_y;

};


#endif