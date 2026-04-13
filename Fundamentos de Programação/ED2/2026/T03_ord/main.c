/**********************************************************************************
Luiza Rodrigues Cardoso - 14593332
Trabalho 03 - Orden // Estrutura de Dados 2
Ordenação de objetos
*********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//def Brinquedo e seus atributos
typedef struct 
{
    /* data */
    int id;
    char cor[20];
    float comprimento;
    float nota;

} Brinquedo;



int main(){
    char c;
    int qtd_brinq;
    scanf("%d", &qtd_brinq);

    //criando um vetor de struct
    Brinquedo *brinquedos;
    brinquedos =  (Brinquedo *)malloc(qtd_brinq * sizeof(Brinquedo));

    int i=0;
    while( i < qtd_brinq)
    {   
        //leitura dos dados e tranfere para a estrutura
        scanf("%s %f %f", brinquedos[i].cor, &brinquedos[i].comprimento, &brinquedos[i].nota);
        brinquedos[i].id =  i;
        //leitura de char
        scanf("%c", &c);
        i++;
        //se for um caractere de final de instrução, termina o loop
        if (c == '\n' || c == '\r') 
        {
            break; 
        }
    }
    for(int i=0; i<qtd_brinq; i++)
    {
        printf("%d %s %.2f %.2f\n", brinquedos[i].id, brinquedos[i].cor, brinquedos[i].comprimento, brinquedos[i].nota);
    }
    return 0;
}