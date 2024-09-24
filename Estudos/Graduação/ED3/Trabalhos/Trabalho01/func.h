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
   // char padding[1600 - (sizeof(char) + 4 * sizeof(int))];       // Preenche o restante da página de disco com lixo
} Cabecalho;

// Exemplo de estrutura Registro (ajuste conforme necessário)
typedef struct {
   int populacao;
   float tamanho;
   char uniMedida;
   int velocidade;
   char *nome;
   char *nEspecie;
   char *habitat;
   char *tipo;
   char *dieta;
   char *alimento;

   char removido;
   int encadeamento;

} Registro;

// -------- Funções Fornecidas -----------------
void binarioNaTela(char *nomeArquivoBinario);

void scan_quote_string(char *str);
//----------------------------------------------

void escreve_cabecalho(Cabecalho c, FILE* bin, char status);
Cabecalho leitura_cabecalho(Cabecalho c, FILE* bin);
//leitura do arquivo CSV
void lendo_csv(char *nomeCSV, FILE *bin,  Cabecalho cabecalho, Registro registro);
void Escrevebin(FILE *nomebin, Registro registro,  Cabecalho c);


// Função para recuperar todos os registros e mostrar na saída padrão (função 2)
void recuperar_todos_os_registros(char *nomeBin);
void buscar_registros_por_campo(char *nomeBin, int n) ;


#endif