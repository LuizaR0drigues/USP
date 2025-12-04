#include "camera.h"

Camera::Camera(){}

void Camera::init(int width, int height, bool modo)
{
    camera_posic = glm::vec3(0.0f, 0.0f, 3.0f);
    camera_front = glm::vec3(0.0f, 0.0f, -1.0f);
    //Direita = Frente x Y
    camera_right = glm::normalize(glm::cross(camera_front, glm::vec3(0.0f, 1.0f, 0.0f)));
    //Cima = Direita x Frente
    camera_up = glm::normalize(glm::cross(camera_right, camera_front));

    camera_veloc = 0.1f;
    rx = 0.0f;
    //yaw começa em -90° para a câmera encarar o z = -1
    ry = -90.0f;

    // variaveis do mouse
    first_mouse = false;
    sensibilidade = 0.1f;
    last_x = width / 2;
    last_y = height / 2;

    // variavel de modo de projecao
    //true = prespectiva
    //false = orto
    modo_perspec = modo;
}

//Função para analisar as teclas "não-texto" (setas, etc)
void Camera::teclas_especiais(int key, int x, int y)
{ 
    //Movimentação de translação da camera[(cima/baixo) e (esquerda/direita)]
    switch (key)
    {
    case GLUT_KEY_UP:
        camera_posic += camera_veloc * camera_up;
        break;
    case GLUT_KEY_DOWN:
        camera_posic -= camera_veloc * camera_up;
        break;
    case GLUT_KEY_LEFT:
        camera_posic -= camera_veloc * camera_right;
        break;
    case GLUT_KEY_RIGHT:
        camera_posic += camera_veloc * camera_right;
        break;
    default:
        break;
    }

    glutPostRedisplay();
}

//Para analisar as teclas "text" (wasd, +, -, etc)
void Camera::teclado(unsigned char key, int x, int y)
{
    //WASD -> rotação da câmera
    switch (key)
    {
    //Rotacao em x/cima
    case 'w':
    case 'W':
        rx += 5.0f;
        break;
    //Rotacao em x/baixo
    case 's':
    case 'S':
        rx -= 5.0f;
        break;
    //Rotacao em y/esquerda
    case 'a':
    case 'A':
        ry -= 5.0f;
        break;
    //Rotacao em y/direita
    case 'd':
    case 'D':
        ry += 5.0f;
        break;
    //Zoom da câmera
    case '+':
        camera_posic += camera_front * camera_veloc;
        break;
    case '-':
        camera_posic -= camera_front * camera_veloc;
        break;
    }

    glutPostRedisplay();
}

//Define a projeção que está sendo usada
void Camera::setProjecao(bool NovoModo){
    this->modo_perspec = NovoModo;
}

//Para ativar o modo de projeção atual
void Camera::modo_projecao(int width, int height)
{
    //Pega o aspecto da tela (16:9, 4:3, etc)
    float aspecto = (float)width / (float)height;

    glMatrixMode(GL_PROJECTION);
    glEnable(GL_DEPTH_TEST); 
    glLoadIdentity();

    //true = prespectiva
    //false = orto
    if (this->modo_perspec == MODO_PERSPEC)
    {
        //Cor do plano de fundo
        glClearColor(0.1, 0.0, 0.1f, 0.5f);
        //gluPerspective(campo de visão, aspecto, zPróximo, zLonge)
        gluPerspective(45.0f, aspecto, 0.1f, 100.0f);
    }
    else
    {
        //Tamanho da caixa de visualização
        float tam = 20.0f;
        //Cor do plano de fundo
        glClearColor(0.0, 0.0, 0.1f, 0.1f);

        //glOrtho(esquerda, direita, base, topo, zPróximo, zLonge)
        if (width >= height)
            glOrtho(-tam * aspecto, tam * aspecto, -tam, tam, -100.0f, 100.0f);
        else
            glOrtho(-tam, tam, -tam / aspecto, tam / aspecto, -100.0f, 100.0f);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//Para aplicar as mudanças na câmera
void Camera::aplica_parametro()
{
    //Calcula a nova frente
    glm::vec3 front;
    front.x = cos(glm::radians(ry)) * cos(glm::radians(rx));
    front.y = sin(glm::radians(rx));
    front.z = sin(glm::radians(ry)) * cos(glm::radians(rx));
    camera_front = glm::normalize(front);

    //Direita = Frente x Y
    camera_right = glm::normalize(glm::cross(camera_front, glm::vec3(0.0f, 1.0f, 0.0f)));
    //Cima = Direita x Frente
    camera_up = glm::normalize(glm::cross(camera_right, camera_front));

    //Calcula o alvo da câmera
    glm::vec3 alvo = camera_posic + camera_front;

    //gluLookAt(posicX, posicY, posicZ, alvoX, alvoY, alvoZ, upX, upY, upZ)
    gluLookAt(camera_posic.x, camera_posic.y, camera_posic.z, // onde estou
              alvo.x, alvo.y, alvo.z,                         // pra onde olho
              camera_up.x, camera_up.y, camera_up.z);         // define onde é "cima"
}

//Para transformar coordenadas do vértice e converter para coordenadas da janela, considerando a perspectiva
VerticesPhong Camera::transf_coord_tela(const VerticesPhong v, int largura, int altura, glm::mat4 model_matriz)
{
    VerticesPhong saida;

    //Matriz View
    glm::vec3 alvo = camera_posic + camera_front;
    glm::mat4 view = glm::lookAt(camera_posic, alvo, camera_up);

    //matriz de projecao
    float aspecto = (float)largura / (float)altura;
    glm::mat4 proj;

    if(modo_perspec == MODO_PERSPEC){
        proj = glm::perspective(glm::radians(45.0f), aspecto, 0.1f, 100.0f);
    }
    else{
        float tam = 20.0f;
        float esq, dir, baixo, cima;
        if(largura >= altura){
            esq = -tam * aspecto;
            dir = tam * aspecto;
            baixo = -tam;
            cima = tam;
        }
        else{
            esq = -tam ;
            dir = tam ;
            baixo = -tam/aspecto;
            cima = tam/aspecto;
        }
        proj = glm::ortho(esq, dir, baixo, cima, -100.0f, 100.0f);
    }

    //modelo = I
    glm::mat4 model(1.0f);
    glm::vec4 p_world(v.x, v.y, v.z, 1.0f);
    //transformação
    glm::vec4 viewP=  view * model_matriz * p_world;
    glm::vec4 corte = proj * viewP;

    if(corte.w != 0.0f){
        corte /= corte.w;
    }

    //tela ndc -> pixels
    saida.x = corte.x;
    saida.y = corte.y;
    saida.z = corte.z;

    glm::vec3 N(v.nx, v.ny, v.nz);

    glm::mat3 normalMatriz = glm::transpose(glm::inverse(glm::mat3(view * model_matriz)));
    glm::vec3 n2 = glm::normalize(normalMatriz * N);

    saida.nx = n2.x;
    saida.ny = n2.y;
    saida.nz = n2.z;

    return saida;

}

//Converte de coordenadas da câmera para coordenadas da janela
VerticesPhong Camera::toPixel(const VerticesPhong v, int largura, int altura){
    VerticesPhong s = v;
    s.x = (v.x * 0.5f + 0.5f) * largura;
    s.y = (v.y * 0.5f + 0.5f) * altura;
    return s;
}

glm::vec3 Camera::getCameraPosicao(){
    return camera_posic;
}

glm::vec3 Camera::getCameraFront(){
    return camera_front;
}

glm::vec3 Camera::getCameraUP(){
    return camera_up;
}

glm::vec3 Camera::getCameraRight(){
    return camera_right;
}