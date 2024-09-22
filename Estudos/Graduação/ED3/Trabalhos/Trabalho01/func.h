#ifndef FUNC_H
#define FUNC_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PAGE_SIZE 1600
#define FILL_CHAR '$'
#define NULL_char '#'

// Estrutura que representa o registro de cabeçalho
typedef struct {
    char status;                // 1 byte
    int topo;               // 4 bytes
    int proxRRN;            // 4 bytes
    int nroRegRem;          // 4 bytes
    int nroPagDisco;        // 4 bytes
    int qttCompacta;        // 4 bytes
    char padding[1578];         // Preenche o restante da página de disco com lixo
} Cabecalho;

// Exemplo de estrutura Registro (ajuste conforme necessário)
typedef struct {
   int populacao;
   float tamanho;
   char uniMedida[1];
   int velocidade;
   char nome[100];
   char nEspecie[100];
   char habitat[100];
   char tipo[30];
   char dieta[30];
   char alimento[100];

   char removido;
   int encadeamento;

} Registro;

void inicializa_cabecalho(Cabecalho *c);

//leitura do arquivo CSV
void lendo_csv(char *nomeCSV, FILE *bin,  Cabecalho *cabecalho);
//void adiciona_registro(FILE *arquivo, Registro *novo_registro, Cabecalho *cabecalho);
void arquivobin(FILE *nomebin, Registro registro);
#endif