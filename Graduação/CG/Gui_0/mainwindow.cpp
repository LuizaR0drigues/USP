#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "painter.h"
#include <QDebug>
#include <QMouseEvent>


QColor cor = Qt::red;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , painter(800, 600)

{
    ui->setupUi(this);

    //inicializando o canvas
    ui->myFrame->setPixmap(QPixmap::fromImage(painter.getImage()));
    ui->pushButton_3->setText("Iniciar");
    ui->pushButton_4->setText("Fechar");

    //conectando os botoes com suas funções
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &QMainWindow::close);
    connect(ui->button_apagar, &QPushButton::clicked, [this](){painter.clear();
        vertices.clear();
         ui->myFrame->setPixmap(QPixmap::fromImage(painter.getImage()));
    });
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


    if(!ui->myFrame->geometry().contains(event->pos())){ //o movimento esta fora do frame
        QMainWindow::mousePressEvent(event);//saimos do movimeno atual
        return;
    }

    QPoint pos = ui->myFrame->mapFromParent(event->pos());
    int x_pos = pos.x();
    int y_pos = pos.y();
    QPoint ponto (x_pos, y_pos);

    if (x_pos < 0 || x_pos >= 800 || y_pos < 0 || y_pos >= 600){
        qDebug() << "Coordenadas fora do limite do frame!";
        return;
    }
    if( event ->button() ==Qt::RightButton && !vertices.isEmpty()){
        //fecha o poligono
        painter.draw_line(vertices.last().x(), vertices.last().y(), vertices.first().x(),vertices.first().y(), cor);
        vertices.clear(); //começa um novo poligono
    }
    else{
        if(!vertices.isEmpty()){
            painter.draw_line(vertices.last().x(), vertices.last().y(), ponto.x(),ponto.y(), cor);
        }

           vertices.append(ponto);

            qDebug()<<"Click: " << x_pos << y_pos;
    }

    ui->myFrame->setPixmap(QPixmap::fromImage(painter.getImage()));

}
