#ifndef CCOMANDOS_H
    #define COMANDOS_H

#include "registro.h"
#include "cabecalho.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//comandos basicos
void CREATE_TABLE(char *nomeCSV, char *nomearqbin);
void SELECT_TABLE(char *nomearqbin);
#endif