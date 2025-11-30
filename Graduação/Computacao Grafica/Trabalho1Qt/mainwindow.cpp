#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "painter.h"

//Construtor da classe Principal
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) //inicializa a classe base
    , ui(new Ui::MainWindow) //inicializa a interface grafica
    , painter(Largura_Tela, Altura_Tela) //inicializa a jnalea com as dimensões pretendidas
{
    corAresta = Qt::red;
    corPreen = Qt::blue;
    grossuraContorno = 1;

    //configura a interface grafica de acordo com o padroes definidos acima
    ui->setupUi(this);

    //inicializando o canvas
    ui->myFrame->setPixmap(QPixmap::fromImage(painter.getImage()));
    ui->myFrame->setFixedSize(Largura_Tela, Altura_Tela);
    ui->myFrame->setScaledContents(true);

    //conectando os botoes com suas funções
    connect(ui->BtnIniciar, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
    connect(ui->BtnFechar, &QPushButton::clicked, this, &QMainWindow::close);
    connect(ui->button_apagar, &QPushButton::clicked, [this](){
        painter.clear();
        vertices.clear();
        arestas.clear();
        ui->myFrame->setPixmap(QPixmap::fromImage(painter.getImage()));
    });

    //cores
    connect(ui->btnLaranjaAresta, &QPushButton::clicked, [this](){
        corAresta = QColor(255, 165, 0);
        Redraw();
    });
    connect(ui->btnLaranjaPreen, &QPushButton::clicked, [this](){
        corPreen = QColor(255, 165, 0);
        Redraw();
    });
    connect(ui->btnAzulAresta, &QPushButton::clicked, [this](){
        corAresta = QColor(0, 0, 255);
        Redraw();
    });
    connect(ui->btnAzulPreen, &QPushButton::clicked, [this](){
        corPreen = QColor(0, 0, 255);
        Redraw();
    });
    connect(ui->btnVermelhoAresta, &QPushButton::clicked, [this](){
        corAresta = QColor(255, 0, 0);
        Redraw();
    });
    connect(ui->btnVermelhoPreen, &QPushButton::clicked, [this](){
        corPreen = QColor(255, 0, 0);
        Redraw();
    });
    connect(ui->btnAmareloAresta, &QPushButton::clicked, [this](){
        corAresta = QColor(255, 255, 0);
        Redraw();
    });
    connect(ui->btnAmareloPreen, &QPushButton::clicked, [this](){
        corPreen = QColor(255, 255, 0);
        Redraw();
    });
    connect(ui->btnVerdeAresta, &QPushButton::clicked, [this](){
        corAresta = QColor(0, 255, 0);
        Redraw();
    });
    connect(ui->btnVerdePreen, &QPushButton::clicked, [this](){
        corPreen = QColor(0, 255, 0);
        Redraw();
    });
    connect(ui->btnPretoAresta, &QPushButton::clicked, [this](){
        corAresta = QColor(0, 0, 0);
        Redraw();
    });
    connect(ui->btnPretoPreen, &QPushButton::clicked, [this](){
        corPreen = QColor(0, 0, 0);
        Redraw();
    });
    connect(ui->btnBrancoAresta, &QPushButton::clicked, [this](){
        corAresta = QColor(255, 255, 255);
        Redraw();
    });
    connect(ui->btnBrancoPreen, &QPushButton::clicked, [this](){
        corPreen = QColor(255, 255, 255);
        Redraw();
    });

    //grossura
    connect(ui->inputGrossura, &QSpinBox::valueChanged, [this](int value){
        grossuraContorno = value;
        Redraw();
    });
}

//Destrutor da classe prinicipal
MainWindow::~MainWindow()
{
    delete ui;
}
//configura o slot do botao inicial
void MainWindow::on_pushButton_clicked() {
    ui->stackedWidget->setCurrentIndex(1); // vai para a próxima tela
}
//configura o slot do botao fechar
void MainWindow::on_reset_clicked() {
    painter.clear(); //exclui o objeto painter
    ui->myFrame->setPixmap(QPixmap::fromImage(painter.getImage())); //encerra a tela
}

//Função que observa a posição e clique do mouse
void MainWindow::mousePressEvent(QMouseEvent* event)
{
    if(!ui->myFrame->geometry().contains(event->pos())){ //Clique fora do frame
        QMainWindow::mousePressEvent(event);
        return;
    }

    //Pega a posição do clique
    QPoint ponto = ui->myFrame->mapFromGlobal(event->globalPosition().toPoint());

    if (ponto.x() < 0 || ponto.x() >= Largura_Tela || ponto.y() < 0 || ponto.y() >= Altura_Tela){
        return;
    }

    vertices.push_back(ponto);

    int qtdVertices = vertices.size();
    if(qtdVertices >= 2)
    {
        //Conecta o vértice adicionado com o último
        arestas.push_back({qtdVertices-2, qtdVertices-1});

        //Se tiver o suficiente para um polígono
        if(qtdVertices > 2)
        {
            //Conecta o vértice com o primeiro
            arestas.push_back({0, qtdVertices-1});
        }
        //Se já era um polígono
        if(qtdVertices > 3)
        {
            //Remove a conexão do anterior com o primeiro
            arestas.erase(arestas.end() - 3);
        }
    }

    Redraw();
}

void MainWindow::Redraw()
{
    //Limpa a imagem
    painter.clear();

    if(!arestas.empty()){
        painter.draw_contorno(vertices, arestas, corAresta, grossuraContorno);
        //Polígono já verifica se tem arestas o suficiente
        painter.preencher_poligono(vertices, arestas, corPreen);
    }
    else
    {
        painter.draw_vertices(vertices, corAresta, grossuraContorno);
    }

    //Salva na tela a imagem desenhada
    ui->myFrame->setPixmap(QPixmap::fromImage(painter.getImage()));
}
