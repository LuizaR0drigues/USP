#include <stdio.h>
#include <stdlib.h>
#include "func.h"
#include <string.h>

int main() {
    
    int comando, rrn, Idbusca;
    char nomeCSV[100], nomearqbin[100];
    Registro registro;
    
    // Cabecalho
    Cabecalho cabecalho;
    cabecalho.status = '0';
    cabecalho.topo = -1;
    cabecalho.proxRRN = 0;
    cabecalho.nroRegRem = 0;
    cabecalho.nroPagDisco = 0;
    cabecalho.qttCompacta = 0;

    // Leitura dos parâmetros de arquivos
    scanf("%d", &comando);
    
    

    switch (comando)
    {
    case 1:
        scanf("%s", nomeCSV);
        scanf("%s", nomearqbin);

        // Abre o arquivo binário para leitura e escrita 
        FILE *arquivo_binario = fopen(nomearqbin, "wb");
        if (arquivo_binario == NULL) {
            printf("Falha ao abrir o arquivo binário.\n");
            return 1;
        }
        // Inicializa o cabeçalho
        escreve_cabecalho(cabecalho, arquivo_binario);
        Cabecalho test2 = leitura_cabecalho(cabecalho, arquivo_binario);
        printf("S2: %c\n", test2.status);

        //leitura do arquivo csv
        lendo_csv(nomeCSV, arquivo_binario, cabecalho, registro);
        binarioNaTela(nomearqbin);

        //atualizo o valor de cabecalho e escrevo novamente
        cabecalho.status = '1';
        escreve_cabecalho(cabecalho, arquivo_binario);
        Cabecalho teste = leitura_cabecalho(cabecalho, arquivo_binario);
        printf("ST: %c\n", teste.status);


        fclose(arquivo_binario);
        break;
    case 2:
        //leitura do arquvio binario
        scanf("%s", nomearqbin);
        // Chama a função para recuperar e mostrar os registros
        recuperar_todos_os_registros(nomearqbin);
        break;
            
    default:
        break;
    }
    


    
    return 0;
}
