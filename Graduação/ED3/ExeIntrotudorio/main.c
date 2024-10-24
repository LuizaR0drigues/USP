/* --------------------------------------------------
Trabalho introdutorio de Estrutura de Dados 3

Luiza Rodrigues     14593332
Caue Sordi Paulino  14564520

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func_basc.h"

int main()
{
    int  quant, comando, rrn, qtdinfo, Idbusca, *idunico;
    char nomearq[100];
    int quantinsert = 0; 

    scanf("%d", &comando);
    scanf("%s", nomearq);
    
    
    switch (comando)
    {
        case 1:
            scanf("%d", &quant); // número de registros a serem lidos
            int registroValido;

            // Aloca memória para armazenar IDs únicos
            idunico = malloc(quant * sizeof(int));
            if (idunico == NULL) {
                printf("Erro na alocação de memória\n");
                return 0;
            }

            // Abre o arquivo para escrita em modo binário
            FILE *file = fopen(nomearq, "wb");
            if (file == NULL) {
                printf("Falha no processamento do arquivo\n");
                free(idunico);
                return 0;
            }

            int totalInseridos = 0;

            for (int i = 0; i < quant; i++) {
                Registro novoRegistro = RegistrodeEspecies();
                registroValido = 1; // Assume que o registro é válido até prova em contrário

                // Verifica se o ID já está presente
                for (int j = 0; j < totalInseridos; j++) {
                    if (idunico[j] == novoRegistro.especieID) {
                        registroValido = 0;
                        break;
                    }
                }

                // Se o ID for único, armazena o registro
                if (registroValido) {
                    idunico[totalInseridos++] = novoRegistro.especieID;
                    Arquivobin(file, novoRegistro);
                }
            }

            // Libera a memória e fecha o arquivo
            free(idunico);
            fclose(file);
            binarioNaTela(nomearq);
            break;

    case 2:
            // Abre o arquivo para leitura em modo binário
            FILE *arq = fopen(nomearq, "rb");
            if (arq == NULL) {
                printf("Falha no processamento do arquivo\n");
                return 0;
            }

            Registro registroAtual;
            while (1) {
                registroAtual = ArquivodeRegistro(arq);

                // Interrompe o loop se encontrar o final dos registros
                if (registroAtual.especieID == -1) {
                    break;
                }

                // Imprime o registro
                PrintRegistros(registroAtual);
            }

            // Fecha o arquivo
            fclose(arq);
            break;

        
        case 3:
            scanf("%d", &rrn); // Recebe o RRN a ser buscado
            BuscaIndividuo(nomearq, rrn);
            break;
        
        case 4:
            scanf("%d", &Idbusca);         // ID para busca
            scanf("%d", &qtdinfo);          // Quantidade de informações a serem atualizadas
            
            atualizarInformacoes(nomearq, Idbusca, qtdinfo);
            
            break;
        
        default: //comanto neutro
            printf("Comando inválido\n");
            break;
        }

    return 0;
}

/*/ Função readline a strtok para capturar o comando
    readline(lininicial);

    // Captura o primeiro token que contém o comando
    token = strtok(lininicial, " "); // Divide a string em tokens a partir do espaço
    comando = atoi(token);           // token (comando) de char para int

    // Captura o próximo token que é o nome do arquivo
    token = strtok(NULL, " ");
    if (token != NULL) {
        strcpy(nomearq, token);
    }*/
