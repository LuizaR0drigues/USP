#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QColor>

class Painter  {

public:
    Painter(int largura = 800, int altura = 600);

    void draw_point(int x, int y, QColor color = Qt::darkMagenta);
    void draw_line(int x1, int y1, int x2, int y2, QColor color);
    void desenha_oct1(int x1, int y1, int x2, int y2, QColor cor);
    void desenha_oct2(int x1, int y1, int x2, int y2, QColor cor);
    void alg_geral(int x1, int y1, int x2, int y2, QColor cor);

    QImage getImage() const;
    void clear();
private:
    QImage img;

};

#endif // PAINTWIDGET_H
