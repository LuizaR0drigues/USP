

#include "func_basc.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>




void readline(char* string) { //função para ler a linha
    char c = 0;

    do {
        c = (char)getchar();
    } while (c == '\n' || c == '\r');

    int i = 0;

    do {
        string[i] = c;
        i++;
        c = getchar();
    } while (c != '\n' && c != '\r');

    string[i] = '\0';
}

void binarioNaTela(char* nomeArquivoBinario) { /* Você não precisa entender o código dessa função. */
    unsigned long i, cs;
    unsigned char* mb;
    size_t fl;
    FILE* fs;
    if (nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
        fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela): não foi possível abrir o arquivo que me passou para leitura. Ele existe e você tá passando o nome certo? Você lembrou de fechar ele com fclose depois de usar?\n");
        return;
    }
    fseek(fs, 0, SEEK_END);
    fl = ftell(fs);
    fseek(fs, 0, SEEK_SET);
    mb = (unsigned char*)malloc(fl);
    fread(mb, 1, fl, fs);

    cs = 0;
    for (i = 0; i < fl; i++) {
        cs += (unsigned long)mb[i];
    }
    printf("%lf\n", (cs / (double)100));
    free(mb);
    fclose(fs);
}
// Função que cria e inicializa uma estrutura do tipo Registro com valores padrão
Registro RegistrodeIndividuo() 
{
    Registro individuo;

    // Inicializa o campo especieID com um valor neutro (0)
    individuo.especieID = 0;

    // Preenche o campo status com o caractere '$'
    // O campo status tem tamanho fixo de 9 bytes
    for (int i = 0; i < 9; i++) 
    {
        individuo.status[i] = '$';
    }

    // Preenche o campo nome com o caractere '$'
    // O campo nome tem tamanho fixo de 41 bytes
    for (int i = 0; i < 41; i++) 
    {
        individuo.nome[i] = '$';
    }

    // Preenche o campo nome_cientifico com o caractere '$'
    // O campo nome_cientifico tem tamanho fixo de 61 bytes
    for (int i = 0; i < 61; i++) 
    {
        individuo.nome_cientifico[i] = '$';
    }

    // Inicializa o campo impacto_humano com um valor neutro (0)
    individuo.impacto_humano = 0;

    // Inicializa o campo populacao com um valor neutro (0)
    individuo.populacao = 0;

    // Inicializa o campo localizacao com as coordenadas (0.0, 0.0)
    individuo.localizacao[0] = 0.0;
    individuo.localizacao[1] = 0.0;

    // Retorna a estrutura inicializada
    return individuo;
}


Registro RegistrodeEspecies() //leitura dos dados 
{   
    Registro especie = RegistrodeIndividuo();

    // Ler dados para cada registro

    scanf("%d", &especie.especieID); 
    readline(especie.nome);
    readline(especie.nome_cientifico);
    scanf("%d",&especie.populacao);
    readline(especie.status);
    scanf("%f",&especie.localizacao[0]);
    scanf("%f",&especie.localizacao[1]);
    scanf("%d",&especie.impacto_humano);
    
    return especie;
}

Registro ArquivodeRegistro(FILE* file){ 

    Registro especie = RegistrodeIndividuo(); //cria o padrão

    if(!fread(&especie.especieID, sizeof(int), 1, file))    //se não tiver o que ler
    {
        especie.especieID  = -1;
        return especie;
    }
    // Lendo os dados do arquivo
    fread(especie.nome, sizeof(char), 41, file);
    fread(especie.nome_cientifico, sizeof(char), 61, file);
    fread(&especie.populacao, sizeof(int), 1, file);
    fread(especie.status, sizeof(char), 9, file);
    fread(&especie.localizacao[0], sizeof(float), 1, file);
    fread(&especie.localizacao[1], sizeof(float), 1, file);
    fread(&especie.impacto_humano, sizeof(int), 1, file);

    return especie;
}


void Arquivobin(FILE* file, Registro especie){    //escreve no arquivo 
    
    // Escrevendo os dados no arquivo com a função fwrite
    fwrite(&especie.especieID, sizeof(int), 1, file);
    fwrite(especie.nome, sizeof(char), 41, file);
    fwrite(especie.nome_cientifico, sizeof(char), 61, file);
    fwrite(&especie.populacao, sizeof(int), 1, file);
    fwrite(especie.status, sizeof(char), 9, file);
    fwrite(&especie.localizacao[0], sizeof(float), 1, file);
    fwrite(&especie.localizacao[1], sizeof(float), 1, file);
    fwrite(&especie.impacto_humano, sizeof(int), 1, file);
    
}
void PrintRegistros(Registro especie)
{
    
    // Lendo e imprimindo cada registro
        printf("ID: %d\n", especie.especieID);
        printf("Nome: %s\n", especie.nome);
        printf("Nome Científico: %s\n", especie.nome_cientifico);
        //tratamento dos casos nulos e com dados
        if(especie.populacao == 0)
            printf("População: NULO\n");
        else{
            printf("População: %d\n",  especie.populacao);
        }
        printf("Status: %s\n", especie.status);
        printf("Localização: (%.2f, %.2f)\n", especie.localizacao[0], especie.localizacao[1]);
        //tratamento dos casos nulos e com dados
        if(especie.impacto_humano == 0)
            printf("Impacto Humano: NULO\n\n");
        else{
            printf("Impacto Humano: %d\n\n",  especie.impacto_humano);
        }

}
//fseek
//Move o cursor de leitura/escrita no arquivo para a posição especificada
// offset: deslocamento em bytes, whence: referência (SEEK_SET, SEEK_CUR, SEEK_END)


Registro BuscaIndividuo(char *nomearquivo, int rrn) {
    int tamregistro = 4+41+61+4+9+ 2 *4 +4 ; //tam = somatoria dos tamanhos dos campos das variaveis, o conjunto da especie

    FILE *file; 
    if (nomearquivo == NULL || !(file =fopen(nomearquivo, "rb"))) { //se nao deu problema algum (por enquanto)
        printf("Falha no processamento do arquivo\n");
    }
   
    //printf("%d\n", rrn * tamregistro);
    fseek(file, rrn * tamregistro, SEEK_SET); //vai para o RRN desejado
    Registro especie;
    especie = ArquivodeRegistro(file);

    if (especie.especieID == -1) {  //caso o arquivo nao tenha o que ler
        printf("Espécie não encontrada\n");
    } 
    else { // caso bem sucedido deve printar as informações seguintes
        PrintRegistros(especie);
    }

    fclose(file);
}
void atualizarInformacoes(char *nomearquivo, int idb, int numInfob) {
    // Inicializa a estrutura de registro com valores padrão
    Registro especie = RegistrodeIndividuo();
    int encontrado = 0; // Flag para verificar se a espécie foi encontrada
    int tamanho_registro = 4 + 41 + 61 + 4 + 9 + 2 * 4 + 4; // Tamanho total de um registro
    int registro_pos = 0; // Posição do registro no arquivo
    char tipo[50], info[50];
    
    // Abre o arquivo binário para leitura e escrita
    FILE *file = fopen(nomearquivo, "rb+");
    if (!file) {
        printf("Falha no processamento do arquivo\n");
        return;
    }

    // Procura o registro com o ID correspondente
    while (fread(&especie.especieID, sizeof(int), 1, file)) {
        if (especie.especieID == idb) {
            encontrado = 1;
            break;
        }
        registro_pos++;
        fseek(file, registro_pos * tamanho_registro, SEEK_SET);
    }

    // Verifica se o registro foi encontrado
    if (!encontrado) {
        printf("Espécie não encontrada\n");
        binarioNaTela(nomearquivo); // Exibe o conteúdo do arquivo binário
        fclose(file);
        return;
    }

    // Reposiciona o cursor do arquivo para o início do registro encontrado
    fseek(file, registro_pos * tamanho_registro, SEEK_SET);
    especie = ArquivodeRegistro(file); // Lê o registro encontrado

    // Atualiza as informações do registro conforme fornecido
    for (int i = 0; i < numInfob; i++) {
        readline(tipo); // Lê o tipo de informação a ser atualizada
        readline(info); // Lê o valor da informação

        if (strcmp(tipo, "STATUS") == 0) {
            if (strcmp(especie.status, "NULO") == 0) {
                strcpy(especie.status, info);
            } else {
                printf("Informação já inserida no arquivo\n");
            }
        } else if (strcmp(tipo, "HUMAN IMPACT") == 0) {
            if (especie.impacto_humano == 0) {
                especie.impacto_humano = atoi(info);
            } else {
                printf("Informação já inserida no arquivo\n");
            }
        } else if (strcmp(tipo, "POPULATION") == 0) {
            if (especie.populacao == 0) {
                especie.populacao = atoi(info);
            } else {
                printf("Informação já inserida no arquivo\n");
            }
        }
    }

    // Reposiciona o cursor do arquivo para o início do registro e atualiza o arquivo
    fseek(file, registro_pos * tamanho_registro, SEEK_SET);
    Arquivobin(file, especie); // Escreve o registro atualizado no arquivo

    // Fecha o arquivo e exibe o conteúdo modificado
    fclose(file);
    binarioNaTela(nomearquivo);
}

