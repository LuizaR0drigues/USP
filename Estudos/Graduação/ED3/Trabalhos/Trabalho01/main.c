#include <stdio.h>
#include <stdlib.h>
#include "func.h"
#include "funcoes_fornecidas.h"
#include <string.h>

int main() {
    
    int comando, rrn, Idbusca;
    char nomeCSV[100], nomearqbin[100];
    Cabecalho *inicio;
    Registro *registro;

    // Leitura dos parâmetros de arquivos
    scanf("%d", &comando);
    scanf("%s", nomeCSV);
    scanf("%s", nomearqbin);

    printf("%d %s %s \n", comando, nomeCSV, nomearqbin);
    
    // Abre o arquivo binário para leitura e escrita 
    FILE *arquivo_binario = fopen(nomearqbin, "wb");
    if (arquivo_binario == NULL) {
        printf("Falha ao abrir o arquivo binário.\n");
        return 1;
    }
    else{
        printf("Lendo do arquivo binario concluida \n");
    }
    
    //inicializa_cabecalho(inicio);
    //fwrite(&inicio, sizeof(Cabecalho), 1, arquivo_binario);
    
    lendo_csv(nomeCSV, arquivo_binario, inicio);


    fclose(arquivo_binario);
    return 0;
}
