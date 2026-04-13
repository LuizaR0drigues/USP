/**********************************************************************************
Luiza Rodrigues Cardoso - 14593332
Trabalho 03 - Orden // Estrutura de Dados 2
Ordenação de objetos
*********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// def Brinquedo e seus atributos
typedef struct
{
    /* data */
    double id;
    char cor[20];
    float comprimento;
    float nota;

} Brinquedo;

void merge(Brinquedo vetor[], int inicio, int meio, int final)
{
    // definindo os limites dos intervalos dxe observacao
    int firs_met = meio - inicio + 1;
    int sec_met = final - meio;
    int i, j, k;

    // criando vetores auxiliares
    Brinquedo *esquerda = (Brinquedo *)malloc(firs_met*sizeof(Brinquedo));
    Brinquedo *direita = (Brinquedo *)malloc(sec_met*sizeof(Brinquedo));

    // fazendo copias do vetor para cada metade - vetor/2 por iteração
    // divide
    for (i = 0; i < firs_met; i++)
    {
        // subvetor da esquerda
        esquerda[i] = vetor[inicio + i];
    }

    for (j = 0; j < sec_met; j++)
    {
        // subvetor da direita
        direita[j] = vetor[meio + j + 1];
    }

    i = 0, j = 0, k = inicio;
    // ordenação das partes
    while (i < firs_met && j < sec_met)
    {
        int flag = 0;
        int criterioCor = strcmp(esquerda[i].cor, direita[j].cor);
        if (criterioCor < 0)
        {
            flag = 1; // cor da esquerda é vem primeiro
        }
        else if (criterioCor == 0) // empate de cor
        {
            if (esquerda[i].comprimento < direita[j].comprimento)
            {
                flag = 1; // msm cor, porem comprimento menor
            }
            else if (esquerda[i].comprimento == direita[j].comprimento)
            { // ordena por nota
                if (esquerda[i].nota >= direita[j].nota)
                {
                    flag = 1; // só muda a nota que é maior
                }
            }
        }
        if (flag)
        {
            vetor[k] = esquerda[i];
            i++;
        }
        else
        {
            vetor[k] = direita[j];
            j++;
        }
        k++;
    }

    // Copia elems que sobraram
    while (i < firs_met)
    {
        vetor[k] = esquerda[i];
        i++;
        k++;
    }
    while (j < sec_met)
    {
        vetor[k] = direita[j];
        j++;
        k++;
    }
    free(esquerda);
    free(direita);
}

void mergesort(Brinquedo vetor[], int inicio, int final)
{ // para cada chamada que cumpra a condição
    if (inicio < final)
    {
        // identifica o indice medio do vetor
        int meio = (inicio) + (final - inicio) / 2;

        // divide, recuriva, o vetor em duas partes
        // esquerda(init, meio)
        mergesort(vetor, inicio, meio);
        // direita(meio+1, final)
        mergesort(vetor, meio + 1, final);

        // aplica o merge
        merge(vetor, inicio, meio, final);
    }
}

int main()
{
    char c;
    double qtd_brinq;
    scanf("%lf", &qtd_brinq);

    if (qtd_brinq > 0 && qtd_brinq <= 1e6)
    {
        // criando um vetor de struct
        Brinquedo *brinquedos, *temp;
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
        mergesort(brinquedos, 0, qtd_brinq - 1);

        for (int i = 0; i < qtd_brinq; i++)
        {
            printf("%1.lf;", brinquedos[i].id);
            // printf("%d %s %.2f %.2f\n", brinquedos[i].id, brinquedos[i].cor, brinquedos[i].comprimento, brinquedos[i].nota);
        }
        free(brinquedos);
    }
    else
    {
        return 0;
    }
    return 0;
}