#include "bregistro.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "registro.h"

#define LOTACAO_MAX 4

#define FOLHA '0'
#define FOLHA_N '1'
#define NULL_VALUE -1

#define TAMANHO_NO 93

int contador_RRN = 0; // vai ser substituido pelo cabecalho

//caso o ponteiro pi seja nulo = -1
//os ints inicializam com -1
NoArvore *no_criar(bool folha)
{
    //printf("Um novo no foi criado\n");
    NoArvore *no = malloc(sizeof(NoArvore));
    if(folha){
        no->folha = FOLHA; // é folha
    }else{
        no->folha = FOLHA_N; // não é folha
    }
    
    no->nroChavesIndexadas = -1;
    no->RRNdoNo = -1;
    for(int i=0; i< ORDEM; i++)
    {
        no->P[i] = -1; //5 ponteiros
        //printf("Ponteiro de indice[%d]: %d\n", i, no->P[i]);
    }
    for(int i=0; i < ORDEM-1 ; i++)
    {
        no->CPRs[i].C = NULL_VALUE; //4 campos de referencia
        no->CPRs[i].PR = -1;
        //printf(" Chave[%d]: %ld   -- Pr: %ld\n", i, no->CPRs[i].C, no->CPRs[i].PR);
    }
    no->lotacao=0;
 return no;
}

NoArvore *no_readbin(FILE* entrada) 
{
    //fseek(entrada,TAMANHO_NO*RRN,SEEK_SET); //vai pro lugar certo
    NoArvore* aux = no_criar(true);


    fread(&aux->folha, sizeof(char), 1, entrada);
    fread(&aux->nroChavesIndexadas, sizeof(int), 1, entrada);
    fread(&aux->RRNdoNo, sizeof(int), 1, entrada);
    for(int i =0; i<ORDEM-1; i++)
    {
        fread(&aux->CPRs[i].C, sizeof(int), 1, entrada);
        fread(&aux->CPRs[i].PR, sizeof(int), 1, entrada);
    }

    return aux;
}


void no_writebin(FILE *nomebin, NoArvore *no)
{
    fseek(nomebin, TAMANHO_NO*no->RRNdoNo,SEEK_SET);
    fwrite(&no->folha, sizeof(char), 1, nomebin);
    fwrite(&no->nroChavesIndexadas, sizeof(int), 1, nomebin);
    fwrite(&no->RRNdoNo, sizeof(int), 1, nomebin);
     for(int i =0; i<ORDEM-1; i++)
    {
        fwrite(&no->CPRs[i].C, sizeof(long int), 1, nomebin);
        fwrite(&no->CPRs[i].PR, sizeof(long int), 1, nomebin);
    }
    printf("Ok\n");
}


void no_print(NoArvore *no){
    printf("RRN=%d  |  P[0]=%d  ",no->RRNdoNo,no->P[0]);
    for(int i=0;i<LOTACAO_MAX;i++){
        printf("(%ld %ld) P[%d]=%d  ",
            no->CPRs[i].C,no->CPRs[i].PR,
            i+1,no->P[i+1]);
    }
    printf("\n");
}

PCPR get_null_pcpr(){
    PCPR null_pcpr;
    CPR null_cpr;
    null_cpr.C=NULL_VALUE;
    null_cpr.PR=-1;
    null_pcpr.corpo=null_cpr;
    null_pcpr.P=-1;
    return null_pcpr;
}

PCPR no_tenta_inserir(NoArvore *no,CPR valor_inserir,FILE *arquivo){
    // Retorna o CPR que sair caso ele fique cheio
    PCPR overflow = get_null_pcpr();


    // Fazer a inserção binária aqui ao invés desse método aqui embaixo:
    int idx_inserir = 0;
    for(int i=0;i<no->lotacao;i++){ // descobre a posição para inserir
        if(valor_inserir.C > no->CPRs[i].C){
            idx_inserir = i+1;
        }
    }
    
    for(int i=no->lotacao - 1;i>=idx_inserir;i--){ // faz o shift
        if(i+1 == LOTACAO_MAX){
            overflow.P = no->P[i+1];
            overflow.corpo = no->CPRs[i];
        }else{
            no->CPRs[i+1] = no->CPRs[i];
            no->P[i+2] = no->P[i+1];
        }
        
    }
    no->CPRs[idx_inserir] = valor_inserir; // coloca o valor de fato
    no->lotacao++;

    // salva no arquivo as atualizações
    no_writebin(arquivo,no);

    return overflow; // avisa que inseriu de boas
}

bool PCPR_isnull(PCPR pcpr){
    return pcpr.corpo.C == NULL_VALUE;
}

void space(int j){
    for(int i=0;i<j;i++){
        printf(" ");
    }
}

// trocar o contador_RRN por c->proxRRNNo
// tratar o caso da raiz !!
PCPR no_inserir_recursivo(FILE *indice,NoArvore *atual,CPR valor_inserir, CabecalhoArvore *c, int level){
    // caso de inicialização da árvore B
    printf("\nValor do ponteiro Btree: %p.  Valor do noraiz: %d\n",atual,c->noRaiz);
   
    if(c->noRaiz== 0){
        
        space(level);printf(">> inserção sem raiz -- criando raiz primária\n");
        atual = no_criar(true);
        atual->RRNdoNo = contador_RRN++;
        
        // Atualiza o cabeçalho com o novo RRN da raiz
        bcabecalho_setNoRaiz(c,atual->RRNdoNo);
        
        // Atualiza o cabeçalho no arquivo binário
        fseek(indice,0,SEEK_SET);
        bcabecalho_writebin(indice,c);
    
    }
    
    

    PCPR inserir_restante = get_null_pcpr();
    if(atual->folha!=FOLHA){
        space(level);printf(">> Não é uma folha --> chamando recursão \n");
        // fazendo busca sequencial para saber onde entrar:
        int idx_entrar = 0;
        for(int i=0;i<atual->lotacao;i++){ // descobre a posição para inserir
            if(valor_inserir.C > atual->CPRs[i].C){
                idx_entrar = i+1;
                printf("Indice de inserção: %d", idx_entrar);
            }
        }

        int RRN_entrar = idx_entrar;
       // NoArvore *no_filho = no_readbin(indice,RRN_entrar);
      //  inserir_restante = no_inserir_recursivo(indice,no_filho,valor_inserir, c, level+1);// inserir_restante é o CBR que subiu depois de ter feito o split 1 para 2
    }else{
        // é como se tivesse voltando do vazio da folha
        space(level);printf(">> É uma folha --> tentando inserir diretamente\n");
        inserir_restante.corpo = valor_inserir; 
    }
 
    
    // caso em que ele para caso seja null_pcpr:
    // caso que proibe ele tentar inserir caso os retornos seja nulo
    if(PCPR_isnull(inserir_restante)){
        space(level);printf(">> O valor retornado é nulo, portanto já foi inserido e só está voltando a recursão\n");
        return inserir_restante;
    }


    PCPR overflow = no_tenta_inserir(atual,valor_inserir,indice);

    printf("nó atual:");no_print(atual);printf("\n\n");
    if(PCPR_isnull(overflow)){
        //retorna um nó nulo (Conseguiu inserir diretamente)
        space(level);printf(">> Não aconteceu overflow --> [%ld] foi inserido com sucesso (retorna nulo)\n",inserir_restante.corpo.C);
        PCPR null_pcpr = get_null_pcpr();
        return null_pcpr;
    }else{
        space(level);printf(">> Aconteceu overflow --> realizando split 1 pra 2\n");
        //faz o split 1 pra 2 e retorna o que ficar no meio
        // sabemos que isso aqui vai acontecer quando a lotação do nó for igual a LOTACAO_MAX
        // primeiro caso: cria um nó folha irmãozinho
        // printf("Prévia antecipada: ");no_print(atual);
        
        //retiramos o do meio considerando LOTACAO_MAX+1 elementos
        int idx_meio = (LOTACAO_MAX+1)/2;
        
            // salvando o do meio pra subir
        PCPR subiu;
        subiu.corpo = atual->CPRs[idx_meio];
        // subiu.P = atual->P[idx_meio+1];             // deveria apontar para o irmãozinho ------------------------------------------

            // removendo o do meio no nó
        for(int i=idx_meio+1;i<LOTACAO_MAX;i++){
            atual->CPRs[i-1] = atual->CPRs[i];
            atual->P[i] = atual->P[i+1];
        }
        atual->lotacao--; // lotação diminuiu
        
        // atual->CPRs[LOTACAO_MAX-1] = overflow.corpo;
        // atual->P[LOTACAO_MAX] = overflow.P;
        // atual->lotacao++; // lotação volta a aumentar

        // passar para o irmaozinho tudo que vem desde do idx_meio até o fim
        NoArvore *irmaozinho = no_criar(atual->folha);
        irmaozinho->RRNdoNo = contador_RRN++;
        subiu.P = irmaozinho->RRNdoNo; // o que subiu aponta para o irmãozinho
        
        irmaozinho->CPRs[0] = overflow.corpo;
        irmaozinho->P;

        space(level);printf("  -- o nó que subiu é o [%ld]\n",subiu.corpo.C);

        int j=0;
        for(int i=idx_meio;i<LOTACAO_MAX;i++,j++){
            irmaozinho->CPRs[j] = atual->CPRs[i];
            atual->CPRs[i].C = NULL_VALUE;
            atual->CPRs[i].PR = -1;
            atual->lotacao--;
        }

        // escrever o nó atual no disco
        no_writebin(indice,atual);

        // escrever o irmãozinho no disco
        no_writebin(indice,irmaozinho);

        // retorna o subiu

        // porém, se o nó que eu estiver inserindo (atual) já for a raiz, ele sube para a raiz
        if(c->noRaiz == atual->RRNdoNo){
            space(level);printf(">> Está tentando dar split na raiz --> cria uma nova raiz superior\n");
            NoArvore *nova_raiz = no_criar(false);
            nova_raiz->RRNdoNo = contador_RRN++;
            nova_raiz->P[0] = atual->RRNdoNo; //aponta para o que era antes (que no caso é o atual)
            nova_raiz->P[1] = irmaozinho->RRNdoNo; // aponta para o irmãozinho que acabou de ser criado
            
            space(level);printf("Raiz superior: ");no_print(nova_raiz);

            // atualiza o cabecalho
            bcabecalho_setNoRaiz(c,nova_raiz->RRNdoNo);
            fseek(indice,0,SEEK_SET);
            bcabecalho_writebin(indice,c);
        }
        return subiu;
        
    }
}

int buscando_chave(FILE *arquivo_indice, NoArvore *atual, long int campo)
{
    fseek(arquivo_indice, 0, SEEK_SET); //ponteiro no inicio pra leitura do cabecalho
    CabecalhoArvore *bcabe = bcabecalho_readbin(arquivo_indice);  // Apenas a leitura

    if (bcabe == NULL || atual == NULL) {
        return -1;  // Falha ao ler o cabeçalho
    }

    int quant =0;
    int posicao_atual = bcabe->noRaiz;  // Começa a busca pelo nó raiz
    
    while (posicao_atual != -1) { // procura até encontrar um rrn invalido
       
        // Move para o início do nó  a partir do campo folha
        fseek(arquivo_indice, (posicao_atual+1) * 93 + sizeof(char), SEEK_SET);
        // Lê a estrutura do nó
        //fread(&atual->folha, sizeof(char), 1, arquivo_indice); //primeiro campo 1 byte
        fread(&atual->nroChavesIndexadas, sizeof(int), 1, arquivo_indice); //segundo campo 4 bytes
        fread(&atual->RRNdoNo, sizeof(int), 1, arquivo_indice); //terceiro campo 4 bytes

        quant = atual->nroChavesIndexadas;
        for (int i = 0; i < quant; i++) { 
            //lendo os campos de cada regsitro da presente na pagina da arvore
            fread(&atual->P[i], sizeof(int), 1, arquivo_indice); //lê o ponteiro
            fread(&atual->CPRs[i].C, sizeof(long int), 1, arquivo_indice); // lê a chave
            fread(&atual->CPRs[i].PR, sizeof(long int), 1, arquivo_indice);     // lê o PR
                    
            if (atual->CPRs[i].C == campo) {
                //printf("Encontrou\n");
                return atual->CPRs[i].PR;  // Encontrou a chave
            } else if (campo < atual->CPRs[i].C) {
                posicao_atual =  atual->P[i];  // Atualiza o RRN para o ponteiro à esquerda
                break;
            } else if (i == quant-1) {
                // Se chegou ao final do laço e o campo é maior que todas as chaves
                fread(&posicao_atual, sizeof( int), 1, arquivo_indice);  // Lê o ponteiro à direita
                break;
            }
        }
        
    }
    return -1;
}



