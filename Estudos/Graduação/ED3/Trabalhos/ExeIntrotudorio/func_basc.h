#ifndef __FUNC_BASC_H
#define __FUNC_BASC_H

#include <stdio.h>
#include <stdlib.h>

void readline(char *string);

/**
 * Use essa função para comparação no run.codes.
 * Lembre-se de ter fechado (fclose) o arquivo anteriormente.
 *
 * Ela vai abrir de novo para leitura e depois fechar
 * (você não vai perder pontos por isso se usar ela).
 */
void binarioNaTela(char *nomeArquivoBinario);

#endif // __FUNCOES_FORNECIDAS__
