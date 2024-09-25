#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "registro.h"
#include "cabecalho.h"
#include "funcoesFornecidas.h"

int main()
{
     int comando;
    char nomeCSV[100], nomearqbin[100];
    
    scanf("%d%*c",&comando);
    switch(comando){
         case 1: //CREATE TABLE
            scanf("%s %s",nomeCSV,nomearqbin);
            //abertura do arquivo csv para leitur
            FILE *arquivo_csv = fopen(nomeCSV, "r");
            if (arquivo_csv == NULL) {
                printf("Falha ao abrir o arquivo \n");
                return 0;
            }
            FILE *arquivo_binario = fopen(nomearqbin, "wb");
            if (arquivo_binario == NULL) {
                printf("Falha ao abrir o arquivo binário.\n");
                return 0;
            }

            //nome das colunas
            cabecalho_readcsv(arquivo_csv);

            while (!feof(arquivo_csv)) { //salva todos os dados em dino
                Registro *dino = registro_readcsv(arquivo_csv);
                
                // Verifica se leu corretamente o registro
                if (dino == NULL) {
                    printf("Erro ao ler o registro do CSV\n");
                    break;
                }
                
                // Exibir as informações do registro lido
                //registro_print(dino);

                //escreve no arquivo binario
                registro_writebin(arquivo_binario, dino);
                // Liberar a memória alocada para o registro
                free(dino->nome);
                free(dino->dieta);
                free(dino->habitat);
                free(dino->tipo);
                free(dino->nEspecie);
                free(dino->alimento);
                free(dino);
            }
            
            // chamada pra função de criar a tabela
            fclose(arquivo_csv);
            fclose(arquivo_binario);
            
            binarioNaTela(nomearqbin);
            
            
            
            
            break;
    }
    //     default:
    //         printf("Comando desconhecido\n");
    //         exit(1);
    // }
/*
    char nomeCSV[] = "dados1.csv";
    char nomearqbin[]= "binario1.bin";
    
    FILE *arquivo_csv = fopen(nomeCSV, "r");
        if (arquivo_csv == NULL) {
            printf("Falha ao abrir o arquivo CSV\n");
            return 0;
        }
    while (!feof(arquivo_csv)) {
        Registro *dino = registro_readcsv(arquivo_csv);
        
        // Verifica se leu corretamente o registro
        if (dino == NULL) {
            printf("Erro ao ler o registro do CSV\n");
            break;
        }
        
        // Exibir as informações do registro lido
        registro_print(dino);

        // Liberar a memória alocada para o registro
        free(dino->nome);
        free(dino->dieta);
        free(dino->habitat);
        free(dino->tipo);
        free(dino->nEspecie);
        free(dino->alimento);
        free(dino);
    }
*/
    // Fechar o arquivo CSV após processar tudo

    return 0;
    }