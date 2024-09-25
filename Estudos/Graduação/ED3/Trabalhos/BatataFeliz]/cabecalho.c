#include "cabecalho.h"


Cabecalho *cabecalho_readbin(FILE *file){
    // lê o cabecalho de um arquivo binário
}

void cabecalho_writebin(FILE *file, Cabecalho *cabecalho){
    // escreve o cabecalho no arquivo binário

}

void cabecalho_readcsv(FILE *csv){
    char buffer[300];
    fgets(buffer, sizeof(buffer), csv); // Pula a linha de cabeçalho
}

bool cabecalho_getStatus(Cabecalho *cabecalho){
    // verifica o valor do campos status
    if(cabecalho->status == CABECALHO_STATUS_OK){
        return true;
    }
    else{
        return false;
    }
    
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

void cabecalho_setStatus(Cabecalho *cabecalho, bool status){
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