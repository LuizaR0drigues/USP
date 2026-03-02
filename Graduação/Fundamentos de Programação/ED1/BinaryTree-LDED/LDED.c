#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LDED.h"



Lista* cria_lista()
{
    Lista* li = (Lista*)malloc(sizeof(Lista));
    if(li !=NULL)
        *li = NULL;
    return li;
}

void libera_lista(Lista* li)
{

    if(li != NULL)
    {
        Elem* no;
        while((*li)!= NULL)
        {
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

int tamanho_lista(Lista* li)
{
    if(li == NULL)
        return 0;
    Elem *no = *li;
    int cont =0;
    while(no != NULL)
    {
        cont++;
        no = no->prox;

    }

    return cont;
}


int insere_inicio(Lista* li, char *tag, char status)
{
    if(li == NULL)
        return 0;
    Elem* no = (Elem*)malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    strcpy(no->dt.dados, tag);
    no->prox = (*li);//aponta para o conteudo da lista
    no->ant = NULL;//aponta para o inicio

    if((*li) != NULL)//se nao for vazia, o sue primeiro no ir� apontar para para o inserido
        (*li)->ant = no;
    *li =no;
    return 1;
}

int insere_final(Lista *li, char *tag, char status)
{
    if(li == NULL)
        return 0;
    Elem *no = (Elem*)malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    strcpy(no->dt.dados, tag);
    no->prox = NULL;
    if((*li) == NULL)//lista vazia
    {
        no->ant = NULL;
        *li = no;
    }
    else
    {
        Elem *aux = *li;
        while(aux->prox != NULL)
        {
            aux = aux->prox;//percorre a lista
        }
        aux->prox = no;//aponta para o novo ultimo
        no->ant = aux;//aponta para o velho ultimo
    }
    return 1;
}

int insere_ordenado(Lista* li, char *tag, char status)
{
    if(li == NULL)
        return 0;
    Elem* no = (Elem*)malloc(sizeof(Elem));
    if(no ==NULL)
        return 0;
     strcpy(no->dt.dados, tag);
     no->dt.status = status;
    if((*li)==NULL)//insere no inicio, lista vazia
    {
        no->prox =NULL;
        no->ant = NULL;
        *li = no;
        return 1;
    }
    else
    {
        Elem* anterior, *atual = *li;

        while(atual != NULL && (strcmp(atual->dt.dados , tag) <= -1))
        {
            anterior = atual;
            atual = atual->prox;
        }
        if(atual == *li)//insere no incio
        {
            no->ant = NULL;
            (*li)->ant = no;
            no->prox =(*li);
            *li = no;
        }
        else
        {
            no->prox = anterior->prox;
            no->ant = anterior;
            anterior->prox = no;
            if (atual != NULL)
                atual->ant = no;
        }
    }
    return 1;
}


int remove_inicio(Lista* li)
{
    if(li == NULL)
        return 0;

    if((*li) == NULL)//lista vaia
        return 0;

    Elem *no= *li;
    *li= no->prox;
    if(no->prox != NULL)
        no->prox->ant = NULL;

    free(no);
    return 1;
}

int remove_meio(Lista* li, tipo_dado dt)
{
    if(li == NULL)
        return 0;
    if((*li) == NULL)
        return 0;

    Elem *no = *li;
    while(no!= NULL )
    {
        no = no->prox;
    }

    if(no == NULL)//nao encontrado
        return 0;

    if(no->ant == NULL)//primeiro elemento
        *li = no->prox;

    else
        no->ant->prox = no->prox;

    if(no->prox != NULL)
        no->prox->ant = no->ant;//avan�a

    free(no);
    return 1;
}

int remove_final(Lista* li)
{
    if(li == NULL)
        return 0;
    if((*li)==NULL)
        return 0;

    Elem *no= *li;
    while(no->prox != NULL)//percorrre a lista ate chegar em null
        no = no->prox;

    if(no->ant == NULL)
        *li = no->prox;
    else
        no->ant->prox = NULL;

    free(no);
    return 1;
}

int consulta_lista(Lista *li, char *valor, int *n)
{
    if(li == NULL)
        return 0;
    if((*li) == NULL)
        return 0;

    Elem *no = *li;
    int i =-1;
    while(no !=  NULL && strcmp(no->dt.dados, valor) <= 0)
    {
        no = no->prox;
        i++;
        *n = *n+1;
    }
    if(no == NULL)
        return 0;
    else
    {
        strcpy(no->dt.dados, valor);
    }
    return i;
}

void imprime_lista(Lista* li)
{
    Elem* no = *li;

    if (li == NULL)
        return;
    while (no != NULL)
    {
        printf("%s %c\n",no->dt.dados, no->dt.status);
        no = no->prox;
    }
}
