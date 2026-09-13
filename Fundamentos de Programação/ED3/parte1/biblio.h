#ifndef BIBLIO_H
#define BIBLIO_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//definindo a struct cabecalho
//POssui 17 bytes, status(1), topo(4), prox(4), nroRem(4), nroPares(4)
struct Cabecalho {
    char status; 
    int topoPiplha;
    int proxRNN;
    int nroRegRem;
    int nroPares;
};

//struct Registro de Dados
struct Registro{
    int idPoPs;
    int idPoPsConectado;
    char unidadeMed;
    char removido;
    int encadPilha;
};

#endif