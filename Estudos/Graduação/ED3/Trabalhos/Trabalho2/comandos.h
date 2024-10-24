#ifndef CCOMANDOS_H
    #define COMANDOS_H

#include "registro.h"
#include "cabecalho.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


//comandos basicos - arquivo de dados
void CREATE_TABLE(char *nomeCSV, char *nomearqbin, Cabecalho *c);
void SELECT_TABLE(char *nomearqbin);
int SELECT_WHERE(char *nome, char *campo, int n);

//comandos basicos - Árvore - B
int INSERT_INDICE(char *binario, char *indice, Cabecalho *c);
void SEARCH_INDICE(char *binario, char *indice, long int campo);

#endif