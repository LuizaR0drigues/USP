#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bcabecalho.h"
#include "bregistro.h"
#include "registro.h"
#include "cabecalho.h"
#include "funcoesFornecidas.h"

 #define PAGINA_TAMANHO 1600

FILE* abertura_arqBin(char *nome, char *tipo)
{
    FILE *arquivo = fopen(nome,tipo);
    if (arquivo == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return NULL; // Retorna 0 se não conseguiu abrir o arquivo
    }
    return arquivo;
}

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
            
            while (!feof(arquivo_csv)) { //salva todos os dados em dino
                Registro *registro = registro_readcsv(arquivo_csv);

                // Verifica se leu corretamente o registro
                if (registro == NULL) {
                    printf("Erro ao ler o registro do CSV\n");
                    break;
                }
                
                // Exibir as informações do registro lido
                //registro_print(registro);
                registro_setEncadeamento(registro, -1);
                //escreve no arquivo binario
                registro_writebin(arquivo_binario, registro);

                //qtt de registros
                qtt++;
                // Liberar a memória alocada para o registro
                //free(registro->nome);
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

//função que busca registros pelo campo e valor
int SELECT_WHERE(char *nomearquivo, char *campo, int quant) {
    FILE *arquivo_binario = fopen(nomearquivo, "rb");
    if (arquivo_binario == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return 0; // Retorna 0 se não conseguiu abrir o arquivo
    }

    Cabecalho *cabecalho = cabecalho_readbin(arquivo_binario);
    if (cabecalho == NULL) {
        printf("Falha ao ler o cabeçalho do arquivo.\n");
        fclose(arquivo_binario);
        return 0;
    }

    Registro *registro ;
    fseek(arquivo_binario,1600, SEEK_SET); // Setando a leitura para a primeira página de dados

    int cont_registro = 0;
    int teste = verificacaoString(campo); // Verifica o tipo do campo

    // Verificação do tipo da variável que deve-se buscar no arquivo binário
    if (teste == -1) {
        printf("Campo inválido.\n");
        free(cabecalho);
        fclose(arquivo_binario);
        return 0; // Campo inválido
    }

    // Leitura do valor a ser buscado
    char valorString[100];
    int valorInt = -1;
    float valorFloat = -1.0f;
   
    if (teste <= 5) {
        scan_quote_string(valorString); // Leitura de valor string
    } else if (teste <= 7) {
        scanf("%d", &valorInt); // Leitura de valor int
    } else if (teste == 8) {
        scanf("%f", &valorFloat); // Leitura de valor float
    }

    // Itera sobre todos os registros até o final do arquivo
    // Itera sobre todos os registros até o final do arquivo
    while (!feof(arquivo_binario)) {
       registro = registro_readbin(arquivo_binario);
        if (registro_isValid(registro)) {
            // Verifica se o registro corresponde ao valor buscado
            if (teste <= 5) {
                registro_busca_elemento(valorString, -1, -1.0f, registro);
                    
                
            } else if (teste <= 7) {
                registro_busca_elemento(NULL, valorInt, -1.0f, registro) ;
                    
                
            } else if (teste == 8) {
                registro_busca_elemento(NULL, -1, valorFloat, registro) ;
                   
            }
        }
      
        free(registro); // Libera a memória do registro lido
        cont_registro++;
    }
    
    printf("Numero de paginas de disco: %d\n\n", cabecalho->nroPagDisco);
    free(cabecalho); // Libera o cabeçalho lido
    
    fclose(arquivo_binario); // Fecha o arquivo binário
    return 0;
}

int INSERT_INDICE(char *binario, char *indice)
{
   FILE *arquivo_binario = fopen(binario, "rb");
    if (arquivo_binario == NULL) {
        printf("Falha ao abrir o arquivo \n");
        return 0;
    }
     FILE *arquivo_indice = fopen(indice, "wb");
    if (arquivo_indice== NULL) {
        printf("Falha ao abrir o arquivo \n");
        return 0;
    }
    
    //estruturas do arquivos de dados
    Registro *registro;  // Estrutura para armazenar um registro
    Cabecalho *cabecalho = cabecalho_readbin(arquivo_binario);

    //cabecalho da arvore b
    CabecalhoArvore *bcabecalho = bcabecalho_inicializa();
    bcabecalho_writebin(arquivo_indice, bcabecalho);
    
    fseek (arquivo_binario, 1600, SEEK_SET);
    // Lê registros do arquivo binário
    int cont_registro=0;
    while (1) {
        
        //lendo o arquivo binario
        registro = registro_readbin(arquivo_binario);

        cont_registro++;
        // printf("Registro lido -----------------------------\n");
        //verificação de integridade
        if ( registro == NULL || registro->removido == 'E') {
            break;  // Sai do loop se não houver mais registros para ler
        }
        
        if(registro_isValid(registro)==false){ //no positivo, colocamos o ponteiro do disco logo apos o cabecalho
            fseek (arquivo_binario, 1600+REGISTRO_SIZE*(cont_registro), SEEK_SET);
            continue;
        }

        //tranformado string -> long int
        long int campo = converteNome(registro->nome);
        CPR valor;
        valor.C = campo;
        valor.PR = 16000+ (160 *cont_registro); //calculo do byetoffset
        printf("-----------------------------------------------------------------------\n");
        printf("\nNome: %s %lu %d\n", registro->nome, campo, valor.PR);
        
        NoArvore *raiz = no_criar(true,0);
        raiz->RRNdoNo = 0;
        bcabecalho->noRaiz = 0;
        
        PCPR retorno = no_inserir_recursivo(arquivo_indice, raiz, valor, bcabecalho,0);
        printf("\n Valores inseridos %lu %d\n", retorno.corpo.C, retorno.corpo.PR);

        // for (int i = 0; i < 4; i++) {
        //     campo = converteNome(registro->nome);
        //     valor.C = campo;
        //     valor.PR = 1600 + (160 * i); // Calculo do byteoffset com base no índice
        //     printf("Inserindo: Nome=%s C=%lu PR=%d\n", registro->nome, campo, valor.PR);
            
        //     retorno = no_inserir_recursivo(arquivo_indice, raiz, valor, bcabecalho, 0);
        //     printf("Resultado: ");
        //     no_print(raiz);
        //     printf("    PCPR: (%ld %d) %d", retorno.corpo.C, retorno.corpo.PR, retorno.P);
        //     printf("\n\n");
        // }

        // Lê todos os registros e imprime
        printf("\nTodos os registros [%d]:\n",bcabecalho->proxRRNno);
        for (int rrn = 0; rrn < bcabecalho->proxRRNno; rrn++) {
            NoArvore *no = no_readbin(arquivo_indice, rrn);
            printf("RRN = %d | ", rrn);
            no_print(no);
        }
        printf("\n\n\n");
    }

    //modificando o cabeçalho e reescrevendo as novas informações
    bcabecalho_getStatus(bcabecalho);
    bcabecalho_setproxRRNno(bcabecalho, cont_registro);
    fseek(arquivo_indice, 0, SEEK_SET); //posicionado o ponteiro no inicio novamente
    bcabecalho_writebin(arquivo_indice, bcabecalho);

    
    free(registro);
    free(cabecalho);
    fclose(arquivo_binario); 
    fclose(arquivo_indice);
    return 0;
}

void SEARCH_INDICE(char *indice, long int campo)
{

}



