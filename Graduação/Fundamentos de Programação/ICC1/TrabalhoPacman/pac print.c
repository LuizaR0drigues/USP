

#include <stdio.h>
/*vamos ter variaveia vazias no int main logo depois vamos ler eo arquivo e pegar os valores
depois vamos lidar com essas infos e escrefver*/
void bbsrt(int rank[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (rank[j] < rank[j + 1]) {
                int temp = rank[j];
                rank[j] = rank[j + 1];
                rank[j + 1] = temp;
            }
        }
    }
}

void topcinco(int rank[], int n, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s\n", filename);
        return;
    }
    for (int i = 0; i < n && i < 5; i++) {
        fprintf(file, "%d\n", rank[i]);
    }

    fclose(file);
}

int main() {
    int rank[] = {10, 5, 15, 8, 3};
    int n = sizeof(rank) / sizeof(rank[0]);

    bbsrt(rank, n);

    topcinco(rank, n, "rank.txt");

    return 0;
}

