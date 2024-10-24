#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "func.h"


#define PAGE_SIZE 1600
#define FILL_CHAR '$'


void inicializa_cabecalho(Cabecalho *c) {
    c->status = '0';
    c->topo = -1;
    c->proxRRN = 0;
    c->nroRegRem = 0;
    c->nroPagDisco = 0;
    c->qttCompacta = 0;

    // Preencher o restante da página de disco com o caractere '$'
    memset(c->padding, FILL_CHAR, sizeof(c->padding));
}

#include <stdio.h>
#include <string.h>

void le_csv(char *nome_arquivo, FILE *arquivo_binario, Cabecalho *cabecalho) {
    FILE *arquivo_csv = fopen(nome_arquivo, "r");
    if (arquivo_csv == NULL) {
        printf("Falha ao abrir o arquivo CSV.\n");
        return;
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
}

/*
void le_csv(char *nome_arquivo, FILE *arquivo_binario, Cabecalho *cabecalho) {
    FILE *arquivo_csv = fopen(nome_arquivo, "r");
    if (arquivo_csv == NULL) {
        printf("Falha ao abrir o arquivo CSV.\n");
        return;
    }

    Registro registro;
    while (fscanf(arquivo_csv, "%s, %s, %s, %d, %s, %d, %s, %d, %s, %s", registro.nome, registro.dieta, registro.habitat, &registro.populacao, registro.tipo, &registro.velocidade,registro.uniMedida,&registro.tamanho, registro.nEspecie, registro.alimento) == 2) {
        // Adiciona o registro ao arquivo binário
        printf("teste: %s, %s, %s, %d, %s, %d, %s, %d, %s, %s", registro.nome, registro.dieta, registro.habitat, registro.populacao, registro.tipo, registro.velocidade,registro.uniMedida,registro.tamanho, registro.nEspecie, registro.alimento);
        //adiciona_registro(arquivo_binario, &registro, cabecalho);
    }

    fclose(arquivo_csv);
}*/
/*
void adiciona_registro(FILE *arquivo, Registro *novo_registro, Cabecalho *cabecalho) {
    // Move o ponteiro para o final do arquivo
    fseek(arquivo, 0, SEEK_END);

    // Escreve o novo registro no arquivo
    fwrite(novo_registro, sizeof(Registro), 1, arquivo);

    // Atualiza o valor de proxRRN e nroPagDisco no cabeçalho
    cabecalho->proxRRN++;
    cabecalho->nroPagDisco = (ftell(arquivo) + PAGE_SIZE - 1) / PAGE_SIZE; // Calcula o número de páginas ocupadas

    // Volta ao início do arquivo para atualizar o cabeçalho
    fseek(arquivo, 0, SEEK_SET);
    fwrite(cabecalho, sizeof(Cabecalho), 1, arquivo);
}

void remove_registro(FILE *arquivo, int rrn, Cabecalho *cabecalho) {
    // Calcula a posição do registro a ser removido com base no RRN
    long pos = sizeof(Cabecalho) + rrn * sizeof(Registro);
    
    // Vai para a posição do registro
    fseek(arquivo, pos, SEEK_SET);

    // Marca o registro como removido (por exemplo, gravando -1 no campo id)
    Registro registro;
    fread(&registro, sizeof(Registro), 1, arquivo);
    registro.id = -1;

    // Volta para a posição do registro e reescreve-o
    fseek(arquivo, pos, SEEK_SET);
    fwrite(&registro, sizeof(Registro), 1, arquivo);

    // Atualiza o número de registros removidos no cabeçalho
    cabecalho->nroRegRem++;

    // Atualiza o cabeçalho no arquivo
    fseek(arquivo, 0, SEEK_SET);
    fwrite(cabecalho, sizeof(Cabecalho), 1, arquivo);
}


void compacta_arquivo(FILE *arquivo, Cabecalho *cabecalho) {
    // Crie um novo arquivo temporário para armazenar os registros válidos
    FILE *arquivo_temp = fopen("temp.bin", "wb");

    // Copia o cabeçalho para o arquivo temporário
    fwrite(cabecalho, sizeof(Cabecalho), 1, arquivo_temp);

    Registro registro;
    while (fread(&registro, sizeof(Registro), 1, arquivo) == 1) {
        if (registro.id != -1) { // Se o registro não foi removido
            fwrite(&registro, sizeof(Registro), 1, arquivo_temp);
        }
    }

    // Fecha ambos os arquivos e substitui o arquivo original pelo temporário
    fclose(arquivo);
    fclose(arquivo_temp);
    remove("arquivo.bin");
    rename("temp.bin", "arquivo.bin");

    // Atualiza o cabeçalho (incrementa a quantidade de compactações)
    cabecalho->qttCompacta++;
}*/