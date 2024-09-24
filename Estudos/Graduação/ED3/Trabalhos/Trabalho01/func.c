#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "func.h"
#include <ctype.h>
#include <stdbool.h>

#define PAGE_SIZE 1600 //tamanho de uma pagina do disco
#define FILL_CHAR '$'

// ------------ Funções Fornecidas ----------------------------------------------------------------------------------------------------------------------
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

void escreve_cabecalho(Cabecalho c, FILE* bin, char str) {

    if(str == '1')
    {   
        c.status = str;
        fwrite(&c.status, sizeof(char), 1, bin);
    }
    else{
        c.status = '0';
        fwrite(&c.status, sizeof(char), 1, bin);
        
    }

    fwrite(&c.topo, sizeof(int), 1, bin);
        fwrite(&c.proxRRN, sizeof(int), 1, bin);
        fwrite(&c.nroRegRem, sizeof(int), 1, bin);
        fwrite(&c.nroPagDisco, sizeof(int), 1, bin);
        // Preencher o restante da página de disco com o caractere '$'
        int resto = 1600- 4 * sizeof(int) - sizeof(int);
        char aux[resto];
        for(int i=0; i< resto; i++)
        {
            aux[i] = '$';
        }
        fwrite(aux, sizeof(char), resto, bin);//completa com $
    
    
    
}
Cabecalho leitura_cabecalho(Cabecalho c, FILE* bin) {
    
    fread(&c.status, sizeof(char), 1, bin);
    printf("Status3: %c\n", c.status);
    fread(&c.topo, sizeof(int), 1, bin);
    fread(&c.proxRRN, sizeof(int), 1, bin);
    fread(&c.nroRegRem, sizeof(int), 1, bin);
    fread(&c.nroPagDisco, sizeof(int), 1, bin);
    return c;
}

void lendo_csv(char *nomeCSV, FILE *nomeBin, Cabecalho cabecalho, Registro registro) {
    
    int tamT = 0, tamD = 0, tamA = 0, tamE = 0, tamH = 0, tam = 0; //variaveis que irao armazenar os tamanhos dos campos variaveis
    char linha[160]; // uma variavel responsavel por receber o registro completo
    char *campo;

    FILE *arquivo_csv = fopen(nomeCSV, "r");
    if (arquivo_csv == NULL) {
        printf("Falha ao abrir o arquivo CSV\n");
        return;
    }

    leitura_cabecalho(cabecalho, nomeBin);
    printf("SL: %c \n", cabecalho.status);
    char buffer[160];
    // Lendo o cabeçalho do arquivo CSV (nomes das colunas)
    fgets(buffer, sizeof(buffer), arquivo_csv); // Pula a linha de cabeçalho

  
    while (fgets(linha, sizeof(linha), arquivo_csv)) {
        // Remove os caracteres de nova linha (tanto \n quanto \r)
        linha[strcspn(linha, "\n")] = '\0'; //remove o \n e \r de cada linha do csv
        linha[strcspn(linha, "\r")] = '\0';
   
        // Início da leitura dos campos separados por vírgula
        char *linha_copy = linha;

        // Nome
        campo = strsep(&linha_copy, ","); //usando a função strsep para dividir em tokens

        if (campo != NULL) {
            tam = strlen(campo);
            registro.nome = (char*) malloc((tam + 1) * sizeof(char));
            strcpy(registro.nome, campo);
            registro.nome[tam] = '#'; // Finaliza com '#'
        }
        
        // Dieta
        campo = strsep(&linha_copy, ",");
        if (campo != NULL) {
            tamD = strlen(campo);
            registro.dieta = (char*) malloc((tamD + 1) * sizeof(char));
            strcpy(registro.dieta, campo);
            registro.dieta[tamD] = '#'; // Finaliza com '#'
           
        }

        // Habitat
        campo = strsep(&linha_copy, ",");
        if (campo != NULL) {
            tamH = strlen(campo);
            registro.habitat = (char*) malloc((tamH + 1) * sizeof(char));
            strcpy(registro.habitat, campo);
            registro.habitat[tamH] = '#'; // Finaliza com '#'
              
        }

        // População
        campo = strsep(&linha_copy, ",");
        if(campo != NULL)
        {
            registro.populacao = atoi(campo);
        }
        else{
            registro.populacao = -1; //para caso de poulação -> null
        }

        // Tipo
        campo = strsep(&linha_copy, ",");
        if (campo != NULL) {
            tamT = strlen(campo);
            registro.tipo = (char*) malloc((tamT + 1) * sizeof(char));
            strcpy(registro.tipo, campo);
            registro.tipo[tamT] = '#'; // Finaliza com '#'
        }

        // Velocidade
        campo = strsep(&linha_copy, ",");
        if(campo != NULL)
        {
            registro.velocidade = atoi(campo);
        }
        else{
            registro.populacao = -1;
        }

        // Unidade de medida
        campo = strsep(&linha_copy, ",");
        registro.uniMedida = (campo != NULL) ? campo[0] : '$';
        if(campo != NULL)
        {
            registro.uniMedida = campo[0];
        }
        else{
            registro.uniMedida = '$';
        }

        // Tamanho
        campo = strsep(&linha_copy, ",");
        if(campo != NULL)
        {
            registro.tamanho = atof(campo);
        }
        else{
            registro.tamanho = -1;
        }

        // Espécie
        campo = strsep(&linha_copy, ",");
        if (campo != NULL) {
            tamE = strlen(campo);
            registro.nEspecie = (char*) malloc((tamE + 1) * sizeof(char));
            strcpy(registro.nEspecie, campo);
            registro.nEspecie[tamE] = '#'; // Finaliza com '#'
        }

        // Alimento
        campo = strsep(&linha_copy, ",");
        if (campo != NULL) {
            tamA = strlen(campo);
           registro.alimento = (char*) malloc((tamA + 1) * sizeof(char));
            strcpy(registro.alimento, campo);
            registro.alimento[tamA] = '#'; // Finaliza com '#'
        }

        // Calcular bytes restantes para completar os 160 bytes
        int soma = 160 - (tam + tamD + tamH + tamT + tamE + tamA + 18);

        // Armazena o registro no arquivo binário
        registro.removido = '0'; // não removido
        registro.encadeamento = 0; // não há encadeamento
        
        // Função fictícia para armazenar o registro no arquivo binário
        Escrevebin(nomeBin, registro,  cabecalho);

        // Libera a memória alocada
        free(registro.nome);
        free(registro.dieta);
        free(registro.habitat);
        free(registro.tipo);
        free(registro.nEspecie);
        free(registro.alimento);
    }
    

    fclose(arquivo_csv);
   
}

void Escrevebin(FILE *nomebin, Registro registro,  Cabecalho cabecalho) {
    // Escreve campos de tamanho fixo
    fwrite(&registro.removido, sizeof(char), 1, nomebin);
    fwrite(&registro.encadeamento, sizeof(int), 1, nomebin);
    fwrite(&registro.populacao, sizeof(int), 1, nomebin);
    fwrite(&registro.tamanho, sizeof(float), 1, nomebin);
    fwrite(&registro.uniMedida, sizeof(char), 1, nomebin);
    fwrite(&registro.velocidade, sizeof(int), 1, nomebin);

    // Escreve strings (sem \0, já que é um formato binário e tamanho variável) usando o tamanho de cada uma
    int tamT = 0, tamD = 0, tamA = 0, tamE = 0, tamH = 0, tam = 0;
    tam = strlen(registro.nome);
    tamA = strlen(registro.alimento);
    tamD = strlen(registro.dieta);
    tamE = strlen(registro.nEspecie);
    tamT = strlen(registro.tipo);
    tamH = strlen(registro.habitat);
    fwrite(registro.nome, sizeof(char), tam, nomebin);
    fwrite(registro.nEspecie, sizeof(char), tamE, nomebin);
    fwrite(registro.habitat, sizeof(char), tamH, nomebin);
    fwrite(registro.tipo, sizeof(char), tamT, nomebin);
    fwrite(registro.dieta, sizeof(char), tamD, nomebin);
    fwrite(registro.alimento, sizeof(char), tamA, nomebin);

    // Calcula o tamanho já escrito (campos fixos + strings)
    int tamanhoEscrito = sizeof(char)    // removido
                       + sizeof(int)     // encadeamento
                       + sizeof(int)     // populacao
                       + sizeof(float)   // tamanho
                       + sizeof(char)    // uniMedida
                       + sizeof(int)     // velocidade
    + tam + tamA + tamD + tamE + tamH + tamT;

    // Verifica quanto falta para completar os 160 bytes
    int espacoRestante = 160 - tamanhoEscrito;
    if (espacoRestante > 0) {
        char preenchimento[espacoRestante];
        memset(preenchimento, '$', espacoRestante); //preenchendo o vetor com $
        fwrite(preenchimento, sizeof(char), espacoRestante, nomebin);
    }


   
}


// Função para recuperar todos os registros e mostrar na saída padrão (função 2)
//registro
// agora quando status 1 o arquivo é lido e da o print porem com dados problemáticos
// estando fragmentados, parece que o codigo nao esta separando corretamente oq deveria ser cada variavel 
// verificar se o registro foi logicamente removido
void recuperar_todos_os_registros(char *nomeBin) {
    FILE *arquivo_binario = fopen(nomeBin, "rb");
    if (arquivo_binario == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    Cabecalho cabecalho;
    if (fread(&cabecalho, sizeof(Cabecalho), 1600, arquivo_binario) != 1) { //lendo todo o cabeçalho
        printf("Erro ao ler o cabeçalho do arquivo.\n");
        fclose(arquivo_binario);
        return;
    }

    printf("Status: %c\n", cabecalho.status);

    if (cabecalho.status == '0') {
        printf("Falha no processamento do arquivo: arquivo inconsistente.\n");
        fclose(arquivo_binario);
        return;
    }

    Registro registro;
    int registros_encontrados = 0;

    while (fread(&registro.removido, sizeof(char), 1, arquivo_binario) == 1) {
        // Verificar se o registro foi logicamente removido
        if (registro.removido == '1') {
            fseek(arquivo_binario, 160 - sizeof(char), SEEK_CUR); // Pular para o próximo registro
            continue; // Ignorar registros removidos
        }

        fread(&registro.encadeamento, sizeof(int), 1, arquivo_binario);
        fread(&registro.populacao, sizeof(int), 1, arquivo_binario);
        fread(&registro.tamanho, sizeof(float), 1, arquivo_binario);
        fread(&registro.uniMedida, sizeof(char), 1, arquivo_binario);
        fread(&registro.velocidade, sizeof(int), 1, arquivo_binario);

        

        // Exibir os dados do registro
        registros_encontrados++;
        printf("Nome: %s\n", registro.nome);
        printf("Dieta: %s\n", registro.dieta);
        printf("Habitat: %s\n", registro.habitat);
        printf("População: %d\n", registro.populacao);
        printf("Tipo: %s\n", registro.tipo);
        printf("Velocidade: %d %c/h\n", registro.velocidade, registro.uniMedida);
        printf("Tamanho: %.2f\n", registro.tamanho);
        printf("Espécie: %s\n", registro.nEspecie);
        printf("Alimento: %s\n", registro.alimento);
        printf("\n");

        // Libera memória alocada para strings
        free(registro.nome);
        free(registro.dieta);
        free(registro.habitat);
        free(registro.tipo);
        free(registro.nEspecie);
        free(registro.alimento);
    }

    if (registros_encontrados == 0) {
        printf("Registro inexistente.\n");
    }

    fclose(arquivo_binario);
}

void buscar_registros_por_campo(char *nomeBin, int n) { // func 3 que busca registros por campo n vezes
    FILE *arquivo_binario = fopen(nomeBin, "rb");
    if (arquivo_binario == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    Cabecalho cabecalho;
    if (fread(&cabecalho, sizeof(Cabecalho), 1, arquivo_binario) != 1) {
        printf("Erro ao ler o cabeçalho do arquivo.\n");
        fclose(arquivo_binario);
        return;
    }

    // Verificar se o arquivo está consistente
    if (cabecalho.status == '0') {
        printf("Falha no processamento do arquivo: arquivo inconsistente.\n");
        fclose(arquivo_binario);
        return;
    }
    // para cada n vezes ira ler o campo e o valor do campo
    for (int i = 0; i < n; i++) {
        char nomeCampo[30];
        char valorCampo[100];
        int registros_encontrados = 0;

        // Lê o nome do campo e o valor do campo
        scanf("%s", nomeCampo);
        scan_quote_string(valorCampo); // Usa a função fornecida para tratar strings com aspas

        Registro registro;
        rewind(arquivo_binario); // Volta para o início do arquivo binário após o cabeçalho
        fseek(arquivo_binario, sizeof(Cabecalho), SEEK_SET); // Pula o cabeçalho do arquivo binário

        // Ler registros do arquivo binário
        while (fread(&registro.removido, sizeof(char), 1, arquivo_binario) == 1) {
            if (registro.removido == '1') {
                // Pular registros removidos
                fseek(arquivo_binario, sizeof(int) + sizeof(int) + sizeof(float) + sizeof(char) + sizeof(int) + 160, SEEK_CUR);
                continue;
            }

            fread(&registro.encadeamento, sizeof(int), 1, arquivo_binario);
            fread(&registro.populacao, sizeof(int), 1, arquivo_binario);
            fread(&registro.tamanho, sizeof(float), 1, arquivo_binario);
            fread(&registro.uniMedida, sizeof(char), 1, arquivo_binario);
            fread(&registro.velocidade, sizeof(int), 1, arquivo_binario);

            // Ler strings de tamanho variável (nome, dieta, habitat, tipo, etc.)
            char buffer[100];
            int tamanho_string;

            // Ler e comparar o campo especificado
            if (strcmp(nomeCampo, "nome") == 0) {
                fread(&tamanho_string, sizeof(int), 1, arquivo_binario);
                fread(buffer, sizeof(char), tamanho_string, arquivo_binario);
                buffer[tamanho_string] = '\0';
                if (strcmp(buffer, valorCampo) == 0) {
                    printf("Nome: %s\n", buffer);
                    registros_encontrados++;
                }
            } else if (strcmp(nomeCampo, "dieta") == 0) {
                fread(&tamanho_string, sizeof(int), 1, arquivo_binario);
                fread(buffer, sizeof(char), tamanho_string, arquivo_binario);
                buffer[tamanho_string] = '\0';
                if (strcmp(buffer, valorCampo) == 0) {
                    printf("Dieta: %s\n", buffer);
                    registros_encontrados++;
                }
            } else if (strcmp(nomeCampo, "habitat") == 0) {
                fread(&tamanho_string, sizeof(int), 1, arquivo_binario);
                fread(buffer, sizeof(char), tamanho_string, arquivo_binario);
                buffer[tamanho_string] = '\0';
                if (strcmp(buffer, valorCampo) == 0) {
                    printf("Habitat: %s\n", buffer);
                    registros_encontrados++;
                }
            } else if (strcmp(nomeCampo, "populacao") == 0) {
                fread(&tamanho_string, sizeof(int), 1, arquivo_binario);
                fread(buffer, sizeof(char), tamanho_string, arquivo_binario);
                buffer[tamanho_string] = '\0';
                if (atoi(buffer) == atoi(valorCampo)) {
                    printf("População: %s\n", buffer);
                    registros_encontrados++;
                }
            } // continue comparando para outros campos, como tipo, velocidade, etc.

            // Pular para o próximo registro no arquivo binário
            fseek(arquivo_binario, sizeof(int) + sizeof(float) + sizeof(int) + 160, SEEK_CUR);
        }

        if (registros_encontrados == 0) {
            printf("Registro inexistente.\n");
        }



    }


    fclose(arquivo_binario);
}