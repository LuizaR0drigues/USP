//cole isso em primeiro lugar  na global
#define MAX_SCORES 5

void rank(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error na abertura de arquivo %s\n", filename);
        return;
    }

    int rank[MAX_SCORES];
    int numScores = 0;
    int score;
    while (fscanf(file, "%d", &score) != EOF) {
        rank[numScores] = score;
        numScores++;
    }

    fclose(file);

    // organiza o rank
    int i, j;
    for (i = 0; i < numScores - 1; i++) {
        for (j = 0; j < numScores - i - 1; j++) {
            if (rank[j] < rank[j + 1]) {
                int temp = rank[j];
                rank[j] = rank[j + 1];
                rank[j + 1] = temp;
            }
        }
    }

    // novos top 5
    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    for (i = 0; i < MAX_SCORES && i < numScores; i++) {
        fprintf(file, "%d\n", rank[i]);
    }

    fclose(file);
}

int main() {
    //coloque isso no final do codigo main
    const char* filename = "rank.txt";

    rank(filename);

    return 0;
}
