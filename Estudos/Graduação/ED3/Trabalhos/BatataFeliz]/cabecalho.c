#include "cabecalho.h"

/*
#define CABECALHO_STATUS_OK 1
#define CABECALHO_STATUS_INCON 0
*/
Cabecalho *cabecalho_readbin(FILE *file){
    // lê o cabecalho de um arquivo binário
}
Cabecalho* cabecalho_inicializa()
{
    //estrutura padrão do cabecalho
    Cabecalho *cabecalho  = malloc(sizeof(Cabecalho));
    cabecalho->status = CABECALHO_STATUS_INCON;
    cabecalho->topo = -1;
    cabecalho->proxRRN = 0;
    cabecalho->nroRegRem = 0;
    cabecalho->nroPagDisco = 0;
    cabecalho->qttCompacta = 0;

    return cabecalho;
}

bool cabecalho_getStatus(Cabecalho *cabecalho) {
    // Verifica o valor do campo status
    /*if (cabecalho->status == CABECALHO_STATUS_OK) {
        return true; // Retorna verdadeiro se o status for '1'
    } else {
        return false; // Retorna falso caso contrário
    }*/
   return cabecalho->status == CABECALHO_STATUS_OK;
}

void cabecalho_writebin(FILE *file, Cabecalho *cabecalho) {
    // Escreve o cabeçalho no arquivo binário
    if (!cabecalho_getStatus(cabecalho)) {
        // Se o status não for OK, ajusta para '1'
        cabecalho_setStatus(cabecalho, '1');
    }
    fwrite(&cabecalho->status, sizeof(char), 1, file);
    fwrite(&cabecalho->topo, sizeof(int), 1, file);
    fwrite(&cabecalho->proxRRN, sizeof(int), 1, file);
    fwrite(&cabecalho->nroRegRem, sizeof(int), 1, file);
    fwrite(&cabecalho->nroPagDisco, sizeof(int), 1, file);
    fwrite(&cabecalho->qttCompacta, sizeof(int), 1, file);

    // Preencher o restante da página de disco com o caractere '$'
    int resto = 1600 - (5 * sizeof(int)) - sizeof(char); // Calcula o espaço restante
    char aux[resto];
    for (int i = 0; i < resto; i++) {
        aux[i] = '$'; // Preenche o array com '$'
    }
    fwrite(aux, sizeof(char), resto, file); // Escreve o preenchimento no arquivo
}

void cabecalho_readcsv(FILE *csv) {
    char buffer[300];
    fgets(buffer, sizeof(buffer), csv); // Pula a linha de cabeçalho
}


int cabecalho_getTopo(Cabecalho *cabecalho){
    // verifica o valor do campo topo
    return cabecalho->topo;
}
int cabecalho_getProxRegRem(Cabecalho *cabecalho){
    // verifica o valor do campo proximo a ser removido
    return cabecalho->proxRRN;
}

int cabecalho_getNroPagDisco(Cabecalho *cabecalho){
    // verifica a quantidade de paginas 
    return cabecalho->nroRegRem;
}

int cabecalho_getQttCompacta(Cabecalho *cabecalho){
    // verifica quantas vezes foi compactado
    return cabecalho->qttCompacta;
}

void cabecalho_setStatus(Cabecalho *cabecalho, char status){
    cabecalho->status = status;
}

void cabecalho_setTopo(Cabecalho *cabecalho, int topo){
    cabecalho->topo = topo;
}

void cabecalho_setProxRRN(Cabecalho *cabecalho, int proxRRN){
    cabecalho->proxRRN = proxRRN;
}

void cabecalho_setNroPagDisco(Cabecalho *cabecalho, int nropag){
    cabecalho->nroPagDisco = nropag;
}

void cabecalho_setQttCompacta(Cabecalho *cabecalho, int quant){
    cabecalho->qttCompacta = quant;
}