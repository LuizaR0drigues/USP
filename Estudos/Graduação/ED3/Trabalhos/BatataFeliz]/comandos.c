#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "registro.h"
#include "cabecalho.h"


/*
#define CABECALHO_STATUS_OK 1
#define CABECALHO_STATUS_INCON 0
*/
void CREATE_TABLE(char *nomeCSV, char *nomearqbin, Cabecalho *cabecalho){
    // ler o arquivo csv (cria a página)
    //abertura do arquivo csv para leitur
    int qtt =0;
            FILE *arquivo_csv = fopen(nomeCSV, "r");
            if (arquivo_csv == NULL) {
                printf("Falha ao abrir o arquivo \n");
                return ;
            }
            FILE *arquivo_binario = fopen(nomearqbin, "wb");
            if (arquivo_binario == NULL) {
                printf("Falha ao abrir o arquivo binário.\n");
                return ;
            }

            //nome das colunas
            cabecalho_readcsv(arquivo_csv);


            //escrita
            cabecalho_writebin(arquivo_binario,cabecalho);
            //printf("Status: %c\n", cabecalho->status);
            while (!feof(arquivo_csv)) { //salva todos os dados em dino
                Registro *dino = registro_readcsv(arquivo_csv);

                // Verifica se leu corretamente o registro
                if (dino == NULL) {
                    printf("Erro ao ler o registro do CSV\n");
                    break;
                }
                
                // Exibir as informações do registro lido
                //registro_print(dino);
                registro_setEncadeamento(dino, -1);
                //escreve no arquivo binario
                registro_writebin(arquivo_binario, dino);

                //qtt de registros
                qtt++;
                // Liberar a memória alocada para o registro
                //free(dino->nome);
            }
            
            // Verificação do cabeçalho
            cabecalho_getStatus(cabecalho);
            
            
            //calculo da quantidade de paginas de disco         
            int total = qtt * 160; //qtt de registro * numero de bytes
            total = (total/1600) ; //quantidade de bytes / numeros de butes que equivale uma pagina + 1 pagina do cabelaho
            int aux = round(total) +2;
            cabecalho_setNroPagDisco(cabecalho, aux);//atualizando o valor de nro de paginas de disco
            cabecalho_setProxRRN(cabecalho, qtt); //proximo rrn
            fseek(arquivo_binario, 0, SEEK_SET);
            // Escreve o cabeçalho no arquivo binário
            cabecalho_writebin(arquivo_binario, cabecalho);

            // chamada pra função de criar a tabela
            fclose(arquivo_csv);
            fclose(arquivo_binario);
}   

void SELECT_TABLE(char *nomearqbin) {
    FILE *arquivo_binario = fopen(nomearqbin, "rb");
    if (arquivo_binario == NULL) {
        printf("Falha ao abrir o arquivo \n");
        return;
    }

    Registro registro;  // Estrutura para armazenar um registro

    // Lê registros do arquivo binário
    while (1) {
        Registro *dino = registro_readbin(arquivo_binario);
        
        // Verifica se a leitura foi bem-sucedida
        if (dino == NULL) {
            break;  // Sai do loop se não houver mais registros para ler
        }
        
        registro_print(dino);  // Imprime o registro lido
    }

    fclose(arquivo_binario); 
}