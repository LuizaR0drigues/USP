#ifndef CABECALHO_H
    #define CABECALHO_H
    
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>

    #define CABECALHO_SIZE 1600
    #define CABECALHO_FILL '$'
    #define CABECALHO_STATUS_OK 1
    #define CABECALHO_STATUS_INCON 0

    typedef struct {
        char status;                // 1 byte
        int topo;               // 4 bytes
        int proxRRN;            // 4 bytes
        int nroRegRem;          // 4 bytes
        int nroPagDisco;        // 4 bytes
        int qttCompacta;        // 4 bytes
    // char padding[1600 - (sizeof(char) + 4 * sizeof(int))];       // Preenche o restante da página de disco com lixo
    } Cabecalho;

    // Funções de leitura e escrita binária
    Cabecalho* cabecalho_inicializa();
    Cabecalho *cabecalho_readbin(FILE *file);
    void cabecalho_verificacao(Cabecalho *cabecalho);
    void cabecalho_writebin(FILE *file, Cabecalho *cabecalho);
    void cabecalho_readcsv(FILE *csv);

    // Funções para obter valores dos campos do cabeçalho
    bool cabecalho_getStatus(Cabecalho *cabecalho);
    int cabecalho_getTopo(Cabecalho *cabecalho);
    int cabecalho_getProxRegRem(Cabecalho *cabecalho);
    int cabecalho_getNroPagDisco(Cabecalho *cabecalho);
    int cabecalho_getQttCompacta(Cabecalho *cabecalho);

    // Funções para definir valores dos campos do cabeçalho
    void cabecalho_setStatus(Cabecalho *cabecalho, bool status);
    void cabecalho_setTopo(Cabecalho *cabecalho, int topo);
    void cabecalho_setProxRRN(Cabecalho *cabecalho, int proxRRN);
    void cabecalho_setNroPagDisco(Cabecalho *cabecalho, int nropag);
    void cabecalho_setQttCompacta(Cabecalho *cabecalho, int quant);
#endif