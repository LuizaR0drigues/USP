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
    int tam;
    clock_t t;

    scanf("%d%*c", &tam);
    aux = (int*)malloc(tam*sizeof(int));

    for(int i=0; i<tam; i++)
    {
        scanf("%d%*c",&aux[i]);
    }
    t = clock();
    QuickSort(aux, 0,tam-1);
    t = clock() -t;
    for (int i = 0; i < tam; i++)
    {
        printf("%d ", aux[i]);
    }
    printf("Tempos: %f", ((double)t)/((second )));

    return 0;
}
