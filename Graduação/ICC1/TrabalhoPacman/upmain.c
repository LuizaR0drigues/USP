#include <stdio.h>
#include <stdlib.h>
#include <string.h>      //  memcpy
#include <conio.h>       // _kbhit, _getch
#include <windows.h>
#include <time.h>    //  cls

#define SPEED 50

#define LINHAS 24
#define COLUNAS 38
#define CHAR_PACMAN 'P'
#define CHAR_FANT 'F'

void cls(HANDLE hConsole)
{
    COORD coordScreen = { 0, 0 };    // home for the cursor
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;

    // Get the number of character cells in the current buffer.
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return;
    }

    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    // Fill the entire screen with blanks.
    if (!FillConsoleOutputCharacter(hConsole,        // Handle to console screen buffer
                                    (TCHAR)' ',      // Character to write to the buffer
                                    dwConSize,       // Number of cells to write
                                    coordScreen,     // Coordinates of first cell
                                    &cCharsWritten)) // Receive number of characters written
    {
        return;
    }

    // Get the current text attribute.
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return;
    }

    // Set the buffer's attributes accordingly.
    if (!FillConsoleOutputAttribute(hConsole,         // Handle to console screen buffer
                                    csbi.wAttributes, // Character attributes to use
                                    dwConSize,        // Number of cells to set attribute
                                    coordScreen,      // Coordinates of first cell
                                    &cCharsWritten))  // Receive number of characters written
    {
        return;
    }

    // Put the cursor at its home coordinates.
    SetConsoleCursorPosition(hConsole, coordScreen);
}
//função que carregara o mapa
void carrega_mapa(char matriz[LINHAS][COLUNAS])
{
    FILE *arq;
    int lin, col;
    int i,j;
    char linha[COLUNAS];
    lin =0;
    col=0;

    //abrindo arquivo
    arq=fopen("mapa2.txt","r");
    if(!arq)
    {
        printf("\nErro de entrada na abertura do arquivo!");
        exit(1);
    }
    //fscanf(arq,"%d %d\n",&lin,&col);
    //verificando os tamanhos do arquivo
    /*printf("linha: %d", lin);
    printf("COl: %d", col);*/
    lin  =0;
    col=0;
    /*if(lin >LINHAS && col>COLUNAS)
    {
        printf("\n##ERRO: Arquivo de entrada incompativel! \n\n");
        exit(1);
    }*/
    for(i=0; i<LINHAS; i++)
    {
        fgets(linha,COLUNAS+1,arq);
        linha[strcspn(linha, "\n")] = 0;
        for(j=0; j<COLUNAS; j++)
        {
            matriz[i][j]=linha[j];
        }
    }

    fclose(arq);
}
typedef struct
{
    int x;
    int y;
    int status;
} PACMAN;

typedef struct
{
    int x;
    int y;
    int status;
} FANT;

void move(PACMAN *p,char move,char tabuleiro[LINHAS][COLUNAS])
{
    int px = p->x;
    int py = p->y;
    switch(move)
    {
    case 'w':
        (py)--;
        break;
    case 's':
        (py)++;
        break;
    case 'a':
        (px)--;
        break;
    case 'd':
        (px)++;
        break;
    }
    // verifica se não está bloqueado
    if(px<COLUNAS && py<LINHAS && px>=0 && py>=0)
    {
        if(tabuleiro[py][px]!='#')
        {
            p->x = px;
            p->y = py;
        }
    }
    else
    {
        //teleporta pro outro lado

    }if(px<0)
        {
            p->x = COLUNAS-1;
        }
        if(py<0)
        {
            p->y = LINHAS-1;
        }
        if(px>=COLUNAS)
        {
            p->x = 0;
        }
        if(py>=LINHAS)
        {
            p->y = 0;
        }
}

void moveFantasma(FANT *f, char tabuleiro[LINHAS][COLUNAS])
{
    int px = f->x;
    int py =f->y;
    int movef;
    while(1){
        px = f->x;
        py =f->y;
        movef = rand()%4;
        printf("%d %d\n",movef,rand());
        //0 subir, 1 direita, 2 descer, 3 esquerda
        switch(movef)
        {
        case 0:
            py--;
            break;
        case 1:
            px++;
            break;
        case 2:
            py++;
            break;
        case 3:
            px--;
            break;
        }
        //verifica se o fantasma estra dentro do mapa
        if(px<COLUNAS && py<LINHAS && px>=0 && py>=0)
        {
            if(tabuleiro[py][px]!='#')
            {
                f->x = px;
                f->y = py;
            }else{
                continue;
            }
        }
        else{
            if(px<0)
            {
                f->x = COLUNAS-1;
            }
            if(py<0)
            {
                f->y = LINHAS-1;
            }
            if(px>=COLUNAS)
            {
                f->x = 0;
            }
            if(py>=LINHAS)
            {
                f->y = 0;
            }
        }
        break;
    }

}

void moveFantasmasegue(FANT *f, PACMAN *p,char tabuleiro[LINHAS][COLUNAS])
{
    int px = f->x;
    int py = f->y;
    int movef;
    int dx,dy;
    int mode = 0;
    while(1){
        px = f->x;
        py =f->y;
        mode = rand()%100;
        if(mode<=40){
            dx = p->x - f->x;
            dy = p->y - f->y;
            if(abs(dx) > abs(dy)){
                px+= dx/abs(dx);
            }else{
                py+= dy/abs(dy);
            }
        }else{
            movef = rand()%4;
            printf("%d %d\n",movef,rand());
            //0 subir, 1 direita, 2 descer, 3 esquerda
            switch(movef)
            {
                case 0:
                    py--;
                    break;
                case 1:
                    px++;
                    break;
                case 2:
                    py++;
                    break;
                case 3:
                    px--;
                    break;
            }
        }


        //verifica se o fantasma estra dentro do mapa
        if(px<COLUNAS && py<LINHAS && px>=0 && py>=0)
        {
            f->x=px;
            f->y=py;
            break;
        }
        else{
            if(px<0)
            {
                f->x = COLUNAS-1;
            }
            if(py<0)
            {
                f->y = LINHAS-1;
            }
            if(px>=COLUNAS)
            {
                f->x = 0;
            }
            if(py>=LINHAS)
            {
                f->y = 0;
            }
        }
        break;
    }

}

void printaMatriz(char matriz[LINHAS][COLUNAS], PACMAN pac, FANT fant)
{
    int x,y;
    char printa;
    int desc;

    cls( GetStdHandle( STD_OUTPUT_HANDLE ));
    //Sleep(SPEED);
    for(y=0; y<LINHAS; y++)
    {
        for(x=0; x<COLUNAS; x++)
        {
            printa = matriz[y][x];
            if(pac.x==x && pac.y==y)
            {
                printa = CHAR_PACMAN;
            }
            if(fant.x == x && fant.y==y)
                printa = CHAR_FANT;
            //mesma coisa do if para o fantasma *********
            printf("%c",printa);
        }
        printf("\n");
    }

}

int main()
{
    char matriz[LINHAS][COLUNAS];
    FANT fantasma;
    PACMAN pac;
    pac.x = 19;
    pac.y = 3;
    fantasma.x=21;
    fantasma.y=6;

    int mov;
    int i, desc;
    char tecla, linha[50];
    desc = 0;

    srand(time(NULL));
    carrega_mapa(matriz);



   while(1)
    {
        //moveFantasma(&fantasma, matriz);
        moveFantasmasegue(&fantasma,&pac,matriz);
        printaMatriz(matriz,pac,fantasma);
        scanf("%c%*c",&tecla);
        move(&pac,tecla,matriz);

    }

    return 0;
}
