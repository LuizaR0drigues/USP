#include <stdio.h>
#include <stdlib.h>
#include "func.h"
#include "funcoes_fornecidas.h"
#include <string.h>

int main() {
    
    int comando, rrn, Idbusca;
    char nomearq[100], nomearqbin[100];

    // Leitura dos parâmetros
    scanf("%d", &comando);
    scanf("%s", nomearq);
    scanf("%s", nomearqbin);

    printf("%d %s %s \n", comando, nomearq, nomearqbin);

    // Abre o arquivo binário para leitura e escrita 
    FILE *arquivo_binario = fopen(nomearqbin, "wb");
    if (arquivo_binario == NULL) {
        printf("Falha ao abrir o arquivo binário.\n");
        return 1;
    }

    // Inicializa o cabeçalho e escreve no arquivo binário
    Cabecalho cabecalho;
    inicializa_cabecalho(&cabecalho);
    if (fwrite(&cabecalho, sizeof(Cabecalho), 1, arquivo_binario) != 1) {
        printf("Falha ao escrever o cabeçalho no arquivo binário.\n");
        fclose(arquivo_binario);
        return 1;
    }

    // Exemplo de leitura de arquivo CSV e inserção dos registros no arquivo binário
    //le_csv(nomearq, arquivo_binario, &cabecalho);

    FILE *arquivo_csv = fopen(nomearq, "r");
    if (arquivo_csv == NULL) {
        printf("Falha ao abrir o arquivo CSV.\n");
        return 0;
    }

    Registro registro;
    char linha[512];  // Buffer para ler cada linha do CSV

    while (fgets(linha, sizeof(linha), arquivo_csv) != NULL) {
        // Remove o caractere de nova linha, se presente
        linha[strcspn(linha, "\n")] = '\0';

        // Usa strtok para dividir a linha em campos
        char *campo = strtok(linha, ",");
        if (campo != NULL) strcpy(registro.nome, campo);

        campo = strtok(NULL, ",");
        if (campo != NULL) strcpy(registro.dieta, campo);

        campo = strtok(NULL, ",");
        if (campo != NULL) strcpy(registro.habitat, campo);

        campo = strtok(NULL, ",");
        if (campo != NULL) registro.populacao = atoi(campo);

        campo = strtok(NULL, ",");
        if (campo != NULL) strcpy(registro.tipo, campo);

        campo = strtok(NULL, ",");
        if (campo != NULL) registro.velocidade = atoi(campo);

        campo = strtok(NULL, ",");
        if (campo != NULL) registro.uniMedida = campo[0];

        campo = strtok(NULL, ",");
        if (campo != NULL) registro.tamanho = atoi(campo);

        campo = strtok(NULL, ",");
        if (campo != NULL) strcpy(registro.nEspecie, campo);

        campo = strtok(NULL, ",");
        if (campo != NULL) strcpy(registro.alimento, campo);

        // Exibe o registro lido (ou adicione ao arquivo binário)
        printf("Registro lido: %s, %s, %s, %d, %s, %d, %c, %d, %s, %s\n", 
               registro.nome, registro.dieta, registro.habitat, registro.populacao, 
               registro.tipo, registro.velocidade, registro.uniMedida, 
               registro.tamanho, registro.nEspecie, registro.alimento);

        // Exemplo de chamada para adicionar o registro ao arquivo binário
        // adiciona_registro(arquivo_binario, &registro, cabecalho);
    }

    fclose(arquivo_csv);

    /*// Exemplo de adição manual de um registro
    Registro novo_registro;
    novo_registro.id = 1; // Exemplo de ID
    snprintf(novo_registro.nome, sizeof(novo_registro.nome), "Exemplo de Nome");
    adiciona_registro(arquivo_binario, &novo_registro, &cabecalho);

    // Exemplo de remoção lógica de um registro pelo RRN
    int rrn_para_remover = 0; // RRN do registro que você quer remover
    remove_registro(arquivo_binario, rrn_para_remover, &cabecalho);

    // Compactação do arquivo para remover permanentemente os registros lógicos
    compacta_arquivo(arquivo_binario, &cabecalho);
    
    // Fecha o arquivo binário
    fclose(arquivo_binario);

    printf("Operações concluídas com sucesso!\n");*/
    return 0;
}
