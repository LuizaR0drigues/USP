#ifndef REGISTRO_H
    #define REGISTRO_H
    
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdbool.h>

    #define REGISTRO_SIZE 160
    #define REGISTRO_FILL '$'
    #define REGISTRO_DELIMITADOR '#'

    #define REGISTRO_REMOVIDO_TRUE '1'
    #define REGISTRO_REMOVIDO_FALSE '0'

    // Exemplo de estrutura Registro (ajuste conforme necessário)
    typedef struct {
        int populacao; //4 bytes
        float tamanho; // 4 bytes
        char uniMedida; //1 byte
        int velocidade; //4 bytes
        char *nome;
        char *nEspecie;
        char *habitat;
        char *tipo;
        char *dieta;
        char *alimento;

        char removido; //1 byte
        int encadeamento; //4 bytes
        int tam_preenchimento;

    } Registro;
    

    // Funções de leitura e escrita binária
    Registro *registro_readbin(FILE *file);
    void registro_writebin(FILE *file, Registro *registro);
    Registro *registro_readcsv(FILE *csv);

    // Função para imprimir os dados do registro
    void registro_print(Registro *registro);

    // Verifica se o campo é string ou inteiro
    bool registro_field(char *nome_campo);

    // Remove logicamente um registro
    void registro_remove(Registro *registro);

    // Verifica se o registro é válido (não removido)
    bool registro_isValid(Registro *registro);

    // Funções para obter valores dos campos do registro
    int registro_getPop(Registro *registro);
    float registro_getTam(Registro *registro);
    char registro_getUnimedida(Registro *registro);
    int registro_getVelocidade(Registro *registro);
    char* registro_getNome(Registro *registro);
    char* registro_getNEspecie(Registro *registro);
    char* registro_getHabitat(Registro *registro);
    char* registro_getTipo(Registro *registro);
    char* registro_getDieta(Registro *registro);
    char* registro_getAlimenta(Registro *registro);
    char registro_getRemovido(Registro *registro);
    int registro_getEncadeamento(Registro *registro);

    // Funções para definir valores dos campos do registro
    void registro_setPop(Registro *registro, int pop);
    void registro_setTam(Registro *registro, float tam);
    void registro_setUnimedida(Registro *registro, char unidade);
    void registro_setVelocidade(Registro *registro, int velocidade);
    void registro_setNome(Registro *registro, char *nome);
    void registro_setNEspecie(Registro *registro, char *especie);
    void registro_setHabitat(Registro *registro, char *habitat);
    void registro_setTipo(Registro *registro, char *tipo);
    void registro_setDieta(Registro *registro, char *dieta);
    void registro_setAlimenta(Registro *registro, char *alimento);
    void registro_setRemovido(Registro *registro, bool removido);
    void registro_setEncadeamento(Registro *registro, int encadeamento);

#endif