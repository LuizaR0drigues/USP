#ifndef LDED_H_INCLUDED
#define LDED_H_INCLUDED

//arquivo .h

//informções que serao guardadas no registro
typedef struct {
    char dados[9];
    char status;
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

int insere_inicio(Lista* li, char *tag, char status);
int insere_final(Lista* li, char *tag, char status);
int insere_ordenado(Lista* li, char *tag, char status);
int insere_meio(Lista* li, char *tag, char status);

int remove_inicio(Lista* li);
int remove_meio(Lista* li, tipo_dado dt);
int remove_final(Lista* li);

int consulta_lista(Lista* li, char *valor, int *n);

void imprime_lista(Lista* li);
#endif // LDED_H_INCLUDED
