#include "painter.h"

//Construtor da classe
Painter::Painter(int largura, int altura) : img(largura, altura, QImage::Format_ARGB32){ //parametros iniciais
    img.fill(Qt::white); //inicializa com o fundo branco
}
//Destrutor da classe Painter
void Painter::clear(){
    img.fill(Qt::white);
}

void Painter::draw_point(int x, int y, QColor color, int grossura) {
    //Se grossura < 1, desenha apenas o ponto central
    if (grossura <= 1)
    {
        img.setPixelColor(x, y, color);
    }

    //Antialiasing de cone

    //Para todos os pontos em x na área quadrada ao redor
    for (int dx = -grossura; dx <= grossura; ++dx) {
        int px = x + dx;
        //Se fora da área de desenho
        if (px < 0 || px >= img.width())
            continue;

        //Para todos os pontos em y na área quadrada ao redor
        for (int dy = -grossura; dy <= grossura; ++dy) {
            int py = y + dy;

            //Se fora da área de desenho
            if (py < 0 || py >= img.height())
                continue;

            //Calcula a distância do centro
            float dist = std::sqrt(dx*dx + dy*dy);

            //Se estiver dentro da área permitida
            if (dist <= grossura) {
                //Calcula o alpha linearmente com a distância
                float alpha = 1.0f - dist / grossura;

                //Para evitar erros de arredondamento
                alpha = std::clamp(alpha, 0.0f, 1.0f);

                //Pega a cor do pixel que vai ser desenhado
                QColor dst(img.pixel(px, py));

                //Faz um blending das cores e alphas, para não sobrescrever os cálculos anteriores no pixel
                //https://en.wikipedia.org/wiki/Alpha_compositing
                float outAlpha = alpha + dst.alphaF() * (1.0f - alpha);
                float outR = (color.redF() * alpha + dst.redF() * dst.alphaF() * (1.0f - alpha)) / outAlpha;
                float outG = (color.greenF() * alpha + dst.greenF() * dst.alphaF() * (1.0f - alpha)) / outAlpha;
                float outB = (color.blueF() * alpha + dst.blueF() * dst.alphaF() * (1.0f - alpha)) / outAlpha;

                //Cor que deve ser usada
                QColor blended = QColor(outR * 255, outG * 255, outB * 255, outAlpha * 255);

                //Pinta o pixel
                img.setPixelColor(px, py, blended);
            }
        }
    }
}
//desenha um ponto na tela
void Painter::draw_point(QPoint ponto, QColor color, int grossura)
{
    draw_point(ponto.x(), ponto.y(), color, grossura);
}

//O eixo X é dominante, i. e., para retas mais horizontais
void Painter::desenha_oct1(int x1, int y1, int x2, int y2, QColor cor=Qt::red, int grossura){
    int x, y, dx, dy, d, incE, incNE, incY = 1;

    //variação em x e y
    dx = x2 - x1;
    dy = y2 - y1;

    //Se a reta diminui em Y
    if(dy < 0)
    {
        //Inverte a direção de crescimento
        incY = -1;
        //Inverte dy para não atrapalhar as contas
        dy *= -1;
    }

    //valor inicial da variavel de decisao
    d = 2 * dy - dx;
    incE = 2 * dy;
    incNE = 2 * (dy - dx);
    x = x1;
    y = y1;

    //desenha o ponto inicial
    draw_point(x, y, cor, grossura);


    while(x < x2){
        if (d <= 0) {
            //escolhe E
            d += incE;
            x++; //anda 1 unidade em X
        }
        else { //escolhe NE
            d += incNE;
            x++;
            y += incY;
        }

        draw_point(x, y, cor, grossura);
    }
}

//EIxo Y é o dominante, i.e., retas mais verticiais.
void Painter::desenha_oct2(int x1, int y1, int x2, int y2, QColor cor=Qt::red, int grossura){
    int x, y, dx, dy, d, incE, incNE, incX = 1;

    //variação em x e y
    dx = x2 - x1;
    dy = y2 - y1;

    //Se a reta diminui em X
    if(dx < 0)
    {
        //Inverte a direção de crescimento
        incX = -1;
        //Inverte dy para não atrapalhar as contas
        dx *= -1;
    }

    //valor inicial da variavel de decisao
    d = 2 * dx - dy;
    incE = 2 * dx;
    incNE = 2 * (dx - dy);
    x = x1;
    y = y1;

    //desenha o ponto inicial
    draw_point(x, y, cor, grossura);

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

        draw_point(x, y, cor, grossura);
    }
}

void Painter::draw_line(QPoint ponto1, QPoint ponto2, QColor cor, int grossura){
    int x1 = ponto1.x();
    int y1 = ponto1.y();
    int x2 = ponto2.x();
    int y2 = ponto2.y();

    //variação
    int dx = x2 - x1;
    int dy = y2 - y1;

    if (x1 == x2 && y1 == y2){ //um ponto no plano
        draw_point(x1, y1, cor, grossura);
        return;
    }

    if (dx  == 0){ //reta vertical
        if (y1 > y2){
            std::swap(y1, y2);
        }
        for(int y = y1; y<=y2; y++)
        {
            draw_point(x1, y, cor, grossura);
        }

        return;
    }

    if (dy  == 0){ //reta horizontal
        if (x1 > x2){
            std::swap(x1, x2);
        }
        for(int x = x1; x<=x2; x++)
        {
            draw_point(x, y1, cor, grossura);
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
            draw_point(x1, y1, cor, grossura);
            x1 += inc_x;
            y1+= inc_y;
        }
        return;
    }

    float m = (float)dy/(float)dx;

    if (m <= 1 && m >= -1)
    {
        if (dx >= 0){
            desenha_oct1(x1, y1, x2, y2, cor, grossura);
        }
        else{
            desenha_oct1(x2, y2, x1, y1, cor, grossura);
        }
    }
    else
    {
        if (dy >= 0){
            desenha_oct2(x1, y1, x2, y2, cor, grossura);
        }
        else{
            desenha_oct2(x2, y2, x1, y1, cor, grossura);
        }
    }
}

void Painter::draw_vertices(vector<QPoint> vertices, QColor cor, int grossura)
{
    for(QPoint vert : vertices)
        draw_point(vert, cor, grossura);
}

void Painter::draw_contorno(vector<QPoint> vertices, vector<array<int, 2>> arestas, QColor cor, int grossura)
{
    for(array<int, 2> arr : arestas)
    {
        draw_line(vertices[arr[0]], vertices[arr[1]], cor, grossura);
    }
}

void Painter::OrdenaPorX(vector<DadosET>* nivel)
{
    sort(nivel->begin(), nivel->end(),
         [](const DadosET &a, const DadosET &b)
         {
             return a.xMin < b.xMin;
         });
}

ET* Painter::CriaET(vector<QPoint> vertices, vector<array<int, 2>> arestas)
{
    //Pega o primeiro valor, apenas para poder pular a primeira iteração do loop
    float yMin = vertices[0].y();
    float yMax = yMin;
    for(QPoint ver : vertices)
    {
        //Se for o primeiro, pula ele, pois é a referência inicial
        if(ver == vertices[0])
            continue;

        if(ver.y() < yMin)
            yMin = ver.y();

        if(ver.y() > yMax)
            yMax = ver.y();
    }

    int yMinInt = (int)(ceil(yMin));
    int yMaxInt = (int)(floor(yMax));
    int nroNiveis = yMaxInt - yMinInt;

    ET* listaET = new ET();
    listaET->yMin = yMinInt;
    listaET->nroNiveis = nroNiveis;
    //Cria um ponteiro com nroNiveis vetores de DadosET
    listaET->lista = new vector<DadosET>[nroNiveis];

    for(array<int, 2> ar : arestas)
    {
        QPoint ver1;
        QPoint ver2;

        //Verifica qual é o vértice com menor Y
        if(vertices[ar[0]].y() > vertices[ar[1]].y())
        {
            ver1 = vertices[ar[1]];
            ver2 = vertices[ar[0]];
        }
        else
        {
            ver1 = vertices[ar[0]];
            ver2 = vertices[ar[1]];
        }

        int indice = ceil(ver1.y()) - listaET->yMin;
        float m = (float)(ver2.y() - ver1.y())/(float)(ver2.x() - ver1.x());
        //Retas horizontais tem m==0, o algoritmo não precisa tratar elas
        if(m == 0)
            continue;

        listaET->lista[indice].push_back({ (int)ceil(ver2.y()), (float)ver1.x(), 1.0f/m });
    }

    //Deixa a lista pré-ordenada
    for(int i = 0; i < listaET->nroNiveis; i++)
    {
        if(!listaET->lista[i].empty())
        {
            OrdenaPorX(&(listaET->lista[i]));
        }
    }

    return listaET;
}

void Painter::PreenchimentoDePoligonos(ET* listaET, QColor cor)
{
    vector<DadosET> listaAET;
    for(int i = 0; i < listaET->nroNiveis; i++)
    {
        int yNivel = i + listaET->yMin;
        for(int j = 0; j < (int)listaAET.size(); j++)
        {
            //Se a iteração está no nível ou acima do y máximo da aresta
            if(listaAET[j].yMax <= yNivel)
            {
                //Remove ela
                listaAET.erase(listaAET.begin() + j);
                j--;
                continue;
            }

            //Calcula o ponto X da aresta no nível atual
            listaAET[j].xMin += listaAET[j].mInverso;
        }

        //Move todos os dados do nível pra lista AET
        listaAET.insert(listaAET.end(),
                        make_move_iterator(listaET->lista[i].begin()),
                        make_move_iterator(listaET->lista[i].end()));

        //Limpa o nível original
        listaET->lista[i].clear();

        //Reordena a lista
        OrdenaPorX(&listaAET);

        int verticesCruzados = 0;
        for(int x = ceil(listaAET[0].xMin); x < ceil(listaAET.back().xMin); x++)
        {
            //Para contar cada aresta cruzada no nível
            //Como AET está ordenada em X, então basta sempre verificar o próximo
            while(x >= listaAET[verticesCruzados].xMin)
                verticesCruzados++;

            if(verticesCruzados % 2 == 1)
            {
                draw_point(x, yNivel, cor);
            }
        }
    }
}

void Painter::preencher_poligono(vector<QPoint> vertices, vector<array<int, 2>> arestas, QColor cor)
{
    if(arestas.size() > 2)
    {
        ET* listaET = CriaET(vertices, arestas);
        PreenchimentoDePoligonos(listaET, cor);
        delete[] listaET->lista;
        delete listaET;
    }
}

QImage Painter::getImage() const{
    return img;
}
