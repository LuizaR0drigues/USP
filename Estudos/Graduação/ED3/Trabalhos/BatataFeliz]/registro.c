#include "registro.h"
#include "cabecalho.h"


Registro *registro_readbin(FILE *file) {
    // Lê o registro de um arquivo binário
    // Não abrir o arquivo aqui, pois já foi passado como parâmetro
     Registro *registro;
    Cabecalho cabecalho;
    // Lê o cabeçalho do arquivo
    if (fread(&cabecalho, sizeof(Cabecalho), 1, file) != 1) {
        printf("Erro ao ler o cabeçalho do arquivo.\n");
        return NULL;  // Retorna NULL em caso de erro
    }

    printf("Status: %c\n", cabecalho.status);

    if (cabecalho.status == '0') {
        printf("Falha no processamento do arquivo: arquivo inconsistente.\n");
        return NULL;  // Retorna NULL se o cabeçalho está inconsistente
    }

    // Lê os registros
    int registros_encontrados = 0;
    
    while (fread(&registro->removido, sizeof(char), 1, file) == 1) {
        // Verifica se o registro foi logicamente removido
        if (registro->removido == '1') {
            fseek(file, sizeof(int) + sizeof(int) + sizeof(float) + sizeof(char) + sizeof(int), SEEK_CUR); // Pula para o próximo registro
            continue;  // Ignora registros removidos
        }

        fread(&registro->encadeamento, sizeof(int), 1, file);
        fread(&registro->populacao, sizeof(int), 1, file);
        fread(&registro->tamanho, sizeof(float), 1, file);
        fread(&registro->uniMedida, sizeof(char), 1, file);
        fread(&registro->velocidade, sizeof(int), 1, file);

        registros_encontrados++; // Incrementa o contador de registros encontrados
    }

    if (registros_encontrados == 0) {
        printf("Registro inexistente.\n");
        return NULL;  // Retorna NULL se nenhum registro for encontrado
    }

    return registro;  // Retorna o registro lido
}

void registro_writebin(FILE *nomebin, Registro *registro){// escreve o registro no arquivo binário
//função: // pformata as strings sem o \0, adicionando o delimitador, depois coloca o preenchimento usando a 'tam_preenchimento'
    //formatando as strings de tamanho variaveis
    // Escreve strings (sem \0, já que é um formato binário e tamanho variável) usando o tamanho de cada uma
    int tamT = 0, tamD = 0, tamA = 0, tamE = 0, tamH = 0, tam = 0;
    tam = strlen(registro->nome);
    tamA = strlen(registro->alimento);
    tamD = strlen(registro->dieta);
    tamE = strlen(registro->nEspecie);
    tamT = strlen(registro->tipo);
    tamH = strlen(registro->habitat);

    
    
    // Escreve campos de tamanho fixo
    fwrite(&registro->removido, sizeof(char), 1, nomebin);
    fwrite(&registro->encadeamento, sizeof(int), 1, nomebin);
    fwrite(&registro->populacao, sizeof(int), 1, nomebin);
    fwrite(&registro->tamanho, sizeof(float), 1, nomebin);
    fwrite(&registro->uniMedida, sizeof(char), 1, nomebin);
    fwrite(&registro->velocidade, sizeof(int), 1, nomebin);
    //escreve campos de tamanho variavel
    fwrite(registro->nome, sizeof(char), tam, nomebin);
    fwrite("#", sizeof(char), 1, nomebin);  // Delimitador

    fwrite(registro->nEspecie, sizeof(char), tamE, nomebin);
    fwrite("#", sizeof(char), 1, nomebin);  // Delimitador

    fwrite(registro->habitat, sizeof(char), tamH, nomebin);
    fwrite("#", sizeof(char), 1, nomebin);  // Delimitador

    fwrite(registro->tipo, sizeof(char), tamT, nomebin);
    fwrite("#", sizeof(char), 1, nomebin);  // Delimitador

    fwrite(registro->dieta, sizeof(char), tamD, nomebin);
    fwrite("#", sizeof(char), 1, nomebin);  // Delimitador

    fwrite(registro->alimento, sizeof(char), tamA, nomebin);
    fwrite("#", sizeof(char), 1, nomebin);  // Delimitado

    
    // Verifica quanto falta para completar os 160 bytes
    int preenche = registro->tam_preenchimento;
    char aux[preenche];
    for(int i=0; i<preenche; i++)
    {
        aux[i] = REGISTRO_FILL;
    }
    fwrite(aux, sizeof(char), preenche, nomebin);

}

Registro *registro_readcsv(FILE *csv){
    Registro *registro = malloc(sizeof(Registro));

    char linha[300];
    fgets(linha, sizeof(linha), csv);

    // Remove os caracteres de nova linha (tanto \n quanto \r)
    linha[strcspn(linha, "\n")] = '\0'; //remove o \n e \r de cada linha do csv
    linha[strcspn(linha, "\r")] = '\0';

    // Início da leitura dos campos separados por vírgula
    char *linha_copy = linha;

    // Nome
    char* campo = strsep(&linha_copy, ","); //usando a função strsep para dividir em tokens
    
    int tamT = 0, tamD = 0, tamA = 0, tamE = 0, tamH = 0, tam = 0; //variaveis que irao armazenar os tamanhos dos campos variaveis
    if (campo != NULL) {
        tam = strlen(campo);
        registro->nome = (char*) malloc((tam + 1) * sizeof(char));
        strcpy(registro->nome, campo);
        // registro->nome[tam] = '#'; // Finaliza com '#'
    }
    
    // Dieta
    campo = strsep(&linha_copy, ",");
    if (campo != NULL) {
        tamD = strlen(campo);
        registro->dieta = (char*) malloc((tamD + 1) * sizeof(char));
        strcpy(registro->dieta, campo);
        // registro->dieta[tamD] = '#'; // Finaliza com '#'
        
    }

    // Habitat
    campo = strsep(&linha_copy, ",");
    if (campo != NULL) {
        tamH = strlen(campo);
        registro->habitat = (char*) malloc((tamH + 1) * sizeof(char));
        strcpy(registro->habitat, campo);
        // registro->habitat[tamH] = '#'; // Finaliza com '#'
            
    }

    // População
    campo = strsep(&linha_copy, ",");
    if(campo != NULL)
    {
        registro->populacao = atoi(campo);
    }
    else{
        registro->populacao = -1; //para caso de poulação -> null
    }

    // Tipo
    campo = strsep(&linha_copy, ",");
    if (campo != NULL) {
        tamT = strlen(campo);
        registro->tipo = (char*) malloc((tamT + 1) * sizeof(char));
        strcpy(registro->tipo, campo);
        // registro->tipo[tamT] = '#'; // Finaliza com '#'
    }

    // Velocidade
    campo = strsep(&linha_copy, ",");
    if(campo != NULL)
    {
        registro->velocidade = atoi(campo);
    }
    else{
        registro->populacao = -1;
    }

    // Unidade de medida
    campo = strsep(&linha_copy, ",");
    registro->uniMedida = (campo != NULL) ? campo[0] : '$';
    if(campo != NULL)
    {
        registro->uniMedida = campo[0];
    }
    else{
        registro->uniMedida = '$';
    }

    // Tamanho
    campo = strsep(&linha_copy, ",");
    if(campo != NULL)
    {
        registro->tamanho = atof(campo);
    }
    else{
        registro->tamanho = -1.0;
    }

    // Espécie
    campo = strsep(&linha_copy, ",");
    if (campo != NULL) {
        tamE = strlen(campo);
        registro->nEspecie = (char*) malloc((tamE + 1) * sizeof(char));
        strcpy(registro->nEspecie, campo);
        // registro->nEspecie[tamE] = '#'; // Finaliza com '#'
    }

    // Alimento
    campo = strsep(&linha_copy, ",");
    if (campo != NULL) {
        tamA = strlen(campo);
        registro->alimento = (char*) malloc((tamA + 1) * sizeof(char));
        strcpy(registro->alimento, campo);
        // registro->alimento[tamA] = '#'; // Finaliza com '#'
    }

    // Calcular bytes restantes para completar os 160 bytes
    // nome + dieta + habitat + tipo + especie + alimento
    // 18 = tamanho das variáveis fixas
    registro->tam_preenchimento = 160 - ((tam + tamD + tamH + tamT + tamE + tamA)*sizeof(char) + 18);

    // Armazena o registro no arquivo binário
    registro->removido = REGISTRO_REMOVIDO_FALSE; // não removido
    registro->encadeamento = 0; // não há encadeamento
    
    return registro;
}

void registro_print(Registro *registro){
    printf("Nome: %s\n", registro->nome);
    printf("Dieta: %s\n", registro->dieta);
    printf("Habitat: %s\n", registro->habitat);
    printf("População: %d\n", registro->populacao);
    printf("Tipo: %s\n", registro->tipo);
    printf("Velocidade: %d %c/h\n", registro->velocidade, registro->uniMedida);
    printf("Tamanho: %.2f\n", registro->tamanho);
    printf("Espécie: %s\n", registro->nEspecie);
    printf("Alimento: %s\n", registro->alimento);
    printf("\n");
}

bool registro_field(char *nome_campo){
    // retorna se é um campo de string ou inteiro
}

void registro_remove(Registro *registro){
    // remove logicamente um registro
}

bool registro_isValid(Registro *registro){
    // retorna true caso o registro não seja removido
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
