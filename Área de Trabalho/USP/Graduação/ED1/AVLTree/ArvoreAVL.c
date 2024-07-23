#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArvoreAVL.h" //inclui os Protótipos

struct NO
{
    char info[9];
    char status;
    int altura;
    struct NO *esq;
    struct NO *dir;
};

ArvAVL* cria_ArvAVL()
{
    ArvAVL* raiz = (ArvAVL*) malloc(sizeof(ArvAVL));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void libera_NO(struct NO* no)
{
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void libera_ArvAVL(ArvAVL* raiz)
{
    if(raiz == NULL)
        return;
    libera_NO(*raiz);//libera cada nó
    free(raiz);//libera a raiz
}

int altura_NO(struct NO* no)
{
    if(no == NULL)
        return -1;
    else
        return no->altura;
}

int fatorBalanceamento_NO(struct NO* no)
{
    return labs(altura_NO(no->esq) - altura_NO(no->dir));
}

int maior(int x, int y)
{
    if(x > y)
        return x;
    else
        return y;
}

int estaVazia_ArvAVL(ArvAVL *raiz)
{
    if(raiz == NULL)
        return 1;
    if(*raiz == NULL)
        return 1;
    return 0;
}

int totalNO_ArvAVL(ArvAVL *raiz)
{
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = totalNO_ArvAVL(&((*raiz)->esq));
    int alt_dir = totalNO_ArvAVL(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);
}

int altura_ArvAVL(ArvAVL *raiz)
{
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = altura_ArvAVL(&((*raiz)->esq));
    int alt_dir = altura_ArvAVL(&((*raiz)->dir));
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
}

void preOrdem_ArvAVL(ArvAVL *raiz)
{
    if(raiz == NULL)
        return;
    if(*raiz != NULL)
    {
        printf("%s %c\n",(*raiz)->info,(*raiz)->status);
        preOrdem_ArvAVL(&((*raiz)->esq));
        preOrdem_ArvAVL(&((*raiz)->dir));
    }
}

void emOrdem_ArvAVL(ArvAVL *raiz)
{
    if(raiz == NULL)
        return;
    if(*raiz != NULL)
    {
        emOrdem_ArvAVL(&((*raiz)->esq));
        //printf("%d\n",(*raiz)->info);
        printf("%s: H(%d) fb(%d)\n",(*raiz)->info,altura_NO(*raiz),fatorBalanceamento_NO(*raiz));
        emOrdem_ArvAVL(&((*raiz)->dir));
    }
}

void posOrdem_ArvAVL(ArvAVL *raiz)
{
    if(raiz == NULL)
        return;
    if(*raiz != NULL)
    {
        posOrdem_ArvAVL(&((*raiz)->esq));
        posOrdem_ArvAVL(&((*raiz)->dir));
        printf("%s\n",(*raiz)->info);
    }
}

int consulta_ArvAVL(ArvAVL *raiz, char *tag, int *n1)
{
    int cont=0;
    int i = 0;
    if(raiz == NULL)
        return 0;
    struct NO* atual = *raiz;
    while(atual != NULL)
    {
        if(strcmp(tag, atual->info) ==0)
        {
            cont++;
            *n1=*n1+1;
        }
        if(strcmp(tag, atual->info)>= 1)
            atual = atual->dir;
        else
            atual = atual->esq;

    i++;
    }
    //printf("Consulta: %s %c", atual->info, atual->status);
    return i;
}

//=================================
void RotacaoLL(ArvAVL *A) //LL
{
    printf("RotacaoLL\n");
    struct NO *B;
    B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->esq),(*A)->altura) + 1;
    *A = B;
}

void RotacaoRR(ArvAVL *A) //RR
{
    printf("RotacaoRR\n");
    struct NO *B;
    B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = (*A);
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->dir),(*A)->altura) + 1;
    (*A) = B;
}

void RotacaoLR(ArvAVL *A) //LR
{
    RotacaoRR(&(*A)->esq);
    RotacaoLL(A);
}

void RotacaoRL(ArvAVL *A) //RL
{
    RotacaoLL(&(*A)->dir);
    RotacaoRR(A);
}

int insere_ArvAVL(ArvAVL *raiz,char *tag, char status)
{
    int res;
    if(*raiz == NULL) //árvore vazia ou nó folha
    {
        struct NO *novo;
        novo = (struct NO*)malloc(sizeof(struct NO));
        if(novo == NULL)
            return 0;

        strcpy(novo->info, tag);
        novo->status = status;
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }


    struct NO *atual = *raiz;
    if(strcmp(tag, atual->info) <= 0)
    {
        if((res = insere_ArvAVL(&(atual->esq), tag, status)) == 1)
        {
            if(fatorBalanceamento_NO(atual) >= 2)
            {
                if(strcmp(tag, (*raiz)->esq->info) <= 0)
                {
                    RotacaoLL(raiz);
                }
                else
                {
                    RotacaoLR(raiz);
                }
            }
        }
    }

    else
    {
        if(strcmp(tag, atual->info)>=1)
        {
            if((res = insere_ArvAVL(&(atual->dir), tag, status)) == 1)
            {
                if(fatorBalanceamento_NO(atual) >= 2)
                {
                    if(strcmp((*raiz)->dir->info, tag) <=-1)
                    {
                        RotacaoRR(raiz);
                    }
                    else
                    {
                        RotacaoRL(raiz);
                    }
                }
            }
        }
        else
        {
            printf("Valor duplicado!!\n");
            return 0;
        }
    }

    atual->altura = maior(altura_NO(atual->esq),altura_NO(atual->dir)) + 1;
    return res;
}

struct NO* procuraMenor(struct NO* atual)
{
    struct NO *no1 = atual;
    struct NO *no2 = atual->esq;
    while(no2 != NULL)
    {
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

int remove_ArvAVL(ArvAVL *raiz, char *tag)
{
    if(*raiz == NULL) // valor não existe
    {
        printf("valor não existe!!\n");
        return 0;
    }

    int res;
    if(strcmp(tag, (*raiz)->info)<=-1)
    {
        if((res = remove_ArvAVL(&(*raiz)->esq,tag)) == 1)
        {
            if(fatorBalanceamento_NO(*raiz) >= 2)
            {
                if(altura_NO((*raiz)->dir->esq) <= altura_NO((*raiz)->dir->dir))
                    RotacaoRR(raiz);
                else
                    RotacaoRL(raiz);
            }
        }
    }

    if(strcmp((*raiz)->info,tag)<=-1)
    {
        if((res = remove_ArvAVL(&(*raiz)->dir, tag)) == 1)
        {
            if(fatorBalanceamento_NO(*raiz) >= 2)
            {
                if(altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq) )
                    RotacaoLL(raiz);
                else
                    RotacaoLR(raiz);
            }
        }
    }

    if(strcmp((*raiz)->info, tag)==0)
    {
        if(((*raiz)->esq == NULL || (*raiz)->dir == NULL)) // nó tem 1 filho ou nenhum
        {
            struct NO *oldNode = (*raiz);
            if((*raiz)->esq != NULL)
                *raiz = (*raiz)->esq;
            else
                *raiz = (*raiz)->dir;
            free(oldNode);
        }
        else    // nó tem 2 filhos
        {
            struct NO* temp = procuraMenor((*raiz)->dir);
            strcpy((*raiz)->info, temp->info); //pode dar b.o
            remove_ArvAVL(&(*raiz)->dir, (*raiz)->info);
            if(fatorBalanceamento_NO(*raiz) >= 2)
            {
                if(altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq))
                    RotacaoLL(raiz);
                else
                    RotacaoLR(raiz);
            }
        }
        if (*raiz != NULL)
            (*raiz)->altura = maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir)) + 1;
        return 1;
    }

    (*raiz)->altura = maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir)) + 1;

    return res;
}
