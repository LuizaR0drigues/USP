#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func_basc.h"

int main()
{
    int n, comando;
    char lininicial[50], frase[100];
    char *token, nomearq[20];

    // função readline a strtok para capturar o comando
    readline(lininicial);

    // Captura o primeiro token que contém o comando
    token = strtok(lininicial, " "); // Divide a string em tokens a partir do espaço
    comando = atoi(token);           // Transforma o primeiro token (comando) de char para int

    // Captura o próximo token que é o nome do arquivo
    token = strtok(NULL, " "); // Continua a partir do próximo token (nome do arquivo)
    if (token != NULL) {
        strcpy(nomearq, token); // Copia o nome do arquivo para a variável 'nomearq'
    }
    printf("%s\n", nomearq);
    switch (comando)
    {
    case 1:
        scanf("%d", &n); // qtd registros a serem lidos
        RegistrodeEspecies(nomearq, n);
        binarioNaTela(nomearq);
        break;
    case 2:
        
        break;
    case 3:
        break;
    case 4:
        break;
    }

    return 0;
}