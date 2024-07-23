//  ------------------------------- Caue Sordi Paulino , n USP: 14564520 -------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




// cada aluno
struct Student {
    char name[50];
    float average_grade;
    int reprovations;
};




void swap(struct Student *a, struct Student *b) {
    struct Student temp = *a;
    *a = *b;
    *b = temp;
}


void selection_sort(struct Student *students, int n) {
    for (int i = 0; i < n - 1; i++) {
        int max_idx = i;

        for (int j = i + 1; j < n; j++) {
            // compara alunos por média de notas, quantidade de reprovações e nome
            if (students[j].average_grade > students[max_idx].average_grade ||
                (students[j].average_grade == students[max_idx].average_grade && students[j].reprovations < students[max_idx].reprovations) ||
                (students[j].average_grade == students[max_idx].average_grade && students[j].reprovations == students[max_idx].reprovations && strcmp(students[j].name, students[max_idx].name) < 0)) {
                max_idx = j;
            }
        }

        if (max_idx != i) {
            swap(&students[i], &students[max_idx]);
        }
    }
}



// da merge em dois subarrays de arr[]
void merge(struct Student *arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    struct Student L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        if (L[i].average_grade > R[j].average_grade ||
            (L[i].average_grade == R[j].average_grade && L[i].reprovations < R[j].reprovations) ||
            (L[i].average_grade == R[j].average_grade && L[i].reprovations == R[j].reprovations && strcmp(L[i].name, R[j].name) < 0)) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }




    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(struct Student *arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

int main() {
    int T; //T e o tipo de ordenacao
    scanf("%d", &T);

    int N, M; // N e o numero de alunos e M e o numero de bolsas
    scanf("%d %d", &N, &M);

    // aloca memoria para armazenar os dados dos alunos
    struct Student *students = malloc(N * sizeof(struct Student));

    // le
    for (int i = 0; i < N; i++) {
        scanf("%f %d %s", &students[i].average_grade, &students[i].reprovations, students[i].name);
    }

    // Ordena os alunos de acordo com T
    if (T == 1) {
        selection_sort(students, N);
    } else if (T == 2) {
        merge_sort(students, 0, N - 1);
    }

    //  numero de alunos escolhidos
    // arrumar bolsas extras
    int num_bolsas = 0;
    for (int i = 0; i < N; i++) {
        if (students[i].reprovations <= 10) {
            num_bolsas++;
        }
    }
    printf("%d\n", M);





    // alunos escolhidos
    int restado_bolsas = 0;
    for (int i = 0; i < N && restado_bolsas < M; i++) {
        if (students[i].reprovations <= 10) {
            printf("%s\n",students[i].name);
            restado_bolsas++;
        }
    }







    free(students);



    return 0;
}
