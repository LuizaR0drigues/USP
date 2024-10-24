#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "registro.h"
#include "cabecalho.h"
#include "funcoesFornecidas.h"
#include "comandos.h"

int main()
{
     int comando, quant;
    char nomeCSV[100], nomearqbin[100];
    char *aux, *nomecampo, *valorcampo;
    aux = malloc(100*sizeof(char));
    nomecampo = malloc(100*sizeof(char));
    valorcampo = malloc(100*sizeof(char));
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
         case 3: {
            int quant = 0;
            char nomearquivo[15];
            int paginasDisco=0;
            scanf("%s %d", nomearquivo, &quant); // Leitura do nome do arquivo e a quantidade
            for(int i=0; i<quant; i++){
                scanf("%s", nomecampo);

                printf("Busca %d\n",i+1);
                paginasDisco = SELECT_WHERE(nomearquivo, nomecampo, quant);
            }
            printf("Numero de paginas de disco: %d\n\n", paginasDisco);
            break;
           
        }
         default:
                return 0;
    }
            
    return 0;
    }