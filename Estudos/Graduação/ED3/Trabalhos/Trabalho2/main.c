/*
LUIZA RODRIGUES CARDOSO - 14593332
CAUE SORDI PAULINO - 14564520
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "registro.h"
#include "cabecalho.h"
#include "bcabecalho.h"
#include "bregistro.h"
#include "funcoesFornecidas.h"
#include "comandos.h"

int main()
{
    int comando, quant;
    char nomeCSV[100], nomearqbin[100], nomearquivo[15], nomearquivoindice[15], campo[30];
    char *aux, *nomecampo, *valorcampo;

    //alocação de memoria
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
            
            scanf("%s %d", nomearquivo, &quant);// Leitura do nome do arquivo e a quantidade
            for(int i=0; i<quant; i++){
                scanf("%s", nomecampo);

                printf("Busca %d\n",i+1);
                int paginasDisco = SELECT_WHERE(nomearquivo, nomecampo, quant); //chamando a função responsavel por procurar cada
               
            }
            break;
           
        }
        case 7:{
            scanf("%s %s",nomearqbin,nomearquivoindice);
            INSERT_INDICE(nomearqbin, nomearquivoindice, cabecalho);
            binarioNaTela(nomearquivoindice);
            binarioNaTela(nomearqbin);
          break;  
        }

        case 8:{
            
            scanf("%s %s %*s ", nomearqbin, nomearquivoindice);
            char* auxckeys = malloc(160*sizeof(char));
            scan_quote_string(auxckeys);
            long int campoint = converteNome(auxckeys);
            SEARCH_INDICE(nomearqbin, nomearquivoindice, campoint);
        break;
        }
        case 9:
        {
            break;
        }
         default:
                return 0;
    }
    
    
    return 0;
    }