#include "func_basc.h"

typedef struct info {
    int especieID;
    char nome[41];
    char nome_cientifico[61];
    int populacao;
    char status[9];
    float localizacao[2]; //coordeanadas em x e y cada com 4 bytes
    int impacto_humano;

}Registro;

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

void RegistrodeEspecies(char *nomearquivo, int num)
{       
    char coordx[4], coordy[4], populacao[4], local[8], impacto[4], Id[4];
    Registro *animais = malloc(num * sizeof(*animais));

    FILE *file = fopen(nomearquivo, "ab"); // Abre o arquivo para adicionar (append)
    if (file == NULL) {
        printf("Erro ao abrir o arquivo");
        return;
    }

        for (int i = 0; i < num; i++)
        {
            // Ler dados para cada registro
            readline(Id);
            animais[i].especieID = atoi(Id);
            readline(animais[i].nome);
            readline(animais[i].nome_cientifico);
            readline(populacao);
            animais[i].populacao = atoi(populacao);
            readline(animais[i].status);

            readline(coordx);
            animais[i].localizacao[0] = atof(coordx); // Converter string para float

            readline(coordy);
            animais[i].localizacao[1] = atof(coordy);

            readline(impacto);
            animais[i].impacto_humano = atoi(impacto);

            fwrite(&animais[i], sizeof(Registro), 1, file);
        }
        
    fclose(file);
    free(animais);
}