#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinaria.h"
#include <string.h>

struct NO
{
    char info[9];
    char status;
    struct NO *esq;
    struct NO *dir;
};

ArvBin* cria_ArvBin()
{
    ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void libera_NO_Binaria(struct NO* no)
{
    if(no == NULL)
        return;
    libera_NO_Binaria(no->esq);
    libera_NO_Binaria(no->dir);
    free(no);
    no = NULL;
}

void libera_ArvBin(ArvBin* raiz)
{
    if(raiz == NULL)
        return;
    libera_NO_Binaria(*raiz);
    free(raiz);
}

int insere_ArvBin(ArvBin* raiz, char *tag, char status)
{
    if(raiz == NULL)
        return 0;

    struct NO* novo;
    novo = (struct NO*) malloc(sizeof(struct NO));

    if(novo == NULL)
        return 0;

    strcpy(novo->info,tag);

    novo->status = status;
    novo->dir = NULL;
    novo->esq = NULL;

    if(*raiz == NULL)
    {
        *raiz = novo;
    }
    else
    {
        struct NO* atual = *raiz;
        struct NO* ant = NULL;


        while(atual != NULL)
        {
            ant = atual;
            if(strcmp(tag, atual->info) == 0)
            {
                free(novo);
                return 0;
            }

            if(strcmp(tag, atual->info) >= 1)
                atual = atual->dir;
            else
                atual = atual->esq;
        }

        if(strcmp(tag, ant->info ) >= 1)
            ant->dir = novo;

        else
            ant->esq = novo;
    }

    return 1;
}


struct NO* remove_atual(struct NO* atual)
{
    struct NO *no1, *no2;
    if(atual->esq == NULL)
    {
        no2 = atual->dir;
        free(atual);
        return no2;
    }
    no1 = atual;
    no2 = atual->esq;
    while(no2->dir != NULL)
    {
        no1 = no2;
        no2 = no2->dir;
    }

    if(no1 != atual)
    {
        no1->dir = no2->esq;
        no2->esq = atual->esq;
    }
    no2->dir = atual->dir;
    free(atual);
    return no2;
}

int remove_ArvBin(ArvBin *raiz, char *valor)
{
    if(raiz == NULL)
        return 0;
    struct NO* ant = NULL;
    struct NO* atual = *raiz;
    while(atual != NULL)
    {
        if(strcmp(valor, atual->info) ==0 )
        {
            if(atual == *raiz)
                *raiz = remove_atual(atual);
            else
            {
                if(ant->dir == atual)
                    ant->dir = remove_atual(atual);
                else
                    ant->esq = remove_atual(atual);
            }
            return 1;
        }
        ant = atual;
        if(valor > atual->info)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}

int estaVazia_ArvBin(ArvBin *raiz)
{
    if(raiz == NULL)
        return 1;
    if(*raiz == NULL)
        return 1;
    return 0;
}

int totalNO_ArvBin(ArvBin *raiz)
{
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = totalNO_ArvBin(&((*raiz)->esq));
    int alt_dir = totalNO_ArvBin(&((*raiz)->dir));

    return(alt_esq + alt_dir + 1);
}

int altura_ArvBin(ArvBin *raiz)
{
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = altura_ArvBin(&((*raiz)->esq));
    int alt_dir = altura_ArvBin(&((*raiz)->dir));
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
}

int consulta_ArvBin(ArvBin *raiz, char *valor, int *n2)
{
    int i=0;
    int cont =0;
    if(raiz == NULL)
        return 0;
    struct NO* atual = *raiz;
    while(atual != NULL)
    {
        if(strcmp(valor,atual->info) ==0)
        {
          cont++;
          *n2 =*n2+1;
        }
        if(strcmp(valor , atual->info) >=1)
            atual = atual->dir;
        else
            atual = atual->esq;
    i++;
    }
    return i;
}

void preOrdem_ArvBin(ArvBin *raiz)
{
    if(raiz == NULL)
        return;
    if(*raiz != NULL)
    {
        printf("%s \n",(*raiz)->info);
        preOrdem_ArvBin(&((*raiz)->esq));
        preOrdem_ArvBin(&((*raiz)->dir));
    }
}

void emOrdem_ArvBin(ArvBin *raiz)
{
    if(raiz == NULL)
        return;
    if(*raiz != NULL)
    {
        emOrdem_ArvBin(&((*raiz)->esq));
        printf("%s \n",(*raiz)->info);
        emOrdem_ArvBin(&((*raiz)->dir));
    }
}

void posOrdem_ArvBin(ArvBin *raiz)
{
    if(raiz == NULL)
        return;
    if(*raiz != NULL)
    {
        posOrdem_ArvBin(&((*raiz)->esq));
        posOrdem_ArvBin(&((*raiz)->dir));
        printf("%s \n",(*raiz)->info);
    }
}

// Funcoes Adicionais de Arvore
/*
void Procura_preOrdem_ArvBin(ArvBin *raiz, char *str2, int *achou)
{
    if(raiz == NULL)
        return;
    if (*achou)
        return;
    if(*raiz != NULL)
    {
        if (strcmp(str2, (*raiz)->info) ==0)
        {
            printf("Achou: %s! \n",(*raiz)->info);
            *achou=1;
        }
        Procura_preOrdem_ArvBin(&((*raiz)->esq),str2,achou);
        Procura_preOrdem_ArvBin(&((*raiz)->dir),str2,achou);
    }
}*/

void Exibe_PreOrdem_ArvBin(ArvBin *raiz)
{
    if(raiz == NULL)
        return;


    if(*raiz != NULL)
    {
        printf("%s %c\n",(*raiz)->info, (*raiz)->status);
        Exibe_PreOrdem_ArvBin(&((*raiz)->esq));
        Exibe_PreOrdem_ArvBin(&((*raiz)->dir));

    }
    else
    {
        return;
    }


}


