/**********************************************************************************
Luiza Rodrigues Cardoso - 14593332
Trabalho 04 - Gomas // Estrutura de Dados 2
Ordenação de objetos
*********************************************************************************/

#include <stdio.h>
#include <stdlib.h>

long long flagJog = 0;
//Merge -> ordena os subvetores e mesclas os vetores ja ordenados
void merge(int vetor[], int init, int meio, int final){
    int tam = final - init + 1;
    int i = init, j = meio+1, k = 0;
    
    //criando vetores auxiliares
    int *temp = (int *)malloc(tam *sizeof(int));

    //ordenando o vetor principal de forma descrente
    //conquista
    while(i <= meio && j <= final){
        //se o elem da esquerda for maior
        if(vetor[i] <= vetor[j]){ 
            temp[k] = vetor[i]; 
            i++;
            
        }
        else{//se o elem da direita for maior
            temp[k] = vetor[j]; 
            j++;
            
            flagJog += meio-i+1;
        }
       k++;
    }

    //copiando os restantes da direita e esquerda - se houver
    while( i <= meio){
        temp[k] = vetor[i];
        i++;
        k++;
    }
    while( j <= final){
        temp[k] = vetor[j];
        j++;
        k++;
    }
    for(int i =0; i<tam; i++)
    {
        vetor[init+i] = temp[i];
    }
    free(temp);
}
//MergeSort
//dividivide recursivamente o vetor e os encaminha para ordenação e mesclagem(merge)
void merge_sort(int vetor[], int init, int tam)
{   
    //para cada chamada que cumpra a condição
    if( init < tam ){
        //identifica o indice medio do vetor 
        int meio = init+(tam-init)/2;

        //divide, recuriva, o vetor em duas partes  
        merge_sort(vetor, init, meio);
        merge_sort(vetor, meio+1, tam);

        //aplica o merge 
        merge(vetor, init, meio, tam);
    }
    
}

int main()
{
    int qtd, i = 0, *vetor,  aux;

    while (scanf("%d", &qtd) == 1 && qtd != 0)
    {   
        // alocando memoria
        vetor = (int *)malloc(qtd * sizeof(int));

        for (int i = 0; i < qtd; i++)
        {
            scanf("%d", &vetor[i]);
        }
         flagJog = 0;
        merge_sort(vetor, 0, qtd-1);
        if( flagJog % 2 != 0)
            printf("Jaques\n");
        else{
            printf("Fino\n");
        }
        /*for (int j = 0; j < qtd; j++)
        {
            printf("%d ", vetor[j]);
        }*/
        
        free(vetor);
       
    }

    return 0;
}
