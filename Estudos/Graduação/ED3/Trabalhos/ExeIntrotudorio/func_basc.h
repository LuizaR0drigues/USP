#ifndef __FUNC_BASC_H
#define __FUNC_BASC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct especie {
    int especieID;
    char* nome;
    char* nome_cientifico;
    int populacao;
    char* status;
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

Registro RegistrodeEspecies();
Registro RegistrodeIndividuo();
Registro ArquivodeRegistro(FILE* file);
void Arquivobin(FILE* file, Registro especie);
Registro BuscaIndividuo(char *nomearquivo, int value);
void PrintRegistros(Registro especie);
void atualizarInformacoes(const char *nomearquivo, int id, int numInfo);
void freememoria();
#endif 

