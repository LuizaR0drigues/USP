#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QColor>
#include <vector>
#include <array>
#include <cmath>

using namespace std;

//Struct para salvar os dados da lista ET
struct DadosET
{
    int yMax;
    float xMin;
    float mInverso;
};

//Struct para salvar a ET
struct ET
{
    int yMin, nroNiveis;
    vector<DadosET>* lista;
};

class Painter  {

public:
    Painter(int largura = 800, int altura = 600);

    void clear();
    //Primitivas
    void draw_point(int x, int y, QColor color = Qt::blue, int grossura = 1);
    void draw_point(QPoint ponto, QColor color = Qt::blue, int grossura=1);
    void draw_line(QPoint ponto1, QPoint ponto2, QColor cor = Qt::red, int grossura=1);

    //Iniciam os algoritmos
    void draw_vertices(vector<QPoint> vertices, QColor cor = Qt::blue, int grossura=1);
    void draw_contorno(vector<QPoint> vertices, vector<array<int, 2>> arestas, QColor cor = Qt::red, int grossura=1);
    void preencher_poligono(vector<QPoint> vertices, vector<array<int, 2>> arestas, QColor cor = Qt::blue);

    QImage getImage() const;
private:
    QImage img;

    //Para desenhar as linhas
    void desenha_oct1(int x1, int y1, int x2, int y2, QColor cor, int grossura=1);
    void desenha_oct2(int x1, int y1, int x2, int y2, QColor cor, int grossura=1);

    //Para ordenar os níveis
    void OrdenaPorX(vector<DadosET>* nivel);
    //Para o algoritmo de preenchimento de polígonos
    ET* CriaET(vector<QPoint> vertices, vector<array<int, 2>> arestas);
    void PreenchimentoDePoligonos(ET* listaET, QColor cor);
};

#endif // PAINTWIDGET_H
