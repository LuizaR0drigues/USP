/**********************************************************************************
Luiza Rodrigues Cardoso - 14593332
Trabalho 2.1 - Black Friday // Estrutura de Dados 2
Estratégia adotada -> Guloso -> escolhe o minimo local
*********************************************************************************/
#include <stdio.h>
#include <stdlib.h>


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
        if(esquerda[i] >= direita[j]){ 
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
void merge_sort(int vetor[], int init, int tam)
{   
    //para cada chamada que cumpra a condição
    if( init < tam ){
        //identifica o indice medio do vetor 
        int meio = init+(tam-init)/2;

        //divide, recuriva, o vetor em duas partes  
        //esquerda(init, meio) 
        merge_sort(vetor, init, meio);
        // direita(meio+1, final)
        merge_sort(vetor, meio+1, tam);

        //aplica o merge 
        merge(vetor, init, meio, tam);
    }
    
}

int main(){
    //leitura da quantidade de produtos
    int n, cont=0;   
    scanf("%d", &n);

    //designando um vetor
    int *prod = (int*)malloc((n) * sizeof(int));


    for(int i=0; i<n; i++)
    {
        scanf("%d", &prod[i]);
    }

    merge_sort(prod, 0, n-1);
     /*for(int i=0; i<n-1; i++)
    {
        
        printf("%d ", prod[i]);
        
    }*/
    //printf("\n");
    for(int i=0; i<n-1; i++)
    {
        if( i !=0 && (i+1)%3 ==0)
        {
            cont += prod[i];
            //printf("%d %d\n", prod[i], i);
        }
    }
    printf("%d\n", cont);

    return 0;
    
}