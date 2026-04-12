/**********************************************************************************
Luiza Rodrigues Cardoso - 14593332
Trabalho 02 - Potencia // Estrutura de Dados 2
Potência de n elevado a (k) - usar mod
*********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MOD 1000

long long pot_simples(long long base, int expo){
    long long res =1;
    base %= MOD;

    for(int i=0; i< expo; i++)
    {
        res = (res*base) %MOD;
    }

    return res;
}

long long eleva_dez(long long valor, int dig_dir){
    long long res = valor;
    //para cada digito da direita, eleva o acumulador à 10æ potencia
    for(int i=0; i< dig_dir; i++)
    {
        res = pot_simples(res, 10);
    }
    return res;
    
}

double potencia(double base, double vetor[], int inicio, int final){
    //case base:vetor unitari - unico digitoo
    if(inicio == final){
        //chamado a potencia de base^digito
        return pot_simples(base, vetor[inicio]);
    }

    //calculando o meio
    int meio = (inicio)+(final-inicio)/2;

    //DIVIDE o vetor em duas partes de forma recursiva
    long long esquerda = potencia(base,vetor, inicio, meio); //primeira metade
    long long direita = potencia(base,vetor, meio+1, final); //segunda parte

    //expoente da pot de 10
    int tamDir = final - meio;
    //CONQUISTA
    //fazemos (base^esquerda)(10^Tamanho da direita)*(base^direita)
    long long fator = eleva_dez(esquerda, tamDir) % MOD;

    return(fator * direita ) % MOD;
}


int main(){
    //dados 
    double base = 0, expo = 0;
    long long pot;
    char carac = ' ';
    double *vetor = NULL;
    int cont = 0; //guarda o tamanho do vetor
    
    //leitura
    scanf("%lf ", &base);
    if(base > 0 && base <= 99){
    //transformando o expoente em vetor
    while(1){
        scanf("%c", &carac);
        if(carac == '\n'  || carac == '\r')
        {
            break;
        }
        //usa um vetor temporario para alocar a memoria 
        double *temp = (double*)realloc(vetor, (cont + 1) * sizeof(double));
        if(temp != NULL){
            vetor = temp;
            //subtrai '0' para achar o valor numerico
            vetor[cont] = (int)carac - '0';
            cont++;
        }
        else{
            break;
        } 
    }

    pot = potencia(base, vetor, 0, cont-1);
    printf("%lld\n", pot);
    free(vetor);
    }  
    else{
        printf("Valor fora dos limites!\n");
    }
    return 0;
}