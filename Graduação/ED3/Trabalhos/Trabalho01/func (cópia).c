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

void lendo_csv(char *nomeCSV, FILE *nomeBin, Cabecalho *cabecalho, Registro registro) {
    
    int tamT = 0, tamD = 0, tamA = 0, tamE = 0, tamH = 0, tam = 0;
    char linha[160]; // Tamanho máximo que o registro pode ocupar
    char *campo;

    FILE *arquivo_csv = fopen(nomeCSV, "r");
    if (arquivo_csv == NULL) {
        printf("Falha ao abrir o arquivo CSV\n");
        return;
    }

    // Marca o status do cabeçalho como '1'
    cabecalho->status = '1';
    fwrite(cabecalho, sizeof(Cabecalho), 1, nomeBin);
    char buffer[160];
    // Lendo o cabeçalho do arquivo CSV (nomes das colunas)
    fgets(buffer, sizeof(buffer), arquivo_csv); // Pula a linha de cabeçalho

  
    while (fgets(linha, sizeof(linha), arquivo_csv)) {
        // Remove os caracteres de nova linha (tanto \n quanto \r)
        linha[strcspn(linha, "\n")] = '\0';
        linha[strcspn(linha, "\r")] = '\0';
   
        // Início da leitura dos campos separados por vírgula
        char *linha_copy = linha;

        // Nome
        campo = strsep(&linha_copy, ",");

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
            registro.populacao = -1;
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

void Escrevebin(FILE *nomebin, Registro registro,  Cabecalho *cabecalho) {
    // Escreve campos de tamanho fixo
    fwrite(&registro.removido, sizeof(char), 1, nomebin);
    fwrite(&registro.encadeamento, sizeof(int), 1, nomebin);
    fwrite(&registro.populacao, sizeof(int), 1, nomebin);
    fwrite(&registro.tamanho, sizeof(float), 1, nomebin);
    fwrite(&registro.uniMedida, sizeof(char), 1, nomebin);
    fwrite(&registro.velocidade, sizeof(int), 1, nomebin);

    // Escreve strings (sem \0, já que é um formato binário e tamanho variável)
    fwrite(registro.nome, sizeof(char), strlen(registro.nome), nomebin);
    fwrite(registro.nEspecie, sizeof(char), strlen(registro.nEspecie), nomebin);
    fwrite(registro.habitat, sizeof(char), strlen(registro.habitat), nomebin);
    fwrite(registro.tipo, sizeof(char), strlen(registro.tipo), nomebin);
    fwrite(registro.dieta, sizeof(char), strlen(registro.dieta), nomebin);
    fwrite(registro.alimento, sizeof(char), strlen(registro.alimento), nomebin);

    // Calcula o tamanho já escrito (campos fixos + strings)
    int tamanhoEscrito = sizeof(char)    // removido
                       + sizeof(int)     // encadeamento
                       + sizeof(int)     // populacao
                       + sizeof(float)   // tamanho
                       + sizeof(char)    // uniMedida
                       + sizeof(int)     // velocidade
    + strlen(registro.nome)+ strlen(registro.dieta)+ strlen(registro.habitat)+ strlen(registro.tipo)+ strlen(registro.nEspecie)+ strlen(registro.alimento);

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
void recuperar_dados(char *nomeBin, Registro dino){
    Cabecalho cabecalho;
    int flag =1;
    //abertura do arquivo binario
    FILE* arq = fopen(nomeBin, "rb");
    if (arq == NULL) {
        printf("Falha no processamento do arquivo\n");
        return;
    }
    //um teste para tentar ler o cabeçalho 
    char bufferc[1600];
    int bytesLidos = fread(bufferc, sizeof(char), 1600, arq); 

    // Adicionar terminador nulo na posição correta, se os dados forem menores que 1600
    if (bytesLidos < 1600) {
        bufferc[bytesLidos] = '\0';
    } else {
        bufferc[1599] = '\0'; // Para evitar leitura fora dos limites, garantir terminador
    }
    /*for(int i=0; i< 1600; i++)
    {
        printf("%c ", bufferc[i]); // Agora é seguro imprimir
    }*/

    //sabemos que cada registro so pode ocupar 160 bytes
    // o primeiro byte é para o removido, depois os proximos 4 é para o encadeamento e assimpor adiante até atingirmos os campos variaveis
    //uma outra certeza é que $ sempre será lixo e # é o final de uma campo
    char aux[160];  // Buffer para um registro de 160 bytes
char *campo;    // Para armazenar o campo lido


while (fread(aux, sizeof(char), 160, arq) != 0) // Lendo um registro completo de 160 bytes
{
    // Imprime o conteúdo bruto do registro para depuração
    printf("Registro lido: %s\n", aux);
    
    char *linha_copy = aux; // Copia o buffer atual para linha_copy para manipulação

    // Processa o registro
    while ((campo = strsep(&linha_copy, "#")) != NULL) {
        // Verifica se o campo não é apenas formado por '$'
        bool isLixo = true;  // Assume que o campo é lixo até encontrar um caractere válido
        for (int i = 0; campo[i] != '\0'; i++) {
            if (campo[i] != '$') {
                isLixo = false; // Encontrou um caractere válido
                break;
            }
        }
        
        if (!isLixo) {
            printf("Campo: %s\n", campo); // Imprime o campo válido
        }
    }

    printf("\n"); // Nova linha para s    printf("\n"); // Nova linha para separar registros
}

}



   
/*
while (1) {
                registroAtual = ArquivodeRegistro(arq);

                // Interrompe o loop se encontrar o final dos registros
                if (registroAtual.especieID == -1) {
                    break;
                }

                // Imprime o registro
                PrintRegistros(registroAtual);
            }
*/

    
}
void PrintaRegistros(Registro dinossauro) //função que imprime os dados sobre os dinossauros
{
    // Exibir os dados do registro
    printf("Nome: %s\n", dinossauro.nome);
    printf("Dieta: %s\n", dinossauro.dieta);
    printf("Habitat: %s\n", dinossauro.habitat);
    printf("População: %d\n", dinossauro.populacao);
    printf("Tipo: %s\n", dinossauro.tipo);
    printf("Velocidade: %d %c/h\n", dinossauro.velocidade, dinossauro.uniMedida);
    printf("Tamanho: %.2f\n", dinossauro.tamanho);
    printf("Espécie: %s\n", dinossauro.nEspecie);
    printf("Alimento: %s\n", dinossauro.alimento);
    printf("\n");
}
// Função para recuperar todos os registros e mostrar na saída padrão (função 2)
void buscar_registros_por_campo(char *nomeBin, int n) {
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