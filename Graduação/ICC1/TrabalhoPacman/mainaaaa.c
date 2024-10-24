#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define SPEED 300

#define LINHAS 23
#define COLUNAS 39
#define CHAR_PACMAN 'C'
#define CHAR_WALL '#'
#define CHAR_PELLET '.'
#define CHAR_EMPTY ' '
#define CHAR_GHOST 'O'

void cls(HANDLE hConsole)
{
    COORD coordScreen = {0, 0};
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;

    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return;
    }

    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    if (!FillConsoleOutputCharacter(hConsole, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten))
    {
        return;
    }

    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return;
    }

    if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten))
    {
        return;
    }

    SetConsoleCursorPosition(hConsole, coordScreen);
}

void carrega_mapa(char matriz[LINHAS][COLUNAS])
{
    FILE *arq;
    int i, j;
    char linha[COLUNAS + 1];

    arq = fopen("mapa.txt", "r");
    if (!arq)
    {
        printf("\nErro de entrada na abertura do arquivo!");
        exit(1);
    }

    for (i = 0; i < LINHAS; i++)
    {
        fgets(linha, COLUNAS + 2, arq);
        linha[strcspn(linha, "\n")] = 0;
        for (j = 0; j < COLUNAS; j++)
        {
            matriz[i][j] = linha[j];
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
} GHOST;

void move(PACMAN *p, char move, char tabuleiro[LINHAS][COLUNAS])
{
    int px = p->x;
    int py = p->y;

    switch (move)
    {
    case 'w':
        py--;
        break;
    case 's':
        py++;
        break;
    case 'a':
        px--;
        break;
    case 'd':
        px++;
        break;
    }

    if (px < COLUNAS && py < LINHAS && px >= 0 && py >= 0)
    {
        if (tabuleiro[py][px] != CHAR_WALL)
        {
            p->x = px;
            p->y = py;
        }
    }
    else
    {
        if (px < 0)
        {
            p->x = COLUNAS - 1;
        }
        if (py < 0)
        {
            p->y = LINHAS - 1;
        }
        if (px >= COLUNAS)
        {
            p->x = 0;
        }
        if (py >= LINHAS)
        {
            p->y = 0;
        }
    }
}

void moveGhost(GHOST *g, char tabuleiro[LINHAS][COLUNAS])
{
    int px = g->x;
    int py = g->y;

    int movef = rand() % 4;

    switch (movef)
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

    if (px < COLUNAS && py < LINHAS && px >= 0 && py >= 0)
    {
        if (tabuleiro[py][px] != CHAR_WALL)
        {
            g->x = px;
            g->y = py;
        }
    }
    else
    {
        if (px < 0)
        {
            g->x = COLUNAS - 1;
        }
        if (py < 0)
        {
            g->y = LINHAS - 1;
        }
        if (px >= COLUNAS)
        {
            g->x = 0;
        }
        if (py >= LINHAS)
        {
            g->y = 0;
        }
    }
}

void printMatrix(char matriz[LINHAS][COLUNAS], PACMAN pac, GHOST ghost)
{
    int x, y;
    char printa;

    cls(GetStdHandle(STD_OUTPUT_HANDLE));
    Sleep(SPEED);
    for (y = 0; y < LINHAS; y++)
    {
        for (x = 0; x < COLUNAS; x++)
        {
            printa = matriz[y][x];

            if (pac.x == x && pac.y == y)
            {
                printa = CHAR_PACMAN;
            }

            if (ghost.x == x && ghost.y == y)
            {
                printa = CHAR_GHOST;
            }

            printf("%c", printa);
        }
        printf("\n");
    }
}

int main()
{
    char matriz[LINHAS][COLUNAS];
    GHOST ghost;
    PACMAN pacman;
    pacman.x = 21;
    pacman.y = 7;
    ghost.x = 17;
    ghost.y = 9;

    int i, desc;
    char tecla;

    srand(time(NULL));
    carrega_mapa(matriz);

    while (1)
    {
        moveGhost(&ghost, matriz);
        printMatrix(matriz, pacman, ghost);

        if (pacman.x == ghost.x && pacman.y == ghost.y)
        {
            printf("Game Over\n");
            break;
        }

        if (_kbhit())
        {
            tecla = _getch();
            move(&pacman, tecla, matriz);
        }
        //sleep(SPEED);
    }

    return 0;
}
