#include "registro.h"
#include "cabecalho.h"


Registro *registro_readbin(FILE* entrada) { 
      Registro *registro = cria_registro();

    if (!fread(&registro->removido, sizeof(char), 1, entrada)) {
        registro->removido = 'E'; // Indica que não foi possível ler o registro

        return registro;
    }

    if (registro->removido == '1') {
        return registro;
    }
 //freads para os campos de tamanho fixo
    fread(&registro->encadeamento, sizeof(int), 1, entrada);
    fread(&registro->populacao, sizeof(int), 1, entrada);
    fread(&registro->tamanho, sizeof(float), 1, entrada);
    fread(&registro->uniMedida, sizeof(char), 1, entrada);
    fread(&registro->velocidade, sizeof(int), 1, entrada);
// char*linha = calloc (160, sizeof(char)); para alocar memoria
    char* linha = calloc(160, sizeof(char));
    fgets(linha, 161 - sizeof(int) * 4 - sizeof(char) * 2, entrada); // lê o restante da linha

    strcpy (registro->nome , strsep(&linha, "#")); // strtok para separar os campos e delimitador
    strcpy (registro->nEspecie , strsep(&linha, "#"));
    strcpy (registro->habitat , strsep(&linha, "#"));
    strcpy (registro->tipo , strsep(&linha, "#"));
    strcpy (registro->dieta , strsep(&linha, "#"));
    strcpy (registro->alimento , strsep(&linha, "#"));

    //free(linha);
    
    return registro;
}

Registro* cria_registro ()
{
    Registro *registro  = malloc(sizeof(Registro));
    registro -> removido = '0';
    registro -> encadeamento = -1;
    registro -> populacao = -1;
    registro -> tamanho = -1;
    registro -> uniMedida = '$';
    registro -> velocidade = -1;
    registro -> nome = calloc (160, sizeof(char));
    registro -> nEspecie = calloc (160, sizeof(char));
    registro -> habitat = calloc (160, sizeof(char));
    registro -> tipo = calloc (160, sizeof(char));
    registro -> dieta = calloc (160, sizeof(char));
    registro -> alimento = calloc (160, sizeof(char));

    return registro;

}

void registro_writebin(FILE *nomebin, Registro *registro) {
    // Função para escrever o registro no arquivo binário

    // Obter o tamanho das strings de tamanho variável
    int tam = strlen(registro->nome);
    int tamA = strlen(registro->alimento);
    int tamD = strlen(registro->dieta);
    int tamE = strlen(registro->nEspecie);
    int tamT = strlen(registro->tipo);
    int tamH = strlen(registro->habitat);

    // Escreve campos de tamanho fixo
    fwrite(&registro->removido, sizeof(char), 1, nomebin);
    fwrite(&registro->encadeamento, sizeof(int), 1, nomebin);
    fwrite(&registro->populacao, sizeof(int), 1, nomebin);
    fwrite(&registro->tamanho, sizeof(float), 1, nomebin);
    fwrite(&registro->uniMedida, sizeof(char), 1, nomebin);
    fwrite(&registro->velocidade, sizeof(int), 1, nomebin);

    // Escreve campos de tamanho variável com delimitador #
    if (registro->nome != NULL && strcmp(registro->nome, "#") != 0) {
        fwrite(registro->nome, sizeof(char), tam, nomebin);
    }
    fwrite("#", sizeof(char), 1, nomebin);  // Delimitador

    if (registro->nEspecie != NULL && strcmp(registro->nEspecie, "#") != 0) {
        fwrite(registro->nEspecie, sizeof(char), tamE, nomebin);
    }
    fwrite("#", sizeof(char), 1, nomebin);  // Delimitador

    if (registro->habitat != NULL && strcmp(registro->habitat, "#") != 0) {
        fwrite(registro->habitat, sizeof(char), tamH, nomebin);
    }
    fwrite("#", sizeof(char), 1, nomebin);  // Delimitador

    if (registro->tipo != NULL && strcmp(registro->tipo, "#") != 0) {
        fwrite(registro->tipo, sizeof(char), tamT, nomebin);
    }
    fwrite("#", sizeof(char), 1, nomebin);  // Delimitador

    if (registro->dieta != NULL && strcmp(registro->dieta, "#") != 0) {
        fwrite(registro->dieta, sizeof(char), tamD, nomebin);
    }
    fwrite("#", sizeof(char), 1, nomebin);  // Delimitador

    if (registro->alimento != NULL && strcmp(registro->alimento, "#") != 0) {
        fwrite(registro->alimento, sizeof(char), tamA, nomebin);
    }
    fwrite("#", sizeof(char), 1, nomebin);  // Delimitador

    // Verifica quanto falta para completar os 160 bytes
    int preenche = registro->tam_preenchimento;
    char aux[preenche];
    memset(aux, REGISTRO_FILL, preenche);  // Preenche com o caractere de preenchimento
    fwrite(aux, sizeof(char), preenche, nomebin);
}

Registro *registro_readcsv(FILE *csv) {
    Registro *registro = malloc(sizeof(Registro));
    char linha[300];
    fgets(linha, sizeof(linha), csv);

    // Remove os caracteres de nova linha (tanto \n quanto \r)
    linha[strcspn(linha, "\n")] = '\0';
    linha[strcspn(linha, "\r")] = '\0';

    char *linha_copy = linha;
    //alocando memoria
    registro->nome = calloc(160,sizeof(registro->nome));
    registro->nEspecie = calloc(160,sizeof(registro->nEspecie));
    registro->dieta = calloc(160,sizeof(registro->dieta));
    registro->habitat = calloc(160,sizeof(registro->habitat));
    registro->alimento = calloc(160,sizeof(registro->alimento));
    registro->tipo = calloc(160,sizeof(registro->tipo));

    // Nome
    strcpy(registro->nome,strsep(&linha_copy, ","));

    // Dieta
    strcpy(registro->dieta,strsep(&linha_copy, ","));

    // Habitat
    strcpy(registro->habitat,strsep(&linha_copy, ","));

    // População
    char *populacao = strsep(&linha_copy, ",");
    if (strlen(populacao) == 0) {
        registro->populacao = -1;
    }
    else{
        registro->populacao = atoi(populacao);
    }
    
    // Tipo
    strcpy(registro->tipo,strsep(&linha_copy, ","));
    

    // Velocidade
    char *velocidade = strsep(&linha_copy, ",");
    if (strlen(velocidade) == 0) {
        registro->velocidade = -1;
    }
    else{
        registro->velocidade = atoi(velocidade);
    }
    
    // Unidade de medida
    char *unidade = strsep(&linha_copy, ",");
    if (strlen(unidade) == 0) {
        registro->uniMedida = '$';
    }
    else{
        registro->uniMedida = unidade[0];
    }

    // Tamanho
    char *tamanho = strsep(&linha_copy, ",");
    if (strlen(tamanho) == 0) {
        registro->tamanho = -1;
    }
    else{
        registro->tamanho = atof(tamanho);
    }

    // Espécie
    strcpy(registro->nEspecie,strsep(&linha_copy, ","));
   
    // Alimento
    strcpy(registro->alimento,strsep(&linha_copy, ","));
    
    // Configurações adicionais para o registro
    registro->removido = REGISTRO_REMOVIDO_FALSE;
    registro->encadeamento = 0;

    // Calcular bytes restantes para completar os 160 bytes
    // calcular tam_preenchimento corretamente com base nos tamanhos das strings
    int tam = strlen(registro->nome);
    int tamE = strlen(registro->nEspecie);
    int tamA = strlen(registro->alimento);
    int tamH = strlen(registro->habitat);
    int tamD = strlen(registro->dieta);
    int tamT = strlen(registro->tipo);

    // 18 bytes para os campos fixos (população, tamanho, velocidade, uniMedida, removido e encadeamento) e 6 bytes para delimitadores '#'
    registro->tam_preenchimento = 160 - ((tam + tamD + tamH + tamT + tamE + tamA) * sizeof(char) + 18 +6);

    return registro;
}


void registro_print(Registro *registro){

    
    printf("Nome: %s\n", registro->nome);
    printf("Especie: %s\n", registro->nEspecie);

    if(strcmp(registro->tipo, "") != 0){
        printf("Tipo: %s\n", registro->tipo);
    }

   
    printf("Dieta: %s\n", registro->dieta);
    
    if(strcmp(registro->habitat, "") != 0){
        printf("Lugar que habitava: %s\n", registro->habitat);
    }

    if(registro->tamanho != -1){
        printf("Tamanho: %.1f m\n", registro->tamanho);
    }
    if (registro->velocidade != -1 && registro->uniMedida != '$'){
        printf("Velocidade: %d %cm/h\n", registro->velocidade, registro->uniMedida);
    }
    printf("\n");
    
}
void registro_busca_elemento(char *valor, int valorint, float valorf, Registro *registro) {
    if (valor != NULL && strcmp(registro->nome, valor) == 0) {
        registro_print(registro);
    } else if (valor != NULL && strcmp(registro->nEspecie, valor) == 0) {
        registro_print(registro);
    } else if (valor != NULL && strcmp(registro->alimento, valor) == 0) {
        registro_print(registro);
    } else if (valor != NULL && strcmp(registro->dieta, valor) == 0) {
        registro_print(registro);
    } else if (valor != NULL && strcmp(registro->tipo, valor) == 0) {
        registro_print(registro);
    } else if (valor != NULL && strcmp(registro->habitat, valor) == 0) {
        registro_print(registro);
    } else if (registro->populacao == valorint) {
        registro_print(registro);
    } else if (registro->velocidade == valorint) {
        registro_print(registro);
    } else if (registro->tamanho == valorf) {
        registro_print(registro);
    }
}

int verificacaoString(char *campo) {
    // Verifica o tipo do campo e retorna a posição
    if (strcmp("nome", campo) == 0) {
        return 0; // Retorna 0 para 'nome'
    } else if (strcmp("especie", campo) == 0) {
        return 1; // Retorna 1 para 'especie'
    } else if (strcmp("habitat", campo) == 0) {
        return 2; // Retorna 2 para 'habitat'
    } else if (strcmp("tipo", campo) == 0) {
        return 3; // Retorna 3 para 'tipo'
    } else if (strcmp("dieta", campo) == 0) {
        return 4; // Retorna 4 para 'dieta'
    } else if (strcmp("alimento", campo) == 0) {
        return 5; // Retorna 5 para 'alimento'
    } else if (strcmp("velocidade", campo) == 0) {
        return 6;
    } else if (strcmp("populacao", campo) == 0) {
        return 7;
    } else if (strcmp("tamanho", campo) == 0) {
        return 8;
    } else {
        printf("Campo inexistente.\n");
        return -1; // Campo inexistente
    }
}

bool registro_field(char *nome_campo){
    // retorna se é um campo de string ou inteiro
}

void registro_remove(Registro *registro){
    // remove logicamente um registro
}

bool registro_isValid(Registro *registro){
    // retorna true caso o registro não seja removido
    return registro->removido == REGISTRO_REMOVIDO_FALSE;
}




int registro_getPop(Registro *registro){
    // verifica o valor do campo topo
    return registro->populacao;
}
float registro_getTam(Registro *registro){
    // verifica o valor do campo proximo a ser removido
    return registro->tamanho;
}

char registro_getUnimedida(Registro *registro){
    // verifica a quantidade de paginas 
    return registro->uniMedida;
}

int registro_getVelocidade(Registro *registro){
    // verifica quantas vezes foi compactado
    return registro->velocidade;
}

char* registro_getNome(Registro *registro){
    return registro->nome;
}

char* registro_getNEspecie(Registro *registro){
    return registro->nEspecie;
}

char* registro_getHabitat(Registro *registro){
    return registro->habitat;
}

char* registro_getTipo(Registro *registro){
    return registro->tipo;
}

char* registro_getDieta(Registro *registro){
    return registro->dieta;
}
char* registro_getAlimenta(Registro *registro){
    return registro->alimento;
}
char registro_getRemovido(Registro *registro){
    return registro->removido;
}

int registro_getEncadeamento(Registro *registro){
    return registro->encadeamento;
}








void registro_setPop(Registro *registro, int pop){
    // verifica o valor do campo topo
    registro->populacao = pop;
}
void registro_setTam(Registro *registro, float tam){
    // verifica o valor do campo proximo a ser removido
    registro->tamanho = tam;
}

void registro_setUnimedida(Registro *registro, char unidade){
    // verifica a quantidade de paginas 
    registro->uniMedida = unidade;
}

void registro_setVelocidade(Registro *registro, int velocidade){
    // verifica quantas vezes foi compactado
    registro->velocidade = velocidade;
}

void registro_setNome(Registro *registro, char *nome){
    strcpy(registro->nome, nome);
}

void registro_setNEspecie(Registro *registro, char *especie){
    strcpy(registro->nEspecie, especie);
}

void registro_setHabitat(Registro *registro, char *habitat){
    strcpy(registro->habitat, habitat);
}

void registro_setTipo(Registro *registro,char *tipo){
    strcpy(registro->tipo, tipo);
}

void registro_setDieta(Registro *registro, char *dieta){
    strcpy(registro->dieta, dieta);
}
void registro_setAlimenta(Registro *registro, char *alimento){
    strcpy(registro->alimento, alimento);
}

void registro_setRemovido(Registro *registro, bool removido){
    registro->removido=removido;
}

void registro_setEncadeamento(Registro *registro, int encadeamento) {
    registro->encadeamento = encadeamento;
}