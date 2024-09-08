#include "func_basc.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>




void readline(char* string) {
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

Registro RegistrodeIndividuo()
{
    Registro individuo;
    individuo.especieID = 0; //valor neutro

    for(int i =0; i< 41; i++) //41 é o tamnaho do campo nome
    {
        individuo.nome[i] = '$';
    }

    for(int i=0; i<61; i++) //61 é onome cientifico o tamanho do campo 
    {
        individuo.nome_cientifico[i] = '$';
    }
     individuo.populacao = 0;
    for(int i=0; i<9; i++)
    {
        individuo.status[i] ='$';
    }
    individuo.impacto_humano = 0;

    return individuo;
}

Registro RegistrodeEspecies(char *nomearquivo, int qtd)
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

Registro ArquivodeRegistro(char *nomearquivo, int qtd){

    FILE *file = fopen(nomearquivo, "rb");
    if (file == NULL) {
        printf("Falha no processamento do arquivo\n");

    }

    Registro especie = RegistrodeIndividuo(); //cria o padrão

    if(!fread(&especie.especieID, sizeof(int), 1, file))
    {
        especie.especieID  = -1;
        fclose(file);
        return especie;
    }

    fread(especie.nome, sizeof(char), 41, file);
    fread(especie.nome_cientifico, sizeof(char), 61, file);
    fread(&especie.populacao, sizeof(int), 1, file);
    fread(especie.status, sizeof(char), 9, file);
    fread(&especie.localizacao[0], sizeof(float), 1, file);
    fread(&especie.localizacao[1], sizeof(float), 1, file);
    fread(&especie.impacto_humano, sizeof(int), 1, file);

    return especie;
}


void Arquivobin(FILE* file, Registro especie){    

    fwrite(especie.nome, sizeof(char), 41, file);
    fwrite(especie.nome_cientifico, sizeof(char), 61, file);
    fwrite(&especie.populacao, sizeof(int), 1, file);
    fwrite(especie.status, sizeof(char), 9, file);
    fwrite(&especie.localizacao[0], sizeof(float), 1, file);
    fwrite(&especie.localizacao[1], sizeof(float), 1, file);
    fwrite(&especie.impacto_humano, sizeof(int), 1, file);


    
}
void PrintRegistros(int qtd)
{
    Registro especie;
    int i = 0;

    // Lendo e imprimindo cada registro
     while (i < qtd) {
        printf("ID: %d\n", especie.especieID);
        printf("Nome: %s\n", strcmp(especie.nome, "") == 0 ? "NULO" : especie.nome);
        printf("Nome Científico: %s\n", strcmp(especie.nome_cientifico, "") == 0 ? "NULO" : especie.nome_cientifico);
        printf("População: %d\n", especie.populacao == 0 ? 0 : especie.populacao);
        printf("Status: %s\n", strcmp(especie.status, "") == 0 ? "NULO" : especie.status);
        printf("Localização: %f %f\n", especie.localizacao[0], especie.localizacao[1]);
        printf("Impacto Humano: %d\n\n", especie.impacto_humano == 0 ? 0 : especie.impacto_humano);
        i++;
    }

}


void BuscaIndividuo(char *nomearquivo, int rrn) {
    FILE *file = fopen(nomearquivo, "rb");
    if (file == NULL) { //se nao deu problema algum (por enquanto)
        printf("Falha no processamento do arquivo\n");
        return;
    }

    Registro especie;
    fseek(file, rrn * sizeof(Registro), SEEK_SET); //vai para o RRN desejado
    size_t tamanho_registro = sizeof(Registro); //tamanho do registro   
    if (fread(&especie, tamanho_registro, 1, file) != 1) {  //caso o arquivo nao tenha o que ler
        printf("Espécie não encontrada\n");
    } else { // caso bem sucedido deve printar as informações seguintes
        printf("ID: %d\n", especie.especieID);
        printf("Nome: %s\n", strcmp(especie.nome, "") == 0 ? "NULO" : especie.nome);
        printf("Nome Científico: %s\n", strcmp(especie.nome_cientifico, "") == 0 ? "NULO" : especie.nome_cientifico);
        printf("População: %d\n", especie.populacao == 0 ? 0 : especie.populacao);
        printf("Status: %s\n", strcmp(especie.status, "") == 0 ? "NULO" : especie.status);
        printf("Localização: (%.2f, %.2f)\n", especie.localizacao[0], especie.localizacao[1]);
        printf("Impacto Humano: %d\n", especie.impacto_humano);
    }

    fclose(file);
}

void atualizarInformacoes(const char *nomearquivo, int id, int numInfo) {
    FILE *file = fopen(nomearquivo, "r+b"); 
    if (file == NULL) {  //se nao deu problema algum (por enquanto)
        printf("Falha no processamento do arquivo\n");
        return;
    }

    Registro especie;  // nossa sctruct 
    int encontrado = 0; //flag para saber se encontrou ou nao
    size_t tamanho_registro = sizeof(Registro);   

    while (fread(&especie, tamanho_registro, 1, file)) { //enquanto tiver conteudo para ler
        if (especie.especieID == id) { 
            encontrado = 1;
            fseek(file, -tamanho_registro, SEEK_CUR); //volta para o inicio do registro

            for (int i = 0; i < numInfo; i++) { //enqauanto tiver informação para atualizar
                char tipo[20];
                char dado[20];
                
                // Ler o tipo e o dado a ser atualizado
                readline(tipo); 
                
               //se o tipo for igual a status, ele vai atualizar o status  
                readline(dado);

                if (strcmp(tipo, "STATUS") == 0) {
                    strncpy(especie.status, dado, sizeof(especie.status) - 1);
                    especie.status[sizeof(especie.status) - 1] = '\0';  // Garantir terminação
                } else if (strcmp(tipo, "HUMAN IMPACT") == 0) {
                    especie.impacto_humano = atoi(dado);
                } else if (strcmp(tipo, "POPULATION") == 0) {
                    especie.populacao = atoi(dado);
                } else {
                    printf("Tipo de informação inválido\n");
                    continue;
                }

                fwrite(&especie, sizeof(Registro), 1, file);
            }
            break;
        }
    }

    if (!encontrado) {
        printf("Espécie não encontrada\n");
    }

    fclose(file);
}
