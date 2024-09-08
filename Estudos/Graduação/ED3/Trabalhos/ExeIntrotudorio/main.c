#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func_basc.h"

int main()
{
    int  quant, comando, rrn, qtdinfo, Idbusca, *idunico;
    char lininicial[50], frase[100];
    char *token, nomearq[100];
    int quantinsert = 0; // Inicializa a variável quantinsert

    /*/ Função readline a strtok para capturar o comando
    readline(lininicial);

    // Captura o primeiro token que contém o comando
    token = strtok(lininicial, " "); // Divide a string em tokens a partir do espaço
    comando = atoi(token);           // token (comando) de char para int

    // Captura o próximo token que é o nome do arquivo
    token = strtok(NULL, " ");
    if (token != NULL) {
        strcpy(nomearq, token);
    }
    */
    scanf("%d ", &comando);
    scanf("%s", nomearq);
    switch (comando)
    {
        case 1:
            
            scanf("%d", &quant); // qtd registros a serem lidos
            int flag = 1;

            idunico = malloc(quant * sizeof(int));
            if(idunico == NULL)
            {
                printf("Falha de alocação de memoria\n");
                return 0;
            }

            FILE *file = fopen(nomearq, "wb");
            if (file == NULL) {
                printf("Falha no processamento do arquivo\n");
                free(idunico);
                return 0;
            }

            for (int i = 0; i < quant; i++)
            {
                Registro animais = RegistrodeEspecies();
                
                flag = 1; // Reinicia a flag para cada novo registro
                for (int j = 0; j < quantinsert; j++)
                {
                    if (idunico[j] == animais.especieID)
                    {
                        flag = 0;
                        break;
                    }
                }

                if (flag)
                {
                    idunico[quantinsert] = animais.especieID;
                    quantinsert++;

                    Arquivobin(file, animais);
                }
                freememoria(&animais);
            }
            
            free(idunico);
            fclose(file); // Corrigido para fechar o arquivo corretamente
            binarioNaTela(nomearq);
            break;
        
        case 2:
            //printf("%s\n", nomearq);
            FILE* arq; // Abre o arquivo para leitura binária
            if (nomearq == NULL || !(arq=fopen(nomearq, "rb"))) {
                printf("Falha no processamento do arquivo\n");
                return 0;
            }

            Registro especie;
            while (1) {
                especie = ArquivodeRegistro(arq);

                // Verifica se o ID indica fim de arquivo ou erro
                if (especie.especieID == -1) {
                    break; // Sai do loop se não houver mais registros
                }

                PrintRegistros(especie); // Função para imprimir os registros
            }

            fclose(arq); // Fecha o arquivo após a leitura
        break;

        
        case 3:
            scanf("%d", &rrn);
            BuscaIndividuo(nomearq, rrn);
            break;
        
        case 4:
            scanf("%d", &Idbusca);
            scanf("%d", &qtdinfo);
            atualizarInformacoes(nomearq, Idbusca, qtdinfo);
            break;
        
        default:
            printf("Comando inválido\n");
            break;
        }

    return 0;
}
