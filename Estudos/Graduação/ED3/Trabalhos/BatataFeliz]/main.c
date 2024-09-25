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
    
    scanf("%d%*c",&comando);
    switch(comando){
         case 1: //CREATE TABLE
            scanf("%s %s",nomeCSV,nomearqbin);
            //chamando o comando create table
            CREATE_TABLE(nomeCSV, nomearqbin);
            binarioNaTela(nomearqbin);
            
            break;
    }
    //     default:
    //         printf("Comando desconhecido\n");
    //         exit(1);
    // }
        
    
    return 0;
    }