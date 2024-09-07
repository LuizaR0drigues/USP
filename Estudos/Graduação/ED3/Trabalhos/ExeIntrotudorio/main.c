#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func_basc.h"

int main()
{
    int n, comando;
    char lininicial[50], frase[100];
    char *token;

    // utilizando a função readline a strtok para capturar o comando digitado 
    readline(lininicial);
    token = strtok(lininicial, " "); //divide a string em token a partir do espaço
    comando = atoi(token); //tranformando char em int
    //printf("%d \n", comando);
    scanf("%d", &n);
    switch(comando){
        case 1:
            scanf("%d", &n); //qtd registros a serem lidos
            
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