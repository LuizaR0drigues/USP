#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LDED.h"
#include <time.h>


int main()
{
    Lista *li = cria_lista();
    int valor, tecla;
    valor =0;
    char palavra[18];
    char coman[2], vetor[18];
    int i=0;

    FILE *arquivo;
    arquivo = fopen("dicio.txt", "r");

    if(!arquivo)
    {
        printf("01: Erro na abertura do arquivo!");
        return ;
    }

    while(1)
    {

        fgets(palavra, 18, arquivo);
        i++;
        palavra[strcspn(palavra, "\r\n")] = '\0';

        if(strcmp(palavra, "fim") == 0)
            break;
        insere_ordenado(li, palavra, i);
    }
    //imprime_lista(li);
    //printf("%d\n", valor);

    printf("<<< Forca da Esquerda >>>>>>\n");

    printf("Digite um numero entre 1 e 179: \n");
    scanf("%d", &tecla);
    if( tecla>0 && tecla<180)
    {
        int y= consulta_lista(li, tecla);
    }
    else
    {
        printf("Valor incorreto!\nDigite novamente:\n");
        scanf("%d", &tecla);
    }
    printf("Aqui vai uma dica sobre a palavra: \n");
    int conta = cont_palavara(li, tecla);
    for(int x =1; x<=conta; x++)
    {
        printf("_ ");
    }
    printf("\n\n");
    printf("Dica: \n");
    libera_letra(li, tecla, conta);
    printf("\n");
    printf("\n<<<< Menu: >>>>>>\nDigite A, Se souber a palavra \nDigite B, para chegar letra a letra\nPara abandonar o jogo, digite X\n");
    scanf("%s", coman);
    if( strcmp(coman, "A") == 0)
    {
        printf("Digite a palavra: \n");
        scanf("%s%*c", vetor);
        compara_palavra(li, &vetor, tecla);
    }
     if( strcmp(coman, "X") == 0)
     {
         return 0;
    }



    return 0;
}
