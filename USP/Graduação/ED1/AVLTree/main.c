#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArvoreBinaria.h"
#include "ArvoreAVL.h"



int main()
{
    ArvBin* raizBin = cria_ArvBin();
    ArvAVL* raizAVl= cria_ArvAVL();

    char vet[15], par[15], c[15];
    int coman;
    FILE *arquivo = fopen("arq.txt", "r");
    if(!arquivo)
        printf("Erro na abertura");

    while(1)
    {
        fgets(vet, 15, arquivo);
        vet[strcspn(vet, "\r\n")] = '\0';

        if (strcmp(vet,"x")==0) break;

        fgets(c, 15, arquivo);



        insere_ArvBin(raizBin, vet, c[0]);
        insere_ArvAVL(raizAVl, vet, c[0]);
        //printf("%s %c\n", vet,c);
    }

    int totBin = totalNO_ArvBin(raizBin);
    int totAVl = totalNO_ArvAVL(raizAVl);
    int achouAvl, achouBin;
    int aux1=-1, aux2=-1;

    scanf("%d", &coman);
    switch(coman)
    {
    case 0:
    {
        printf("NA:%d NB:%d \n", totBin, totAVl);
        break;
    }
    case 1:
    {
        scanf("%s", par);
        achouAvl = consulta_ArvAVL(raizAVl, par, &aux1);
        achouBin = consulta_ArvBin(raizBin, par, &aux2);
        //printf("Auxs: %d %d\n", aux1,aux2);
        if(aux1 ==0 && aux2 ==0)
            printf("S:%d NA:%d NB:%d",0, achouBin, achouAvl);
        else
            printf("S:%d NA:%d NB%d",-1, achouBin, achouAvl);
        break;
    }
    case 2:
    {
        Exibe_PreOrdem_ArvBin(raizBin);
        break;
    }
    case 3:

        preOrdem_ArvAVL(raizAVl);
        break;
    }
    libera_ArvBin(raizBin);
    libera_ArvAVL(raizAVl);
    return 0;
}
