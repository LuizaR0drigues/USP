#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <vector>
#include <array>

#include "painter.h"

#define Largura_Tela 710
#define Altura_Tela 500

using namespace std;


QT_BEGIN_NAMESPACE

namespace Ui {
    class MainWindow;
}

QT_END_NAMESPACE
//Classe responsavel por gerenciar a janela
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //definição da janela
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    //função que observa a posição do mouse
    void mousePressEvent(QMouseEvent* event)override ;
private slots:
    //slots iniciar e fechar janela
    void on_pushButton_clicked();
    void on_reset_clicked();
private:
    //definição da interface
    Ui::MainWindow *ui;

    //cria um objeto Painter que gerencia o canvas
    Painter painter;

    //cor da aresta e preenchimento
    QColor corAresta, corPreen;

    //espessura da linha
    int grossuraContorno;

    //vetor de pontos responsavel por armazenar os vertices e array de aresta do poligonos
    vector<QPoint> vertices;
    vector<array<int, 2>> arestas;

    //mantem a tela sempre atualizada
    void Redraw();
};
#endif // MAINWINDOW_H
