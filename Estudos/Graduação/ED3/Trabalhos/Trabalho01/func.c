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


void lendo_csv(char *nomeCSV, FILE *nomeBin, Cabecalho *cabecalho) {
    Registro registro;
    char nome[10], dieta[10], habitat[20], tipo[20], uniMedida[1], nespecie[30], alimento[30], nEspecie[50];
    int velocidade, populacao, tamanho;

    FILE *arquivo_csv = fopen(nomeCSV, "r");
    if (arquivo_csv == NULL) {
        printf("Falha ao abrir o arquivo CSV\n");
        return;
    }
    //lendo o nome das colunas
    fscanf(arquivo_csv, "%s,%s,%s,%d,%s,%d,%s,%d,%s,%s\n", nome, dieta, habitat, &populacao, tipo,&velocidade, uniMedida,  &tamanho, nEspecie, alimento);
    while (!feof(arquivo_csv)) {
        fscanf(arquivo_csv, "%99[^,],%29[^,],%99[^,],%d,%29[^,],%d,%[^,],%f,%99[^,],%99[^\n]", 
                   registro.nome, registro.dieta, registro.habitat, &registro.populacao, 
                   registro.tipo, &registro.velocidade, registro.uniMedida, 
                   &registro.tamanho, registro.nEspecie, registro.alimento);
            /*printf("Nome: %s, Dieta: %s, Habitat: %s, População: %d, Tipo: %s, Velocidade: %d, Unidade: %s, Tamanho: %f, Espécie: %s, Alimento: %s\n",
       registro.nome, registro.dieta, registro.habitat, registro.populacao,
       registro.tipo, registro.velocidade, registro.uniMedida,
       registro.tamanho, registro.nEspecie, registro.alimento);*/
       arquivobin(nomeBin, registro);

        }
      
    fclose(arquivo_csv);
}


void arquivobin(FILE *nomebin, Registro registro)
{
     // Escrevendo os dados no arquivo com a função fwrite
    fwrite(registro.nome, sizeof(char), 100, nomebin);
    fwrite(registro.dieta, sizeof(char), 30, nomebin);
    fwrite(registro.habitat, sizeof(char), 100, nomebin);
    fwrite(&registro.populacao, sizeof(int), 1, nomebin);
    fwrite(registro.tipo, sizeof(char), 100, nomebin);
    fwrite(&registro.velocidade, sizeof(int), 1, nomebin);
    fwrite(registro.uniMedida, sizeof(char), 1, nomebin);
    fwrite(&registro.tamanho, sizeof(int), 1, nomebin);
    fwrite(registro.nEspecie, sizeof(char), 100, nomebin);
    fwrite(registro.alimento, sizeof(char), 100, nomebin);
}