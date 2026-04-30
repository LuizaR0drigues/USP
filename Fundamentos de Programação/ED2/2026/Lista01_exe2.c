#include <stdlib.h>
#include <stdio.h>

//Merge -> ordena os subvetores e mesclas os vetores ja ordenados
void merge(int vetor[], int init, int meio, int final){
    //definindo os limites dos intervalos dxe observacao
    int firs_met = meio - init + 1; 
    int sec_met = final - meio; 
    int i, j, k;

    //criando vetores auxiliares
    int esquerda[firs_met], direita[sec_met];

    //fazendo copias do vetor para cada metade - vetor/2 por iteração
    //divide
    for(i = 0; i< firs_met; i++)
    {
        //subvetor da esquerda
        esquerda[i] = vetor[init+i];
    }

    for(j = 0; j< sec_met; j++)
    {
        //subvetor da direita
        direita[j] = vetor[meio + j + 1];
    }

    //ordenando o vetor principal de forma descrente
    //conquista
    i =0, j=0, k=init;
    while(i < firs_met && j < sec_met){
        //se o elem da esquerda for maior
        if(esquerda[i] <= direita[j]){ 
            vetor[k] = esquerda[i]; //fica à esquerda do vetor principal
            i++;
        }
        else{//se o elem da direita for maior
            vetor[k] = direita[j]; //fica à direita do vetor principal
            j++;
        }
        k++;
    }

    //copiando os restantes da direita e esquerda - se houver
    while( i < firs_met){
        vetor[k] = esquerda[i];
        i++;
        k++;
    }
    while( j < sec_met){
        vetor[k] = direita[j];
        j++;
        k++;
    }
}
//MergeSort
//dividivide recursivamente o vetor e os encaminha para ordenação e mesclagem(merge)
void mergeSort(int vetor[], int init, int tam)
{   
    //para cada chamada que cumpra a condição
    if( init < tam ){
        //identifica o indice medio do vetor 
        int meio = init+(tam-init)/2;

        //divide, recuriva, o vetor em duas partes  
        //esquerda(init, meio) 
        mergeSort(vetor, init, meio);
        // direita(meio+1, final)
        mergeSort(vetor, meio+1, tam);

        //aplica o merge 
        merge(vetor, init, meio, tam);
    }
    
}

int main(){
    int qtd, x;
    scanf("%d", &qtd);

    int S[qtd];
    for(int i=0; i< qtd; i++)
    {
        scanf("%d", &S[i]);
    }
    scanf("%d" &x);
    mergeSort(S, 0, qtd-1);
    for(int i=0; i< qtd; i++)
        {
            printf("%d ", S[i]);
    }
    return 0;
}