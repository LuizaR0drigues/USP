#include <stdio.h>
#include <stdlib.h>
#include "registro.h"
#include "cabecalho.h"

void CREATE_TABLE(char *nomeCSV, char *nomearqbin){
    // ler o arquivo csv (cria a página)
    //abertura do arquivo csv para leitur
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

            //estrutura padrão do cabecalho
            Cabecalho *cabecalho = cabecalho_inicializa();

            //escrita
            cabecalho_writebin(arquivo_binario,cabecalho);

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
            
            // Verificação do cabeçalho
            cabecalho_getStatus(cabecalho);

            // Escreve o cabeçalho no arquivo binário
            cabecalho_writebin(arquivo_binario, cabecalho);

            // chamada pra função de criar a tabela
            fclose(arquivo_csv);
            fclose(arquivo_binario);
}   

void SELECT_TABLE(char *nomearqbin) {
    printf("%s\n", nomearqbin);
    printf("Teste\n");
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