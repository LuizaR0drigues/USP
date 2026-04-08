
typedef struct NO* ArvBin;

ArvBin* cria_ArvBin();
void libera_ArvBin(ArvBin *raiz);
int insere_ArvBin(ArvBin* raiz, char *tag, char status);
int remove_ArvBin(ArvBin *raiz, char *valor);
int estaVazia_ArvBin(ArvBin *raiz);
int altura_ArvBin(ArvBin *raiz);
int totalNO_ArvBin(ArvBin *raiz);
int consulta_ArvBin(ArvBin *raiz, char *valor, int *n2);
void preOrdem_ArvBin(ArvBin *raiz);
void emOrdem_ArvBin(ArvBin *raiz);
void posOrdem_ArvBin(ArvBin *raiz);

// Funcoes Adicionais
//int Procura_preOrdem_ArvBin(ArvBin *raiz, char *valor);
void Exibe_PreOrdem_ArvBin(ArvBin *raiz);


