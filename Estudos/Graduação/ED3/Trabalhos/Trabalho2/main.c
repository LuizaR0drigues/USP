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
            //binarioNaTela(nomearquivoindice);
          break;  
        }

        case 8:{
            
            scanf("%s %s %*s %s",nomearqbin, nomearquivoindice, campo);
            long int campoint = converteNome(campo);
            //RECUPERACAO_INDICE(nomearqbin, nomearquivoindice, campoint);
        break;
        }
         default:
                return 0;
    }/*

    FILE *batata = fopen("batata.bin","wb+");

    int rrn_raiz = 0;
    NoArvore *raiz = no_criar(true,0);
    no_print(raiz);
    for(int i=0;i<4;i++){
        CPR inserir;inserir.C = i*i;inserir.PR=i*4+i*i;
        printf("Inserindo: C=%d PR=%d\n",inserir.C,inserir.PR);
        PCPR retorno = no_inserir_recursivo(batata,raiz,inserir,rrn_raiz);
        printf("Resultado: ");no_print(raiz);printf("    PCPR: (%ld %ld) %d",retorno.corpo.C,retorno.corpo.PR,retorno.P);
        printf("\n\n");
    }


    CPR inserir;inserir.C = 6;inserir.PR=1231;
    printf("Inserindo: C=%d PR=%d\n",inserir.C,inserir.PR);
    
    PCPR retorno = no_inserir_recursivo(batata,raiz,inserir,rrn_raiz);
    // printf("   >> Deu overflow: %d\n",retorno);
    printf("Resultado: ");no_print(raiz);printf("    PCPR: (%ld %ld) %d",retorno.corpo.C,retorno.corpo.PR,retorno.P);
    printf("\n\n\n\n Todos os registros: \n");
    for(int rrn=0;rrn<2;rrn++){
        NoArvore *no = no_readbin(batata,rrn);
        printf("RRN = %d | ",rrn);no_print(no);
    }*/
    return 0;
    }