#include "painter.h"
#include <cmath>
Painter::Painter(int largura, int altura) : img(largura, altura, QImage::Format_RGB888){
    img.fill(Qt::white); //inicializa com o fundo branco
}

void Painter::clear(){
    img.fill(Qt::white);
}

void Painter::draw_point(int x, int y, QColor color){
    if( x >= 0 && x < img.width() && y >= 0 && y < img.height())
    {
        img.setPixel(x, y, color.rgb()); //desenha um ponto em x,y
    }
}

void Painter::draw_line(int x1, int y1, int x2, int y2, QColor color){
    float dx = x2 - x1;
    float dy = y2 - y1;
    float step = std::max(std::abs(dx), std::abs(dy));

    float inc_x = dx / step;
    float inc_y = dy/step;
    float x = x1;
    float y = y1;

    for(int i = 0; i<=step; i++){
        draw_point(x, y, color);
        x += inc_x;
        y += inc_y;
    }

}

//O eixo X é dominante, i. e., para retas mais horizontais
void Painter::desenha_oct1(int x1, int y1, int x2, int y2, QColor cor=Qt::red){
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
    draw_point(x, y,cor);


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

        draw_point(x, y, cor);
    }
}
//EIxo Y é o dominante, i.e., retas mais verticiais.
void Painter::desenha_oct2(int x1, int y1, int x2, int y2, QColor cor=Qt::red){
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
    draw_point(x, y, cor);

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

        draw_point(x, y, cor);
    }
}

void Painter::alg_geral(int x1, int y1, int x2, int y2, QColor cor=Qt::red){
    //variação
    int dx = x2 - x1;
    int dy = y2 - y1;

    if (x1 == x2 && y1 == y2){ //um ponto no plano
        draw_point(x1, y1, cor);
        return;
    }

    if (dx  == 0){ //reta vertical
        if (y1 > y2){
            std::swap(y1, y2);
        }
        for(int y = y1; y<=y2; y++)
        {
            draw_point(x1, y, cor);
        }
        return;
    }

    if (dy  == 0){ //reta horizontal
        if (x1 > x2){
            std::swap(x1, x2);
        }
        for(int x = x1; x<=x2; x++)
        {
            draw_point(x, y1, cor);
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
            draw_point(x1, y1, cor);
            x1 += inc_x;
            y1+= inc_y;
        }
        return;
    }

    float m = (float)dy/(float)dx;

    if (m <= 1 && m >= -1)
    {
        if (dx >= 0){
            desenha_oct1(x1, y1, x2, y2, cor);
        }
        else{
            desenha_oct1(x2, y2, x1, y1, cor);
        }
    }
    else
    {
        if (dy >= 0){
            desenha_oct2(x1, y1, x2, y2, cor);
        }
        else{
            desenha_oct2(x2, y2, x1, y1, cor);
        }
    }
}
QImage Painter::getImage() const{
    return img;
}
