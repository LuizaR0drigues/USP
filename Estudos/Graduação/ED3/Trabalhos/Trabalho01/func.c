#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "func.h"
#include <ctype.h>

#define PAGE_SIZE 1600
#define FILL_CHAR '$'

// ------------ Funções Fornecidas --------------------------------------


void binarioNaTela(char *nomeArquivoBinario) { /* Você não precisa entender o código dessa função. */

	/* Use essa função para comparação no run.codes. Lembre-se de ter fechado (fclose) o arquivo anteriormente.
	*  Ela vai abrir de novo para leitura e depois fechar (você não vai perder pontos por isso se usar ela). */

	unsigned long i, cs;
	unsigned char *mb;
	size_t fl;
	FILE *fs;
	if(nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
		fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela): não foi possível abrir o arquivo que me passou para leitura. Ele existe e você tá passando o nome certo? Você lembrou de fechar ele com fclose depois de usar?\n");
		return;
	}
	fseek(fs, 0, SEEK_END);
	fl = ftell(fs);
	fseek(fs, 0, SEEK_SET);
	mb = (unsigned char *) malloc(fl);
	fread(mb, 1, fl, fs);

	cs = 0;
	for(i = 0; i < fl; i++) {
		cs += (unsigned long) mb[i];
	}
	printf("%lf\n", (cs / (double) 100));
	free(mb);
	fclose(fs);
}

void scan_quote_string(char *str) {

	/*
	*	Use essa função para ler um campo string delimitado entre aspas (").
	*	Chame ela na hora que for ler tal campo. Por exemplo:
	*
	*	A entrada está da seguinte forma:
	*		nomeDoCampo "MARIA DA SILVA"
	*
	*	Para ler isso para as strings já alocadas str1 e str2 do seu programa, você faz:
	*		scanf("%s", str1); // Vai salvar nomeDoCampo em str1
	*		scan_quote_string(str2); // Vai salvar MARIA DA SILVA em str2 (sem as aspas)
	*
	*/

	char R;

	while((R = getchar()) != EOF && isspace(R)); // ignorar espaços, \r, \n...

	if(R == 'N' || R == 'n') { // campo NULO
		getchar(); getchar(); getchar(); // ignorar o "ULO" de NULO.
		strcpy(str, ""); // copia string vazia
	} else if(R == '\"') {
		if(scanf("%[^\"]", str) != 1) { // ler até o fechamento das aspas
			strcpy(str, "");
		}
		getchar(); // ignorar aspas fechando
	} else if(R != EOF){ // vc tá tentando ler uma string que não tá entre aspas! Fazer leitura normal %s então, pois deve ser algum inteiro ou algo assim...
		str[0] = R;
		scanf("%s", &str[1]);
	} else { // EOF
		strcpy(str, "");
	}
}
// -----------------------------------------------------------------------------------------------------------------------------------------------------

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
    
    int tamT, tamD, tamA, tamE, tamH, tam;
    char linha[160]; // Tamanho máximo que o registro pode ocupar

    char nome[10], dieta[10], habitat[20], tipo[20], uniMedida[1], nespecie[30], alimento[30], nEspecie[50];
    int velocidade, populacao, tamanho;

    FILE *arquivo_csv = fopen(nomeCSV, "r");
    if (arquivo_csv == NULL) {
        printf("Falha ao abrir o arquivo CSV\n");
        return;
    }

    //lendo o nome das colunas
    char buffer[100];
    fgets(buffer, sizeof(buffer), arquivo_csv);
    printf("%s\n", buffer);
    char *campo;
    while (fgets(linha, sizeof(linha), arquivo_csv)) {
        printf("%s\n", linha);
        linha[strcspn(linha, "\n")] = '\0'; // Remove o caractere de nova linha
        
        campo = strtok(linha, ",");
        // Nome
        if (campo != NULL) {
            tam = strlen(campo);
            registro.nome = (char*) malloc((tam + 1) * sizeof(char));
            strcpy(registro.nome, campo);
            registro.nome[tam] = '#'; // Finaliza com '#'
        }
        // Dieta
        campo = strtok(NULL, ",");
        
        if (campo != NULL) {
             tamD = strlen(campo);
            registro.dieta = (char*) malloc((tamD + 1) * sizeof(char));
            strcpy(registro.dieta, campo);
            registro.dieta[tamD] = '#'; // Finaliza com '#'
        }

        // Habitat
        campo = strtok(NULL, ",");
        if (campo != NULL) {
             tamH = strlen(campo);
            registro.habitat = (char*) malloc((tamH + 1) * sizeof(char));
            strcpy(registro.habitat, campo);
            registro.habitat[tamH] = '#'; // Finaliza com '#'
        }

        // População
        campo = strtok(NULL, ",");
        registro.populacao = (campo != NULL) ? atoi(campo) : -1;

        // Tipo
        campo = strtok(NULL, ",");
        if (campo != NULL) {
             tamT = strlen(campo);
            registro.tipo = (char*) malloc((tamT + 1) * sizeof(char));
            strcpy(registro.tipo, campo);
            registro.tipo[tamT] = '#'; // Finaliza com '#'
        }

        // Velocidade
        campo = strtok(NULL, ",");
        registro.velocidade = (campo != NULL) ? atoi(campo) : -1;

        // Unidade de medida
        campo = strtok(NULL, ",");
        registro.uniMedida = (campo != NULL) ? campo[0] : '$';

        // Tamanho
        campo = strtok(NULL, ",");
        registro.tamanho = (campo != NULL) ? atof(campo) : -1;

        // Espécie
        campo = strtok(NULL, ",");
        if (campo != NULL) {
            tamE = strlen(campo);
            registro.nEspecie = (char*) malloc((tamE + 1) * sizeof(char));
            strcpy(registro.nEspecie, campo);
            registro.nEspecie[tamE] = '#'; // Finaliza com '#'
        }

        // Alimento
        campo = strtok(NULL, ",");
        if (campo != NULL) {
             tamA = strlen(campo);
            registro.alimento = (char*) malloc((tamA + 1) * sizeof(char));
            strcpy(registro.alimento, campo);
            registro.alimento[tamA] = '#'; // Finaliza com '#'
        }
        int soma = 160 - (tamA + tamT + tamD + tamE + tamH + tam + 18);
        // Armazena o registro no arquivo binário
        cabecalho->status = '1';
        arquivobin(nomeBin, registro, soma, cabecalho);

        // Libera a memória alocada
        free(registro.nome);
        free(registro.dieta);
        free(registro.habitat);
        free(registro.tipo);
        free(registro.nEspecie);
        free(registro.alimento);
    }
    
    printf("%c\n", cabecalho->status);
    fclose(arquivo_csv);

}

void arquivobin(FILE *nomebin, Registro registro, int aux, Cabecalho *cabeçalho) {
    fwrite(&registro.populacao, sizeof(int), 1, nomebin);
    fwrite(&registro.tamanho, sizeof(float), 1, nomebin);
    fwrite(&registro.uniMedida, sizeof(char), 1, nomebin);
    fwrite(&registro.velocidade, sizeof(int), 1, nomebin);

    // Escrevendo os dados das strings
    fwrite(registro.nome, sizeof(char), strlen(registro.nome) + 1, nomebin);
    fwrite(registro.dieta, sizeof(char), strlen(registro.dieta) + 1, nomebin);
    fwrite(registro.habitat, sizeof(char), strlen(registro.habitat) + 1, nomebin);
    fwrite(registro.tipo, sizeof(char), strlen(registro.tipo) + 1, nomebin);
    fwrite(registro.nEspecie, sizeof(char), strlen(registro.nEspecie) + 1, nomebin);
    fwrite(registro.alimento, sizeof(char), strlen(registro.alimento) + 1, nomebin);

    char vet[aux];
    memset(vet, '$', aux * sizeof(char));

    //
    fwrite(vet, sizeof(char), aux, nomebin);
    printf("Ok %c \n", cabeçalho->status);
    
}

// Função para recuperar todos os registros e mostrar na saída padrão (função 2)
void recuperar_todos_os_registros(char *nomeBin, Cabecalho *cabecalho) {
    printf("%s\n", nomeBin);
    FILE *arquivo_binario = fopen(nomeBin, "rb");
    if (arquivo_binario == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    fread(&cabecalho, sizeof(Cabecalho), 1, arquivo_binario);
    printf("Status: %c", cabecalho->status);
    // Verificar se o arquivo está consistente
    if (cabecalho->status == '0') {
        printf("Falha no processamento do arquivo.\n");
        fclose(arquivo_binario);
        return;
    }

    Registro registro;
    int registros_encontrados = 0;

    // Ler registros do arquivo binário
    while (fread(&registro, sizeof(Registro), 1, arquivo_binario) == 1) {
        if (registro.removido == '1') {
            continue; // Pular registros removidos
        }

        // Exibir os dados do registro
        printf("Nome: %s\n", registro.nome);
        printf("Dieta: %s\n", registro.dieta);
        printf("Habitat: %s\n", registro.habitat);
        if (registro.populacao != -1) {
            printf("População: %d\n", registro.populacao);
        }
        printf("Tipo: %s\n", registro.tipo);
        if (registro.velocidade != -1) {
            printf("Velocidade: %d %c/h\n", registro.velocidade, registro.uniMedida);
        }
        if (registro.tamanho != -1) {
            printf("Tamanho: %.2f\n", registro.tamanho);
        }
        printf("Espécie: %s\n", registro.nEspecie);
        printf("Alimento: %s\n", registro.alimento);
        printf("\n");

        registros_encontrados++;
    }

    // Verificar se nenhum registro foi encontrado
    if (registros_encontrados == 0) {
        printf("Registro inexistente.\n");
    }

    fclose(arquivo_binario);
}

