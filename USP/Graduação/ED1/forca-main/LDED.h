#ifndef LDED_H_INCLUDED
#define LDED_H_INCLUDED

//arquivo .h

//informções que serao guardadas no registro
typedef struct {
    char dados[19];
    int status;
}tipo_dado;

struct elemento
{
    tipo_dado dt;
    struct elemento *ant;
    struct elemento *prox;
};

typedef struct elemento* Lista;
typedef struct elemento Elem;

//prototipos de funções

Lista* cria_lista();
void libera_lista(Lista* li);
int tamanho_lista(Lista* li);
int lista_cheia(Lista* li);

int insere_ordenado(Lista* li, char *tag, int status);
int insere_meio(Lista* li, char *tag, int status);

int remove_inicio(Lista* li);
int remove_meio(Lista* li, tipo_dado dt);
int remove_final(Lista* li);

int consulta_lista(Lista* li, int n);

void imprime_lista(Lista* li);

//forca
int cont_palavara(Lista *li, int valor);
void libera_letra(Lista *li, int v1, int v2);
void compara_palavra(Lista *li, char *vetor, int status);
#endif // LDED_H_INCLUDED
