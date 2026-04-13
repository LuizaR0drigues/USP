/**********************************************************************************
Luiza Rodrigues Cardoso - 14593332
Trabalho 03 - Orden // Estrutura de Dados 2
Ordenação de objetos
*********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// def Brinquedo e seus atributos
typedef struct
{
    /* data */
    int id;
    char cor[20];
    float comprimento;
    float nota;

} Brinquedo;

void swap(Brinquedo vetor[], int a, int b)
{
    Brinquedo aux;

    aux = vetor[a];
    vetor[a] = vetor[b];
    vetor[b] = aux;
}

// ordenada por cor
// apos, ordena por comprimento
// se houver empate, ordena por nota

int particiona(Brinquedo vet[], int pIni, int pFin)
{
    Brinquedo pivo;
    pivo = vet[pIni];

    int i = pIni + 1;
    int j = pFin;
    int aux = 0;
    while (i <= j)
    {
        // ordena por cor
        while (i <= pFin)//procura pelo maior
        {
            int criterioCor = strcmp(vet[i].cor, pivo.cor);
            if (criterioCor < 0)
            {
                i++; // ordem alfabetica
            }
            else if (criterioCor == 0) // empate de cor
            {
                if (vet[i].comprimento < pivo.comprimento)
                {
                    i++;
                }
                else if (vet[i].comprimento == pivo.comprimento)
                { // ordena por nota
                    if (vet[i].nota > pivo.nota)
                    {
                        i++;
                    }
                    else
                    {
                        break; // maior que o pivo em tudo
                    }
                }
                else
                {
                    break; // comprimento > pivo
                }
            }
            else
            {
                break; // vem depois alfabeticamente
            }
        }
        while (j >= i)//procura pelo menor
        {
            int criterioCor = strcmp(vet[j].cor, pivo.cor);
            if (criterioCor > 0)
            {
                j--; // cor vem depois - à direita
            }
            else if (criterioCor == 0) // empate de cor
            {
                if (vet[j].comprimento > pivo.comprimento)
                {
                    j--; //cor igual, comprimento diff
                }
                else if (vet[j].comprimento == pivo.comprimento)
                { // ordena por nota
                    if (vet[j].nota < pivo.nota)
                    {
                        j--;//cor e comprimento iguais, usa criterio de nota
                    }
                    else
                    {
                        break; // nota menor ou igual que o pivo
                    }
                }
                else
                {
                    break; // comprimento menor 
                }
            }
            else
            {
                break; // vem antes alfabeticamente
            }
        }
        if (i < j)
        {
            swap(vet, i, j);
        }
    }
    swap(vet, j, pIni);
    return j;
}

void quicksort(Brinquedo vetor[], int pIni, int pFin)
{
    if (pFin < +pIni)
    {
        return;
    }
    int meio = particiona(vetor, pIni, pFin);
    quicksort(vetor, pIni, meio - 1);
    quicksort(vetor, meio + 1, pFin);
}

int main()
{
    char c;
    int qtd_brinq;
    scanf("%d", &qtd_brinq);

    // criando um vetor de struct
    Brinquedo *brinquedos;
    brinquedos = (Brinquedo *)malloc(qtd_brinq * sizeof(Brinquedo));

    int i = 0;
    while (i < qtd_brinq)
    {
        // leitura dos dados e tranfere para a estrutura
        scanf("%s %f %f", brinquedos[i].cor, &brinquedos[i].comprimento, &brinquedos[i].nota);
        brinquedos[i].id = i;
        // leitura de char
        scanf("%c", &c);
        i++;
        // se for um caractere de final de instrução, termina o loop
        if (c == '\n' || c == '\r')
        {
            break;
        }
    }
    quicksort(brinquedos, 0, qtd_brinq - 1);

    for (int i = 0; i < qtd_brinq; i++)
    {
        printf("%d;", brinquedos[i].id);
        //printf("%d %s %.2f %.2f\n", brinquedos[i].id, brinquedos[i].cor, brinquedos[i].comprimento, brinquedos[i].nota);
    }
    return 0;
}