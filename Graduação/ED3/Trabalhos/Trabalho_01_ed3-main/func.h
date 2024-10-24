#ifndef FUNC_H
#define FUNC_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PAGE_SIZE 1600
#define FILL_CHAR '$'

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
   int tamanho;
   char uniMedida;
   int velocidade;
   char nome[100];
   char nEspecie[100];
   char habitat[50];
   char tipo[30];
   char dieta[30];
   char alimento[30];

   char removido;
   int encadeamento;

} Registro;

// Função para inicializar o cabeçalho
void inicializa_cabecalho(Cabecalho *c);

// Função para ler um arquivo CSV e adicionar registros ao arquivo binário
void le_csv(char *nome_arquivo, FILE *arquivo_binario, Cabecalho *cabecalho);
/*
// Função para adicionar um registro ao arquivo binário
void adiciona_registro(FILE *arquivo, Registro *novo_registro, Cabecalho *cabecalho);

// Função para remover um registro logicamente
void remove_registro(FILE *arquivo, int rrn, Cabecalho *cabecalho);

// Função para compactar o arquivo de dados, removendo permanentemente registros excluídos
void compacta_arquivo(FILE *arquivo, Cabecalho *cabecalho);*/

#endif