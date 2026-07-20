/**********************************************************************************
Luiza Rodrigues Cardoso - 14593332
Trabalho 2.2 - Among Us // Estrutura de Dados 2
Estratégia adotada -> Grafo não-direcionado e ponderado; caminhos minimos
*********************************************************************************/
#include <stdio.h>
#include <stdlib.h>



int main(){
    //leitura dos dados
    //num_salas, num_ligações por corredores, num_ligações por tuulações e qunatidade de consultas
    int num_salas, lig_corredor, lig_tubula, qtd_consult;
    
    scanf("%d %d %d %d", &num_salas, &lig_corredor, &lig_tubula, &qtd_consult);

    //temos 3*lig_corredor que decrevem as ligações das salas por meio do corredor de comprimento d - (sala, corredor, comprimento)
    int (*sala_per_corredor)[3] = malloc(lig_corredor * sizeof(*sala_per_corredor));

    for(int i=0; i<lig_corredor; i++){
        for(int j =0; j<3; j++){
            scanf("%d", &sala_per_corredor[i][j]);
        }
    }

    //ligações sala por meio de tubos de ventilação
    int (*sala_per_ventila)[2] = malloc(lig_tubula * sizeof(*sala_per_ventila));

    for(int i=0; i< lig_tubula; i++){
        for(int j=0; j<2; j++){
            scanf("%d", &sala_per_ventila[i][j]);
        }
    }

    int visto = (int*)malloc(qtd_consult * sizeof(int*));
    for(int k=0; k<qtd_consult; k++)
    {
        scanf("%d", &visto[k]);
    }

    //estrategia
    

    return 0;
}