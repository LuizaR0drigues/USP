#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "registro.h"
#include "cabecalho.h"
#include "funcoesFornecidas.h"
#include "comandos.h"

int main()
{
     int comando;
    char nomeCSV[100], nomearqbin[100];
    char *aux;
    aux = malloc(100*sizeof(char));
    scanf("%d%*c",&comando);

    //estrutura padrão do cabecalho
    Cabecalho *cabecalho = cabecalho_inicializa();
    switch(comando){
         case 1: //CREATE TABLE
            scanf("%s %s",nomeCSV,nomearqbin);
            //chamando o comando create table
            CREATE_TABLE(nomeCSV, nomearqbin, cabecalho);
            binarioNaTela(nomearqbin);
            
            break;
        case 2:
            scanf("%s", aux);
            SELECT_TABLE(aux);
            break;
        case 3:
            break;
    }
    //     default:
    //         printf("Comando desconhecido\n");
    //         exit(1);
    // }
    free(aux);
    
    return 0;
    }