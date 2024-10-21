#include "bcabecalho.h"

/*
#define CABECALHO_STATUS_OK 1
#define CABECALHO_STATUS_INCON 0
*/
#define TAMPAGE 93

CabecalhoArvore* bcabecalho_inicializa()
{
    //estrutura padrão do cabecalho
    CabecalhoArvore *cabecalho  = malloc(sizeof(CabecalhoArvore));
    cabecalho->status = CABECALHO_STATUS_INCON;
    cabecalho->noRaiz = -1;
    cabecalho->proxRRNno = 0;
   
    return cabecalho;
}

// Função para ler o cabeçalho do arquivo binário
CabecalhoArvore* bcabecalho_readbin(FILE *entrada) {
    CabecalhoArvore *cabecalho = bcabecalho_inicializa();
    
    // Leitura do status do cabeçalho
    if (!fread(&cabecalho->status, sizeof(char), 1, entrada)) {
        cabecalho->status = 'E'; // Indica erro de leitura
        return cabecalho;
    }

    // Leitura dos campos de tamanho fixo do cabeçalho
    fread(&cabecalho->noRaiz, sizeof(int), 1, entrada);
    fread(&cabecalho->proxRRNno, sizeof(int), 1, entrada);
    
    return cabecalho;
}
bool bcabecalho_getStatus(CabecalhoArvore *cabecalho) {
    // Verifica o valor do campo status
    /*if (cabecalho->status == CABECALHO_STATUS_OK) {
        return true; // Retorna verdadeiro se o status for '1'
    } else {
        return false; // Retorna falso caso contrário
    }*/
   return cabecalho->status == CABECALHO_STATUS_OK;
}

void bcabecalho_writebin(FILE *file, CabecalhoArvore *cabecalho) {
    // Escreve o cabeçalho no arquivo binário
    if (!bcabecalho_getStatus(cabecalho)) {
        // Se o status não for OK, ajusta para '1'
        bcabecalho_setStatus(cabecalho, '1');
    }
    fwrite(&cabecalho->status, sizeof(char), 1, file);
    fwrite(&cabecalho->noRaiz, sizeof(int), 1, file);
    fwrite(&cabecalho->proxRRNno, sizeof(int), 1, file);
   

    

    // Preencher o restante da página de disco com o caractere '$'
    int resto = TAMPAGE - (2 * sizeof(int)) + sizeof(char); // Calcula o espaço restante
    char aux[resto];
    for (int i = 0; i < resto; i++) {
        aux[i] = '$'; // Preenche o array com '$'
    }
    fwrite(aux, sizeof(char), resto, file); // Escreve o preenchimento no arquivo
}

void bcabecalho_readcsv(FILE *csv) {
    char buffer[300];
    fgets(buffer, sizeof(buffer), csv); // Pula a linha de cabeçalho
    
}


int bcabecalho_getNoRaiz(CabecalhoArvore *cabecalho){
    // verifica o valor do campo NoRaiz
    return cabecalho->noRaiz;
}

void bcabecalho_setStatus(CabecalhoArvore *cabecalho, char status){
    cabecalho->status = status;
}

void bcabecalho_setNoRaiz(CabecalhoArvore *cabecalho, int NoRaiz){
    cabecalho->noRaiz = NoRaiz;
}

void bcabecalho_setproxRRNno(CabecalhoArvore *cabecalho, int proxRRNno){
    cabecalho->proxRRNno = proxRRNno;
}
