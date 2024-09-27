#ifndef CCOMANDOS_H
    #define COMANDOS_H

#include "registro.h"
#include "cabecalho.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


//comandos basicos
void CREATE_TABLE(char *nomeCSV, char *nomearqbin, Cabecalho *c);
void SELECT_TABLE(char *nomearqbin);
void SELECT_WHERE(char *nome, char *campo, char *valor);
#endif