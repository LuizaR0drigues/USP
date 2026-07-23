/**********************************************************************************
Luiza Rodrigues Cardoso - 14593332
Trabalho 2.2 - Among Us // Estrutura de Dados 2
Estratégia adotada -> Grafo não-direcionado e ponderado; caminhos minimos
*********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#define infinito 1e100
//Estrutura do grafo
typedef struct No{
    int destino;
    double peso;
    struct No *proximo;
}No;

typedef struct{
    int num_vert;
    No **list_adj;
}Grafo;

void add_aresta(Grafo *grafo, int origem, int destino, double peso){
    No *novo = malloc(sizeof(No));
    novo->destino = destino;
    novo->peso = peso;

    //inserindo no inicio da lista
    novo->proximo = grafo->list_adj[origem];
    grafo->list_adj[origem] = novo;

    //direção oposta
    No *dir_oposta = malloc(sizeof(No));
    dir_oposta->destino = origem;
    dir_oposta->peso = peso;

    dir_oposta->proximo = grafo->list_adj[destino];
    grafo->list_adj[destino] = dir_oposta;
}

int menor_dist(double dist[], int visitado[], int tam){
    double aux;
    int idx = -1;
    //encontrando o primeiro vertice que ainda nao visitado
    for(int i=0; i < tam;i++){
        if(visitado[i] == 0){
            aux = dist[i];
            idx = i;
            break;
        }
    }

    for(int i=0; i < tam;i++){
        if(aux > dist[i] && visitado[i] == 0)
        {
            aux =  dist[i];
            idx = i;
        }
    }
    //caso onde todos ja foram visitados
    if(idx == -1)
    {
        return -1;
    }

    return idx;
}

void dijkstra(Grafo *grafo, int num_salas, double dist[]){
    //caluclando o menor tempos
    int visitados[num_salas], idx_menor_dist;
    for(int i=0; i< num_salas;i++){
        dist[i] = infinito;
        visitados[i] = 0;
    }
    dist[0] = 0;

    for( int i =0; i< num_salas; i++)
    {
        idx_menor_dist =  menor_dist(dist, visitados, num_salas);

        if(idx_menor_dist == -1){
            break;
        }
        visitados[idx_menor_dist] =  1;
        No *atual = grafo->list_adj[idx_menor_dist];

        while( atual != NULL){

            int vizinho =  atual->destino;
            double peso = atual->peso;

            if( !visitados[vizinho] && dist[idx_menor_dist] + peso < dist[vizinho]){
                dist[vizinho] =  dist[idx_menor_dist] + peso;
            }

            atual =  atual->proximo;
        }
    }
}

int main(){
    //leitura dos dados
    //num_salas, num_ligações por corredores, num_ligações por tuulações e qunatidade de consultas
    int num_salas, lig_corredor, lig_tubula, qtd_consult;
    
    scanf("%d %d %d %d", &num_salas, &lig_corredor, &lig_tubula, &qtd_consult);

    // //Criando os grafos Tripulantes e Impostor
    Grafo tripulante;
    tripulante.num_vert = num_salas;
    tripulante.list_adj = malloc(num_salas * sizeof(No*));

    Grafo impostor;
    impostor.num_vert = num_salas;
    impostor.list_adj = malloc(num_salas * sizeof(No*));

    // inicialmente todas as listas são vazias
    for(int i = 0; i < num_salas; i++){
        tripulante.list_adj[i] = NULL;
        impostor.list_adj[i] = NULL;
    }

    //realizando a leitura da tripla (origem, destino, tam coreedor)
    int u, v;
    double d;
    for(int i=0; i< lig_corredor; i++)
    {
        scanf("%d %d %lf", &u, &v, &d);
        add_aresta(&tripulante, u, v, d);
        add_aresta(&impostor, u, v, d);
    }

    //leitura das duplas (u,v)
    u=0, v=0;
    for(int i=0; i< lig_tubula; i++)
    {
        scanf("%d %d", &u, &v);
        add_aresta(&impostor, u, v, 1);
    }

    double  dist_tripulante[num_salas], dist_impostor[num_salas];
    dijkstra(&tripulante, num_salas, dist_tripulante);
    dijkstra(&impostor, num_salas, dist_impostor);
    
    int aux;
    for(int j = 0; j < qtd_consult; j++){
        scanf("%d", &aux);
        if (dist_tripulante[aux] <= dist_impostor[aux])
        printf("victory\n");
        else
            printf("defeat\n");
    }
    return 0;
}