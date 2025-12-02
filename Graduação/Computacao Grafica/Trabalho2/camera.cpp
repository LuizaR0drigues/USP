#include "camera.h"

Camera::Camera(){}

void Camera::init(int width, int height, bool modo)
{
    camera_posic = glm::vec3(0.0f, 0.0f, 3.0f);
    camera_front = glm::vec3(0.0f, 0.0f, -1.0f);
    camera_up = glm::vec3(0.0f, 1.0f, 0.0f);
    camera_veloc = 0.1f;
    rx = 0.0f;
    ry = -90.0f;

    // variaveis do mouse
    first_mouse = false;
    sensibilidade = 0.1f;
    last_x = width / 2;
    last_y = height / 2;

    // variavel de modo de projecao
    modo_perspec = modo; // true=prespectiva e false = orto
}

void Camera::teclas_especiais(int key, int x, int y)
{ // movimentação de translação da camera[(baixo/cima) e (esquerda/direita)]
    switch (key)
    {
    case GLUT_KEY_UP:
        camera_posic.y += camera_veloc;
        break;
    case GLUT_KEY_DOWN:
        camera_posic.y -= camera_veloc;
        break;
    case GLUT_KEY_LEFT:
        camera_posic.x -= camera_veloc;
        break;
    case GLUT_KEY_RIGHT:
        camera_posic.x += camera_veloc;
        break;
    default:
        break;
    }

    glutPostRedisplay();
}

void Camera::teclado(unsigned char key, int x, int y)
{
    // Rotação WASD
    switch (key)
    {
    case 'w':
    case 'W': // rotacao em x/cima
        rx -= 5.0f;
        break;
    case 's':
    case 'S': // baixo
        rx += 5.0f;
        break;
    case 'a':
    case 'A': // rotação em y /esquerda
        ry += 5.0f;
        break;
    case 'd':
    case 'D': // direita
        ry -= 5.0f;
        break;
    // efeito zoom da camera
    case '+':
        camera_posic += camera_front * camera_veloc;
        break;
    case '-':
        camera_posic -= camera_front * camera_veloc;
        break;
    }
    glutPostRedisplay();
}

void Camera::processa_mouse(float window, float xpos, float ypos)
{
    // mouse nao acionado
    if (!first_mouse)
        return;

    if (first_mouse)
    {
        last_x = xpos;
        last_y = ypos;
        first_mouse = false;
    }
    // deslocamento do louse em relação a ultima posi conhecida
    float xoffset = xpos - last_x;
    float yoffset = last_y - ypos;

    // atualiza com a ultima coordeanda
    last_x = xpos;
    last_y = ypos;

    xoffset *= sensibilidade;
    yoffset *= sensibilidade;

    // atualiza os angulos de orientação da camera
    rx += yoffset;
    ry += xoffset;

    // limita o pitch
    if (rx > 89.0)
    {
        rx = 89.0;
    }
    else if (rx < -89.0)
    {
        rx = -89.0;
    }

    
}

void Camera::setProejcao(bool NovoModo){
    this->modo_perspec = NovoModo;
}
void Camera::modo_projecao(int width, int height)
{

    float aspecto = (float)width / (float)height;

    // matriz de projecao
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_DEPTH_TEST); 
    glLoadIdentity();

    if (this->modo_perspec)
    {
        // projeção perspectiva
        glClearColor(0.1, 0.0, 0.1f, 0.5f); // plano de fundo
        gluPerspective(45.0f, aspecto, 0.1f, 100.0f);
    }
    else
    {
        // projecao ortografica
        float tam = 20.0f;                  // tamanho da caixa de visualização
        glClearColor(0.0, 0.0, 0.1f, 0.1f); // plano de fundo

        if (width >= height) // largura domina
            glOrtho(-tam * aspecto, tam * aspecto, -tam, tam, -100.0f, 100.0f);
        else // altura domina
            glOrtho(-tam, tam, -tam / aspecto, tam / aspecto, -100.0f, 100.0f);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Camera::aplica_paramtero()
{
    glm::vec3 front;
    front.x = cos(glm::radians(ry)) * cos(glm::radians(rx));
    front.y = sin(glm::radians(rx));
    front.z = sin(glm::radians(ry)) * cos(glm::radians(rx));
    camera_front = glm::normalize(front);

    glm::vec3 alvo = camera_posic + camera_front;

    // cam (posicX, posicY, posicZ, alvoX, alvoY, alvoZ, upX, upY, upZ)
    gluLookAt(camera_posic.x, camera_posic.y, camera_posic.z, // onde estou
              alvo.x, alvo.y, alvo.z,                         // pra onde olho
              camera_up.x, camera_up.y, camera_up.z);         // define onde é "cima"
}

Vertices Camera::transf_coord_tela(const Vertices v, int largura, int altura){
    Vertices saida;

    //Matriz View
    glm::vec3 alvo = camera_posic + camera_front;
    glm::mat4 view = glm::lookAt(camera_posic, alvo, camera_up);

    //matriz de porjecao
    float aspecto = (float)largura / (float)altura;
    glm::mat4 proj;

    if(modo_perspec){
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
    glm::vec4 viewP=  view * model * p_world;
    glm::vec4 corte = proj * viewP;

    if(corte.w != 0.0f){
        corte /= corte.w;
    }

    //tela ndc -> pixels
    saida.x = corte.x;
    saida.y = corte.y;
    saida.z = corte.z;

    glm::vec3 N(v.nx, v.ny, v.nz);

    glm::mat3 normalMatriz = glm::transpose(glm::inverse(glm::mat3(view * model)));
    glm::vec3 n2 = glm::normalize(normalMatriz * N);

    saida.nx = n2.x;
    saida.ny = n2.y;
    saida.nz = n2.z;

    return saida;

}
Vertices Camera::toPixel(const Vertices v, int largura, int altura){
    Vertices s = v;
    s.x = (v.x * 0.5f + 0.5f) * largura;
    s.y = (v.y * 0.5f + 0.5f) * altura;
    return s;
}
glm::vec3 Camera::getCameraFronte(){
    return camera_front;
}

glm::vec3 Camera::getCameraPosicao(){
    return camera_posic;
}

glm::vec3 Camera::getCameraUP(){
    return camera_up;
}