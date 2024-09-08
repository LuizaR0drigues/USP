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

Registro RegistrodeIndividuo() //criação da struct padrão
{
    Registro individuo;
    individuo.especieID = 0; //valor neutro

    individuo.nome = malloc(41 * sizeof(char));
    for(int i =0; i< 41; i++) //41 é o tamnaho do campo nome
    {
        individuo.nome[i] = '$';
    }
    individuo.nome_cientifico =malloc(61 * sizeof(char));
    for(int i=0; i< 61; i++) //61 é onome cientifico o tamanho do campo 
    {
        individuo.nome_cientifico[i] = '$';
    }

    individuo.populacao = 0;
    individuo.status =malloc(9 * sizeof(char));
    for(int i=0; i<9; i++)
    {
        individuo.status[i] ='$';
    }
    
    memccpy(individuo.localizacao, (int[]){0, 0}, sizeof(float), 2);
    individuo.impacto_humano = 0;
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

    if(!fread(&especie.especieID, sizeof(int), 1, file))
    {
        especie.especieID  = -1;
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
        if(especie.populacao == 0)
            printf("População: NULO\n");
        else{
            printf("População: %d\n",  especie.populacao);
        }
        printf("Status: %s\n", especie.status);
        printf("Localização: (%.2f, %.2f)\n", especie.localizacao[0], especie.localizacao[1]);
        if(especie.impacto_humano == 0)
            printf("Impacto Humano: NULO\n\n");
        else{
            printf("Impacto Humano: %d\n\n",  especie.impacto_humano);
        }
        
        
    

}


Registro BuscaIndividuo(char *nomearquivo, int rrn) {
    int tamregistro = 4+41+61+4+9+ 2 *4 +4 ; //tam = somatoria dos tamanhos dos campos das variaveis

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
    freememoria(&especie);
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
void freememoria(Registro *especie)
{
    if (especie != NULL) {
        free(especie->nome);
        free(especie->nome_cientifico);
        free(especie->status);
    }
}
