//Luiza Rodrigues Cardoso -- Nusp: 14593332
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




// cada aluno
struct Aluno
{
    char name[50];
    float media;
    int dp;
};

void swap(struct Aluno *a, struct Aluno *b)
{
    struct Aluno temp = *a;
    *a = *b;
    *b = temp;
}


void selection_sort(struct Aluno *vetorA, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int maior = i;

        for (int j = i + 1; j < n; j++)
        {
            // compara alunos por média de notas, quantidade de reprovações e nome
            if (vetorA[j].media > vetorA[maior].media ||
                    (vetorA[j].media == vetorA[maior].media && vetorA[j].dp < vetorA[maior].dp) ||
                    (vetorA[j].media == vetorA[maior].media && vetorA[j].dp == vetorA[maior].dp && strcmp(vetorA[j].name, vetorA[maior].name) < 0))
            {
                maior = j;
            }
        }

        if (maior != i)
        {
            swap(&vetorA[i], &vetorA[maior]);
        }
    }
}



// Merge Sort
void merge(struct Aluno *vetor, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;
    struct Aluno vet1[n1], vet2[n2];//os dois subvetores

    for (int i = 0; i < n1; i++)
        vet1[i] = vetor[l + i];
    for (int j = 0; j < n2; j++)
        vet2[j] = vetor[m + 1 + j];

    int i = 0, j = 0, k = l;
    //realizando as comparações e movendo os elemntos para vet1 e vet2
    while (i < n1 && j < n2)
    {
        if (vet1[i].media > vet2[j].media ||
                (vet1[i].media == vet2[j].media && vet1[i].dp < vet2[j].dp) ||
                (vet1[i].media == vet2[j].media && vet1[i].dp == vet2[j].dp && strcmp(vet1[i].name, vet2[j].name) < 0))
        {
            vetor[k] = vet1[i];
            i++;
        }
        else
        {
            vetor[k] = vet2[j];
            j++;
        }
        k++;
    }



//concatenado os elemntos no vetor original
    while (i < n1)
    {
        vetor[k] = vet1[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        vetor[k] = vet2[j];
        j++;
        k++;
    }
}

void merge_sort(struct Aluno *vetor, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
//usando recursão para subdividir o vetor em dois
        merge_sort(vetor, l, m);
        merge_sort(vetor, m + 1, r);
//realizando a ordenação do vetor
        merge(vetor, l, m, r);
    }
}

int main()
{
    int t, dp =0, num_bolsas =0;
    float media =0;
    char nome[50];//T e o tipo de ordenacao
    scanf("%d", &t);

    int na, nbolsas; // na e o numero de alunos e nbolsas e o numero de bolsas
    scanf("%d %d", &na, &nbolsas);

    // aloca memoria para armazenar os dados dos alunos
    struct Aluno aux;
    struct Aluno *aluno = malloc(na * sizeof(struct Aluno));

    // le
    for (int i = 0; i < na; i++)
    {
        scanf("%f %d %s", &media, &dp,nome);
        if( dp <= 10 )
        {
            aluno[i].media = media;
            strcpy(aluno[i].name, nome);
            aluno[i].dp = dp;
            num_bolsas++;
        }
    }

    // Ordena os alunos de acordo com T
    if (t == 1)
    {
        selection_sort(aluno, na);
    }
    else if (t == 2)
    {
        merge_sort(aluno, 0, na - 1);
    }

   //  DIstribuição de bolsas

    if (na < nbolsas)
    nbolsas = na; // Caso em que há mais bolsas do que alunos
else {
    aux = aluno[num_bolsas - 1]; // Atribuir o último aluno às bolsas

    for (int i = num_bolsas - 2; i > 0; i--) {
        if (aluno[i].media == aux.media && aluno[i].dp == aux.dp)
            nbolsas++;
        else
            aux = aluno[i];
    }
}

printf("%d\n", nbolsas);


    // alunos escolhidos
    int restoBolsas = 0;
    for (int i = 0; i < na && restoBolsas < nbolsas; i++) {

            printf("%s\n",aluno[i].name);
            restoBolsas++;
    }


        free(aluno);



        return 0;
    }
