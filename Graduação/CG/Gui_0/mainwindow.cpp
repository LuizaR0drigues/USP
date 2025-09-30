#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "painter.h"
#include <QDebug>
#include <QMouseEvent>

int verticeX [50];
int verticeY[50];
int verticeIndex = 0;
QColor cor = Qt::red;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , painter(800, 800)

{
    ui->setupUi(this);

    //inicializando o canvas
    ui->myFrame->setPixmap(QPixmap::fromImage(painter.getImage()));
    ui->pushButton_3->setText("Iniciar");
    ui->pushButton_4->setText("Fechar");

    //conectando os botoes com suas funções
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &QMainWindow::close);
    connect(ui->button_apagar, &QPushButton::clicked, [this](){painter.clear(); ui->myFrame->setPixmap(QPixmap::fromImage(painter.getImage())); });
    //cores
    connect(ui->toolButton, &QPushButton::clicked, this, &MainWindow::orange_clicked);
    connect(ui->toolButton_2, &QPushButton::clicked, this, &MainWindow::yellow_clicked);
    connect(ui->toolButton_3, &QPushButton::clicked, this, &MainWindow::blue_clicked);
    connect(ui->toolButton_4, &QPushButton::clicked, this, &MainWindow::red_clicked);
    connect(ui->toolButton_5, &QPushButton::clicked, this, &MainWindow::green_clicked);
    connect(ui->toolButton_6, &QPushButton::clicked, this, &MainWindow::black_clicked);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_clicked() {
    ui->stackedWidget->setCurrentIndex(1); // vai para a próxima tela
}
void MainWindow::on_draw_clicked() {
    // desenha uma linha laranja
    painter.draw_line(100, 100, 200, 200, QColor(255,165,0));

    // atualiza o QLabel
    ui->myFrame->setPixmap(QPixmap::fromImage(painter.getImage()));
}

void MainWindow::on_reset_clicked() {
    painter.clear();
    ui->myFrame->setPixmap(QPixmap::fromImage(painter.getImage()));
}

void MainWindow::orange_clicked(){
    cor = QColor(255, 165, 0);
}
void MainWindow::blue_clicked(){
    cor = QColor(0, 0, 255);
}
void MainWindow::red_clicked(){
    cor = QColor(255, 0, 0);
}
void MainWindow::yellow_clicked(){
    cor = QColor(255, 255, 0);
}
void MainWindow::green_clicked(){
    cor = QColor(0, 255, 0);
}

void MainWindow::black_clicked(){
    cor = QColor(0, 0, 0);

}

void MainWindow::mousePressEvent(QMouseEvent* event){
    QPoint pos = ui->myFrame->mapFromParent(event->pos());
    int x_pos = pos.x();
    int y_pos = pos.y();

    if( event ->button() ==Qt::RightButton && verticeIndex >0){
        //fecha o poligono
        painter.alg_geral(verticeX[verticeIndex-1], verticeY[verticeIndex-1], verticeX[0],verticeY[0], cor);
        verticeIndex = 0; //começa um novo poligono
    }
    else{
        if(verticeIndex > 0 ){
            painter.alg_geral(verticeX[verticeIndex-1], verticeY[verticeIndex-1], x_pos, y_pos, cor);
        }

            verticeX[verticeIndex] = x_pos;
            verticeY[verticeIndex] = y_pos;
            verticeIndex++;
            //desenha uma dos lados do poligono
            qDebug()<<"Click: " << x_pos << y_pos;
    }

    ui->myFrame->setPixmap(QPixmap::fromImage(painter.getImage()));

}
