#include <stdio.h>
#include <stdlib.h>
#include "func.h"
#include <string.h>

int main() {
    
    int comando;
    char nomeCSV[100], nomearqbin[100];
    Registro registro;
    
    // Cabecalho
    Cabecalho cabecalho;
    cabecalho.status = '0';
    cabecalho.topo = -1;
    cabecalho.proxRRN = 0;
    cabecalho.nroRegRem = 0;
    cabecalho.nroPagDisco = 0;
    cabecalho.qttCompacta = 0;

    // Leitura dos parâmetros de arquivos
    scanf("%d", &comando);

    switch (comando) {
        case 1: //CREATE TABLE
            scanf("%s", nomeCSV);
            scanf("%s", nomearqbin);

            // Abre o arquivo binário para leitura e escrita 
            FILE *arquivo_binario = fopen(nomearqbin, "wb");
            if (arquivo_binario == NULL) {
                printf("Falha ao abrir o arquivo binário.\n");
                return 1;
            }

            // Inicializa o cabeçalho
            escreve_cabecalho(cabecalho, arquivo_binario, '0');

            // Leitura do arquivo CSV e escrita dos registros
            lendo_csv(nomeCSV, arquivo_binario, cabecalho, registro);

            // Fecha o arquivo após a escrita dos registros
            fclose(arquivo_binario);

            // Abre o arquivo binário novamente para atualizar o cabeçalho
            arquivo_binario = fopen(nomearqbin, "r+b");
            if (arquivo_binario == NULL) {
                printf("Falha ao abrir o arquivo binário para atualização.\n");
                return 1;
            }

            // Atualiza o status do cabeçalho para '1'
            cabecalho.status = '1';
            fseek(arquivo_binario, 0, SEEK_SET); // Move o ponteiro para o início do arquivo
            fwrite(&cabecalho.status, sizeof(char), 1, arquivo_binario);

            fclose(arquivo_binario);

            // Exibe o conteúdo do arquivo binário na tela
            binarioNaTela(nomearqbin);

            break;
        case 2: // SELECT TABLE
            // Leitura do arquivo binário
            scanf("%s", nomearqbin);
            // Chama a função para recuperar e mostrar os registros
            recuperar_todos_os_registros(nomearqbin);
            break;
        default:
            break;
    }
    
    return 0;
}

