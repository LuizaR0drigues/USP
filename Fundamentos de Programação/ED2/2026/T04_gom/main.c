/**********************************************************************************
Luiza Rodrigues Cardoso - 14593332
Trabalho 04 - Gomas // Estrutura de Dados 2
Ordenação de objetos
*********************************************************************************/

#include <stdio.h>
#include <stdlib.h>

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
        int flagJog = 1;
        for(int i=0; i< qtd; i++)
        {   
            for(int j = 0 ; j< qtd -1; j++){
                //printf("%d %d\n", vetor[j],vetor[j+1]);
               if(vetor[j] > vetor[j+1]){
                    //printf("(%d, %d) \n", vetor[j],vetor[j+1]);
                    //swap
                    aux = vetor[j];
                    vetor[j] =  vetor[j+1];
                    vetor[j+1] =  aux;
                    aux++;
                    //identificando os jogadores
                    if(flagJog == 1 ){
                        flagJog = 2;
                    }
                    else{
                        flagJog = 1;
                    }
                    
               }
            }
        }
        if( flagJog == 2)
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
