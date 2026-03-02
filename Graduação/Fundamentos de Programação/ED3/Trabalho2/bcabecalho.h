#ifndef BCABECALHO_H
    #define BCABECALHO_H
    
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>

    #define BCABECALHO_SIZE 93
    #define CABECALHO_FILL '$'
    #define CABECALHO_STATUS_OK 1
    #define CABECALHO_STATUS_INCON 0

    typedef struct {
        char status;                // 1 byte
        int noRaiz;               // 4 bytes
        int proxRRNno;            // 4 bytes
    // char padding[1600 - (sizeof(char) + 4 * sizeof(int))];       // Preenche o restante da página de disco com lixo
    } CabecalhoArvore;

    // Funções de leitura e escrita binária
    CabecalhoArvore* bcabecalho_inicializa();
    CabecalhoArvore* bcabecalho_readbin(FILE *file);
    //void cabecalho_verificacao(CabecalhoArvore *cabecalho);
    void bcabecalho_writebin(FILE *file, CabecalhoArvore *cabecalho);
    void bcabecalho_readcsv(FILE *csv);

    // Funções para obter valores dos campos do cabeçalho
    bool bcabecalho_getStatus(CabecalhoArvore *cabecalho);
    int bcabecalho_getNoRaiz(CabecalhoArvore *cabecalho);

    // Funções para definir valores dos campos do cabeçalho
    void bcabecalho_setStatus(CabecalhoArvore *cabecalho, char status);
    void bcabecalho_setNoRaiz(CabecalhoArvore *cabecalho, int topo);
    void bcabecalho_setproxRRNno(CabecalhoArvore *cabecalho, int proxRRNno);
    
#endif