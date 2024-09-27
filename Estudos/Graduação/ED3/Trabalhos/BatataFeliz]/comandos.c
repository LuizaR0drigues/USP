#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "registro.h"
#include "cabecalho.h"
#include "funcoesFornecidas.h"

 #define PAGINA_TAMANHO 1600
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

    Registro *registro;  // Estrutura para armazenar um registro

    Cabecalho *cabecalho = cabecalho_readbin(arquivo_binario);
    fseek (arquivo_binario, 1600, SEEK_SET);
    // Lê registros do arquivo binário
    int cont_registro=0;
    while (1) {
        
        //sabemos que ele morre no while, mas passa uma vez so aqui
        registro = registro_readbin(arquivo_binario);
        cont_registro++;

        //ele nao passa do primeiro registro_readbin (local do problema )
        // Verifica se a lei/sabemo que o arquivo abretura foi bem-sucedida
        if (registro->removido == 'E') {
            break;  // Sai do loop se não houver mais registros para ler
        }
        if(registro_isValid(registro)==false){
            fseek (arquivo_binario, 1600+REGISTRO_SIZE*(cont_registro), SEEK_SET);
            continue;
        }
        
        registro_print(registro);  // Imprime o registro lido
    }
    printf("Numero de paginas de disco: %d\n", cabecalho->nroPagDisco);
    printf("\n");
    free(registro);
    free(cabecalho);
    fclose(arquivo_binario); 
}

int SELECT_WHERE(char *nome, char *campo) {
    FILE *arquivo_binario = fopen(nome, "rb");
    if (arquivo_binario == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return 0; // Retorna 0 se não conseguiu abrir o arquivo
    }

    Registro *registro;
    Cabecalho *cabecalho = cabecalho_readbin(arquivo_binario); // leitura do cabeçalho do arquivo
    fseek(arquivo_binario, 1600, SEEK_SET); // setando a leitura

    int nroPagDisco = cabecalho->nroPagDisco;
    int found = 0; // Indicador para verificar se algum registro foi encontrado
    int cont_registro = 0;

    while (1) {
        registro = registro_readbin(arquivo_binario);
        if (registro == NULL) {
            break; // Sai do loop se não houver mais registros
        }
        if (registro_isValid(registro) == false) {
            fseek(arquivo_binario, 1600 + REGISTRO_SIZE * (cont_registro), SEEK_SET);
            free(registro); // Libera memória do registro lido antes de continuar
            cont_registro++;
            continue;
        }

        // Verificação do tipo da variável que deve-se buscar no arquivo binário
        int teste = verificacaoString(campo);
        if (teste == 0 || teste == 1 || teste == 2 || teste == 3 || teste == 4 || teste == 5) {
            char valor[100];
            scan_quote_string(valor); // Leitura para o caso de string
            registro_busca_elemento(valor, -1, -1.0f, registro);
        } else if (teste == 6 || teste == 7) {
            int valorint;
            scanf("%d", &valorint); // Leitura para o caso de inteiro
            registro_busca_elemento(NULL, valorint, -1.0f, registro);
        } else if (teste == 8) {
            float valorf;
            scanf("%f", &valorf); // Leitura para o caso de float
            registro_busca_elemento(NULL, -1, valorf, registro);
        } else if (teste == -1) { // Campo inválido
            free(registro);
            break;
        }

        free(registro); // Libera memória do registro lido
        cont_registro++;
    }

    free(cabecalho);
    fclose(arquivo_binario);

    return nroPagDisco;
}