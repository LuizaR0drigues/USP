/*Caue Sordi Paulino N°Usp ********
Luiza Rodrigues Cardoso N°usp 14593332
Algoritmo escolhido: QuickSort
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
int partiociona(int *vet, int inicio, int fim)
{
    // Escolhendo o pivo que sera usado nas comparações
    int pivo = vet[inicio];
    int esquerda = inicio;
    int direita = fim;


    while(esquerda < direita)
    {

        //encontrando o maior elemnto comparando com o pivo, 1 metade
        while(esquerda <= direita && vet[esquerda] <= pivo  )
        {
            esquerda++;
        }

        //encontrando o menor elemento comparando com o pivo, seg metade
        while(direita >= esquerda && vet[direita] > pivo)
        {
            direita--;
        }
        if(esquerda < direita)
        {
            swap(&vet[esquerda],&vet[direita]);
        }
    }
    swap(&vet[inicio],&vet[direita]);
    return direita;
}

void QuickSort(int *vet, int inicio, int fim)
{
    if(inicio < fim)
    {
        int posInd = partiociona(vet, inicio, fim);
        //ordena do incio ao meio
        QuickSort(vet, inicio, posInd-1);

        //ordena do meio ao fim
        QuickSort(vet, posInd+1, fim);
    }
}

int main()
{
    int *aux;
    int LenData =0;
    FILE *arquivo;
    clock_t t; // variavel que armazena o tempo
    for (int i = 1; i <= 20; i++)
    {
        LenData =0;
        char nome_arquivo[10];
        sprintf(nome_arquivo, "%d.in", i); // Formata o nome do arquivo com o número
        arquivo = fopen(nome_arquivo, "r");
        if (arquivo == NULL)
        {
            printf("#1 Erro na abertura do arquivo %d!\n");
            continue;
        }

        // Lê o tamanho e  os dados do arquivo e imprime
        fscanf(arquivo,"%d", &LenData);
        aux = (int*)malloc(LenData*sizeof(int));
        for(int j=0; j<LenData; j++)
        {
            fscanf(arquivo, "%d ", &aux[j]);
        }
        // Fecha o arquivo após a leitura
        printf("Tamanho do vetor: %d\n", LenData);
        printf("Vetor direto do arquivo:\n");
        for (int i = 0; i < LenData; i++)
        {
            printf("%d ", aux[i]);
        }


        //int tam = sizeof(aux)/sizeof(aux[0]);
        t = clock();
        //chhamando o quicksort
        QuickSort(aux, 0,LenData-1);
        t = clock() - t;
        printf("\nSorted array: ");
        for (int i = 0; i < LenData; i++)
        {
            printf("%d ", aux[i]);
        }

        printf("Tempo: %lf\n", ((double)t)/((CLOCKS_PER_SEC/1000)));//conversaõ para double
        free(aux);


        int test =0;
        scanf("%d",&test);
        if(test ==0)
            continue;
        else
            break;


    }

    return 0;
}
