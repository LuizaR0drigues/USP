#include "bregistro.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LOTACAO_MAX 4

#define FOLHA '0'
#define FOLHA_N '1'
#define NULL_VALUE -2

#define TAMANHO_NO 93

int contador_RRN = 0; // vai ser substituido pelo cabecalho

//caso o ponteiro pi seja nulo = -1
//os ints inicializam com -1
NoArvore *no_criar(bool folha,int rrn)
{
    NoArvore *no = malloc(sizeof(NoArvore));
    if(folha){
        no->folha = FOLHA; // é folha
    }else{
        no->folha = FOLHA_N; // não é folha
    }
    
    no->nroChavesIndexadas = -1;
    no->RRNdoNo = rrn;
    for(int i=0; i< ORDEM; i++)
    {
        no->P[i] = -1; //5 ponteiros
    }
    for(int i=0; i < ORDEM -1; i++)
    {
        no->CPRs[i].C = NULL_VALUE; //4 campos de referencia
        no->CPRs[i].PR = -1;
    }
    no->lotacao=0;
 return no;
}

NoArvore *no_readbin(FILE* entrada,int RRN) 
{
    fseek(entrada,TAMANHO_NO*RRN,SEEK_SET); //vai pro lugar certo
    NoArvore* aux = no_criar(true,-1);


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
        fwrite(&no->CPRs[i].C, sizeof(int), 1, nomebin);
        fwrite(&no->CPRs[i].PR, sizeof(int), 1, nomebin);
    }

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
    CPR null_cpr;null_cpr.C=NULL_VALUE;null_cpr.PR=-1;null_pcpr.corpo=null_cpr;null_pcpr.P=-1;
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


// tratar o caso da raiz !!
PCPR no_inserir_recursivo(FILE *nomebin,NoArvore *atual,CPR valor_inserir,int rrn_raiz){
    // O retorno é direcionado para o nó pai
    
    //critério de parada: é nó folha
    if(atual->folha==FOLHA){
        // tentar inserir
        PCPR overflow = no_tenta_inserir(atual,valor_inserir,nomebin);

        if(PCPR_isnull(overflow)){
            //retorna um nó nulo
            printf("   >> Não aconteceu overflow\n");
            PCPR null_pcpr = get_null_pcpr();
            return null_pcpr;
        }else{
            printf("   >> Aconteceu overflow, realizando split 1 pra 2\n");
            //faz o split 1 pra 2 e retorna o que ficar no meio
            // sabemos que isso aqui vai acontecer quando a lotação do nó for igual a LOTACAO_MAX
            // primeiro caso: cria um nó folha irmãozinho
            printf("Prévia antecipada: ");no_print(atual);
            
            //retiramos o do meio considerando LOTACAO_MAX+1 elementos
            int idx_meio = (LOTACAO_MAX+1)/2;
            
                // salvando o do meio pra subir
            PCPR subiu;
            subiu.corpo = atual->CPRs[idx_meio];
            subiu.P = atual->P[idx_meio+1];

                // removendo o do meio no nó
            for(int i=idx_meio+1;i<LOTACAO_MAX;i++){
                printf("%ld <-- %ld\n",atual->CPRs[i-1].C,atual->CPRs[i].C);
                atual->CPRs[i-1] = atual->CPRs[i];
                atual->P[i] = atual->P[i+1];
            }
            atual->lotacao--; // lotação diminuiu
            
            atual->CPRs[LOTACAO_MAX-1] = overflow.corpo;
            atual->P[LOTACAO_MAX] = overflow.P;
            atual->lotacao++; // lotação volta a aumentar

            // passar para o irmaozinho tudo que vem desde do idx_meio até o fim
            NoArvore *irmaozinho = no_criar(true,++contador_RRN);
            int j=0;
            for(int i=idx_meio;i<LOTACAO_MAX;i++,j++){
                irmaozinho->CPRs[j] = atual->CPRs[i];
                atual->CPRs[i].C = NULL_VALUE;
                atual->CPRs[i].PR = -1;
                atual->lotacao--;
            }

            // escrever o nó atual no disco
            no_writebin(nomebin,atual);

            // escrever o irmãozinho no disco
            no_writebin(nomebin,irmaozinho);

            // retorna o subiu
            return subiu;
        }
        
    }

    
    // fazendo busca sequencial para saber onde entrar:
    int idx_entrar = 0;
    for(int i=0;i<atual->lotacao;i++){ // descobre a posição para inserir
        if(valor_inserir.C > atual->CPRs[i].C){
            idx_entrar = i+1;
        }
    }

    int RRN_entrar = idx_entrar;
    NoArvore *no_filho = no_readbin(nomebin,RRN_entrar);
    PCPR inserir_restante = no_inserir_recursivo(nomebin,no_filho,valor_inserir,rrn_raiz);
    // inserir_restante é o CBR que subiu depois de ter feito o split 1 para 2

    // if(rrn_raiz == atual->RRNdoNo && inserir_restante.C!=NULL_VALUE){
    //     // significa que ele voltou de tudo e precisa criar uma raiz acima de tudo
    // }

    // reorganiza os ponteiros
}