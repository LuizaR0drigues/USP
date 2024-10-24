
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArvoreBinaria.h"
#include "LDED.h"



int main()
{
    ArvBin* raiz = cria_ArvBin();
    Lista* li = cria_lista();

    char vet[10], c,par[10];
    int coman;
    FILE *arquivo = fopen("arq.txt", "r");
    if(!arquivo)
        printf("Erro na abertura");

    //int i=0;
    while(1)
    {
        fscanf(arquivo, "%s%*c", vet);
        vet[strcspn(vet, "\r\n")] = '\0';

        if (strcmp(vet,"x")==0) break;

        fscanf(arquivo, "%c%*c",&c);
        //printf("%s %c\n", vet,c);


        insere_ArvBin(raiz, vet, c);
        insere_ordenado(li, vet, c);
    }

    int totBin = totalNO_ArvBin(raiz);
    int totLi = tamanho_lista(li);
    int achou, find2;
    int y=0;

    scanf("%d", &coman);
    switch(coman)
    {
    case 0:
    {
        printf("NL:%d NA:%d \n", totLi, totBin);
        break;
    }
    case 1:
    {
        scanf("%s", par);
        achou = consulta_lista(li, par, &y);
        find2 = consulta_ArvBin(raiz, par);
        printf("S:%d NL:%d NA:%d", achou, y, find2);
        break;
    }
    case 2:
    {
        imprime_lista(li);
        break;
    }
    case 3:
        Exibe_PreOrdem_ArvBin(raiz);
        break;
    }
    libera_ArvBin(raiz);
    libera_lista(li);
    return 0;
}
