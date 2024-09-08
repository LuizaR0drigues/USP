#ifndef __FUNC_BASC_H
#define __FUNC_BASC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct especie {
    int especieID;
    char nome[41];
    char nome_cientifico[61];
    int populacao;
    char status[9];
    float localizacao[2]; //coordeanadas em x e y cada com 4 bytes
    int impacto_humano;

}Registro;

void readline(char *string);

/**
 * Use essa função para comparação no run.codes.
 * Lembre-se de ter fechado (fclose) o arquivo anteriormente.
 *
 * Ela vai abrir de novo para leitura e depois fechar
 * (você não vai perder pontos por isso se usar ela).
 */
void binarioNaTela(char *nomeArquivoBinario);

Registro RegistrodeEspecies(char *nomedoarquivo, int n);
Registro RegistrodeIndividuo();
Registro ArquivodeRegistro(char *nomearquivo, int qtd);
void Arquivobin(FILE* file, Registro especie);
void BuscaIndividuo(char *nomearquivo, int value);
void PrintRegistros(int qtd);
void atualizarInformacoes(const char *nomearquivo, int id, int numInfo);
#endif 

