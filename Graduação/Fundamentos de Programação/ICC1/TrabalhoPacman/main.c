#include <stdio.h>
#include <stdlib.h>
#include <string.h>      //  memcpy
#include <conio.h>       // _kbhit, _getch
#include <windows.h>
#include <time.h>    //  cls

#define SPEED 150
#define LINHAS 18
#define COLUNAS 29
#define CHAR_PACMAN 'P'
#define CHAR_FANT 'F'
#define azul 1
#define amarelo 2
#define verde 3
#define cinza 4
#define roxo 5
#define qtdIni 3
#define MAX_SCORES 5

typedef struct
{
    int x;
    int y;
    char carac;
    int status;
} PACMAN;

typedef struct
{
    int x;
    int y;
    int status;
} FANT;

typedef struct
{
    int pont;
    char nome[4];
    char **mapa;
}PLAYER;
PLAYER newPlayer;

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
void cor(int ncor)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    switch(ncor)
    {
    case azul:
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        break;
    case amarelo:
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
        break;
    case verde:
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        break;
    case cinza:
        SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);
        break;
    case roxo:
        SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE| FOREGROUND_RED );
        break;
    }
}
//função que carregara o mapa
void carrega_mapa(char **matriz)
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
    lin  =0;
    col=0;

    for(i=0; i<LINHAS; i++)
    {
        fgets(linha,COLUNAS+1,arq);
        linha[strcspn(linha, "\n")] = 0;
        for(j=0; j<COLUNAS; j++)
        {
            matriz[i][j]=linha[j];
            if(matriz[i][j] =='.')
            {
                if(rand()%50 == 0)
                {
                    matriz[i][j]='S';
                }
            }
            if(matriz[i][j] =='.')
            {
                if(rand()%50 == 0)
                {
                    matriz[i][j]='O';
                }
            }
        }
    }

    fclose(arq);
}
void rank(const char* filename)
{
    printf("\n%s\n", filename);
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file %s\n", filename);
        return;
    }

    PLAYER rank[MAX_SCORES];
    int numScores = 0;

    // Read existing rank from the file
    while (fscanf(file, "%d %s", &rank[numScores].pont, rank[numScores].nome) != EOF && numScores < MAX_SCORES)
    {
        numScores++;
    }
    fclose(file);

    // Add the new player to the rank
    rank[numScores] = newPlayer;
    numScores++;

    // Sort the rank
    for (int i = 0; i < numScores - 1; i++)
    {
        for (int j = 0; j < numScores - i - 1; j++)
        {
            if (rank[j].pont < rank[j + 1].pont)
            {
                PLAYER temp = rank[j];
                rank[j] = rank[j + 1];
                rank[j + 1] = temp;
            }
        }
    }

    // Update the top 5 players in the file
    file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening file %s\n", filename);
        return;
    }

    for (int i = 0; i < MAX_SCORES && i < numScores; i++)
    {
        fprintf(file, "%d %s\n", rank[i].pont, rank[i].nome);
    }
    fclose(file);
}


void move(PACMAN *p,char **tabuleiro)
{
    int px = p->x;
    int py = p->y;
    if (_kbhit())
    {
        //V� qual tecla est� sendo tocada
        char move = _getch();

        switch(move)
        {
        case 'w':
        case 72:
            (py)--;
            break;
        case 's':
        case 80:
            (py)++;
            break;
        case 'a':
        case 75:
            (px)--;
            break;
        case 'd':
        case 77:
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

            if(px<0)
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
    }
}

void moveFantasmasegue(FANT *f, PACMAN *p,char **tabuleiro)
{
    if(f->status>0)
    {
        return;
    }
    int px = f->x;
    int py = f->y;
    int movef;
    int dx,dy;
    int mode = 0;
    int c=1;
    while(c)
    {
        px = f->x;
        py =f->y;
        mode = rand()%100;
        if(mode<=95)
        {
            dx = p->x - f->x;
            dy = p->y - f->y;
            if(abs(dx) > abs(dy))
            {
                px+= dx/abs(dx);
            }
            else
            {
                py+= dy/abs(dy);
            }
        }
        else
        {
            movef = rand()%4;

            //0 subir, 1 direita, 2 descer, 3 esquerda
            switch(movef)
            {
            case 0:
                if(tabuleiro[py-1][px]!= '#')
                {
                    f->y--;
                    c=0;
                }
                break;
            case 1:
                if(tabuleiro[py][px+1]!= '#')
                {
                    f->x++;
                    c=0;
                }
                break;
            case 2:
                if(tabuleiro[py+1][px]!= '#')
                {
                    f->y++;
                    c=0;
                }
                break;
            case 3:
                if(tabuleiro[py][px-1]!= '#')
                {
                    f->x--;
                    c=0;
                }
                break;
            }

            //teleporta pro outro lado

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

    }


}

void printaMatriz(char **matriz, PACMAN pac, FANT *fant, int pont)
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
                printa = pac.carac;
                cor(amarelo);
                if(pac.status<=0)
                {
                    cor(amarelo);
                }
                else
                {
                    cor(azul);
                }
                printf("%c", printa);
            }
            else
            {
                for(int i=0; i<qtdIni; i++)
                {
                    if(fant[i].x == x && fant[i].y==y&& fant[i].status<=0)
                    {
                        printa = CHAR_FANT;
                        cor(verde);
                        break;
                    }
                    else
                    {
                        cor(cinza);
                    }

                }
                if(matriz[y][x] == 'O' || matriz[y][x] =='S')
                {
                    cor(roxo);
                }
                printf("%c",printa);
            }

        }
        printf("\n");
    }
    printf("\n%d", newPlayer.pont);

}

int pontstatus(char **tabuleiro, FANT *f, PACMAN *p,int *pont)
{

    for(int j=0; j<qtdIni; j++)
    {
        if(p->x== f[j].x && p->y == f[j].y)
        {
            if(p->status<=0)
            {
                p->carac ='M';
                return 1;

            }
            else
            {
                f[j].status = 2*10*1000/SPEED;
                break;
            }
        }
    }

    if(tabuleiro[p->y][p->x]== 'S')
    {
        //fica invencivel
        p->status = 2*10*1000/SPEED;
        tabuleiro[p->y][p->x]=' ';
    }

    if (tabuleiro[p->y][p->x] == '.')
    {
        newPlayer.pont += 5;
        tabuleiro[p->y][p->x] = ' ';
    }


    if(tabuleiro[p->y][p->x]== 'O')
    {
        newPlayer.pont+=10;
        tabuleiro[p->y][p->x]=' ';
    }

    if(p->status>0)
    {
        p->status--;
    }
    for(int i=0; i<qtdIni; i++)
    {
        if(f[i].status>0)
        {
            f[i].status--;
        }
    }

    return 0;
}
int verificaganhou(char **tabuleiro)
{
    for(int i = 0; i <LINHAS; i++)
    {
        for(int j = 0; j <COLUNAS; j++)
        {
            //o jogador inda não ganhou
            if(tabuleiro[i][j] == '.' || tabuleiro[i][j] == 'S' || tabuleiro[i][j] == 'O')
                return 0;
        }
    }
    return 1;
}


int main()
{
    srand(time(NULL));



    char **matriz;
    FANT *fantasma = malloc(qtdIni*sizeof(*fantasma));
    PACMAN pac;
    //PLAYER newPlayer;
    int pont;
    char pause[2];
    const char* filename = "rank.txt";
    char nome[4];

    pont = 0;
    pac.x = 19;
    pac.y = 3;
    pac.carac =CHAR_PACMAN;

    matriz = malloc(LINHAS*sizeof(*matriz));
    for(int i=0; i<LINHAS; i++)
    {
        matriz[i]= malloc((COLUNAS+1)*sizeof(**matriz));
    }

    carrega_mapa(matriz);

    for(int i=0; i<qtdIni; i++)
    {
        fantasma[i].x=(rand()%(COLUNAS-2))+1;
        fantasma[i].y=(rand()%(LINHAS-2))+1;
        fantasma[i].status=0;
        if(matriz[fantasma[i].y][fantasma[i].x]=='#')
        {
            i--;
        }
    }
    printf("digite seu nome: ");
    scanf("%s", newPlayer.nome);


    while(1)
    {

        for(int i=0; i<qtdIni; i++)
        {

            moveFantasmasegue(&fantasma[i],&pac,matriz);
        }
        if(pontstatus(matriz,fantasma,&pac,&pont))
        {
            printaMatriz(matriz,pac,fantasma,pont);
            break;

        }


        printaMatriz(matriz,pac,fantasma,pont);
        Sleep(SPEED);
        move(&pac,matriz);
        move(&pac,matriz);
        if(pontstatus(matriz,fantasma,&pac,&pont))
        {
            printaMatriz(matriz,pac,fantasma,pont);
            break;

        }
        if(verificaganhou(matriz))
        {
            printf("\nParabens!\n");
            printf("\nPontuacao: %d", pont);
            break;
        }


    }
    rank(filename);
    printf("\nGAME OVER, %s", &newPlayer.nome);
    scanf("%s", pause);




    return 0;
}
