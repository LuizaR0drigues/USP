#ifndef CAMERA_H
#define CAMERA_H

#include "structs.h"
#include "glad/glad.h"
#include <GL/freeglut.h>
#include <glm/glm.hpp>//realiza calculos matematicaos pro gl
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include <vector>

#define MODO_ORTO false
#define MODO_PERSPEC true

class Camera{
    public:
    Camera();
    void init(int width, int height,  bool modo);
    void modo_projecao(int width, int height);
    void teclado(unsigned char key, int x, int y);
    void teclas_especiais(int key, int x, int y);
    void aplica_parametro();
    VerticesPhong transf_coord_tela(const VerticesPhong V, int largura, int altura, glm::mat4 model_matriz);
    VerticesPhong toPixel(const VerticesPhong v, int largura, int altura);
    void setProjecao(bool NovoModo);
    glm::vec3 getCameraPosicao();
    glm::vec3 getCameraFront();
    glm::vec3 getCameraUP();
    glm::vec3 getCameraRight();

    private:
    //posicao e orientação
     glm::vec3 camera_posic;
     glm::vec3 camera_front; //visao do obsv
     glm::vec3 camera_up;
     glm::vec3 camera_right;
     float camera_veloc = 0.01f;
     float rx, ry;
     bool first_mouse, modo_perspec = true;
     float sensibilidade, last_x,last_y;

};


#endif