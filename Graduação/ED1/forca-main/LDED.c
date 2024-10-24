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

int insere_ordenado(Lista* li, char *tag, int status)
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

        while(atual != NULL && no->dt.status<= status)
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

int consulta_lista(Lista *li,int valor)
{
    if(li == NULL)
        return 0;
    if((*li) == NULL)
        return 0;

    Elem *no = *li;
    int i =0;
    //printf("O valor passado foi: %d\n", valor);
    while(no !=  NULL && no->dt.status != valor)
    {
        no = no->prox;
        i++;

    }
    if(no == NULL)
        return 0;

    return 1;
}

void imprime_lista(Lista* li)
{
    Elem* no = *li;
    if (li == NULL)
        return;
    while (no != NULL && no->prox != NULL)
    {
        printf("%s \n",no->dt.dados);
        no = no->prox;
    }
}

int cont_palavara(Lista *li, int valor)
{
    Elem *no =*li;
    if(li == NULL)
        return 0;
    while(no!= NULL && no->dt.status!= valor)
    {
        no = no->prox;
    }
    int cont =strlen(no->dt.dados);
    printf("Esta palavra tem %d letras \n", cont);
    return cont;
}

void libera_letra(Lista *li, int valor, int cont)
{
    Elem *no =*li;
    if(li == NULL)
        return 0;
    while(no!= NULL && no->dt.status!= valor)
    {
        no = no->prox;
    }


    char vetor[20];
    strcpy(vetor, no->dt.dados);

    for(int i=0; i<strlen(vetor); i++)
    {


        if(i%2 == 0)
        {
            printf("%c ", vetor[i]);
        }
        else
        {
            printf("_ ");
        }
    }

}
void compara_palavra(Lista *li, char *vetor, int status)
{
    Elem* no = *li;
    if (li == NULL)
        return;
    while (no != NULL && no->dt.status != status)
    {
        no = no->prox;
    }
    if(strcmp(vetor,no->dt.dados ) ==0)
    {
        printf("<<<<<Parabens!!! Palavra correta>>>>>>\n");
    }
    else
    {
        printf("Palavras: %s \nDigitado: %s\n", no->dt.dados,  vetor);
        printf("Palavra incorreta!\n");
    }
}
