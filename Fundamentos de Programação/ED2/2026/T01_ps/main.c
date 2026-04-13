/**********************************************************************************
Luiza Rodrigues Cardoso - 14593332
Trabalho 01 - Processo Seletivo // Estrutura de Dados 2
Alg Utilizado -> MergeSort cuja complexidade é O(n log n) 
*********************************************************************************/
 #include <stdio.h>
#include <stdlib.h>

//Merge -> ordena os subvetores e mesclas os vetores ja ordenados
void merge(double vetor[], int init, int meio, int final){
    //definindo os limites dos intervalos dxe observacao
    int firs_met = meio - init + 1; 
    int sec_met = final - meio; 
    int i, j, k;

    //criando vetores auxiliares
    double esquerda[firs_met], direita[sec_met];

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
void merge_sort(double vetor[], int init, int tam)
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
    //qtd de linhas/vagas
    int qtd_vagas = 0;
    //qtd pra segunda fase
    int qtd_second = 0;
    //qtd de candidatos
    int qtd_cand = 0;


    //leitura N vagas
    scanf("%d", &qtd_vagas);
    
    
    for(int i = 0; i < qtd_vagas; i++)
    {
        //leitura de K e C
        scanf("%d %d", &qtd_second, &qtd_cand);
        //printf("K= %d C= %d\n", qtd_second, qtd_cand);

        //vetor notas[c]
        //aloca a memoria necessaria
        double *notas = (double*)malloc((qtd_cand) * sizeof(double));

        //leitura das c notas que serao avaliadas
        for(int j =0; j < qtd_cand; j++)
        {
            //leitura da c notas
            scanf(" %lf", &notas[j]);
        } 
        //retorna um vetor descrecentemente ordenado
        merge_sort(notas, 0, qtd_cand -1);

        //imprime o K-ésimo maior elemento
        printf("%.2lf\n", notas[qtd_second-1]);
        
        //libera a memoria
        free(notas);

    }
    return 0;
}

//rodar
// gcc main.c -o run
//./run < ./ct/1.in > 1_out_my && diff 1_out_my ./ct/1.out