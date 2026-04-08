#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

void binarioNaTela(char *nomeArquivoBinario) { /* Você não precisa entender o código dessa função. */

	/* Use essa função para comparação no run.codes. Lembre-se de ter fechado (fclose) o arquivo anteriormente.
	*  Ela vai abrir de novo para leitura e depois fechar (você não vai perder pontos por isso se usar ela). */

	unsigned long i, cs;
	unsigned char *mb;
	size_t fl;
	FILE *fs;
	if(nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
		fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela): não foi possível abrir o arquivo que me passou para leitura. Ele existe e você tá passando o nome certo? Você lembrou de fechar ele com fclose depois de usar?\n");
		return;
	}
	fseek(fs, 0, SEEK_END);
	fl = ftell(fs);
	fseek(fs, 0, SEEK_SET);
	mb = (unsigned char *) malloc(fl);
	fread(mb, 1, fl, fs);

	cs = 0;
	for(i = 0; i < fl; i++) {
		cs += (unsigned long) mb[i];
	}
	printf("%lf\n", (cs / (double) 100));
	free(mb);
	fclose(fs);
}

void scan_quote_string(char *str) {

	/*
	*	Use essa função para ler um campo string delimitado entre aspas (").
	*	Chame ela na hora que for ler tal campo. Por exemplo:
	*
	*	A entrada está da seguinte forma:
	*		nomeDoCampo "MARIA DA SILVA"
	*
	*	Para ler isso para as strings já alocadas str1 e str2 do seu programa, você faz:
	*		scanf("%s", str1); // Vai salvar nomeDoCampo em str1
	*		scan_quote_string(str2); // Vai salvar MARIA DA SILVA em str2 (sem as aspas)
	*
	*/

	char R;

	while((R = getchar()) != EOF && isspace(R)); // ignorar espaços, \r, \n...

	if(R == 'N' || R == 'n') { // campo NULO
		getchar(); getchar(); getchar(); // ignorar o "ULO" de NULO.
		strcpy(str, ""); // copia string vazia
	} else if(R == '\"') {
		if(scanf("%[^\"]", str) != 1) { // ler até o fechamento das aspas
			strcpy(str, "");
		}
		getchar(); // ignorar aspas fechando
	} else if(R != EOF){ // vc tá tentando ler uma string que não tá entre aspas! Fazer leitura normal %s então, pois deve ser algum inteiro ou algo assim...
		str[0] = R;
		scanf("%s", &str[1]);
	} else { // EOF
		strcpy(str, "");
	}
}

/*  
    Converte o nome do dinossauro para long

    OBS:   retorna -1 se o primeiro caracter é '*'

    COMO FUNCIONA:

        Para converter os nomes para long e garantir que nomes diferentes 
        deem números diferentes interpretamos eles como números em base 6

        Um número L com n digitos dI em base 6 é escrito como:

            L = d0 * 6^0 + d1 * 6^1 + d2 * 6^2 + d3 * 6^3 + ... + dn * 6^n-1

        Nota-se que estamos escrevendo do digito menos significativo para o 
        mais significativo
*/
long converteNome(char* str) {
    /* O registro que tem essa string como chave foi removido */
    if(str[0] == '*')
        return -1;

    /* Começamos com o primeiro digito na ordem de 6^0 = 1 */
    long power = 1;

    /* Faz a conversão char por char para chegar ao resultado */
    long result = 0;
    for(int i = 0; i < strlen(str); i++) {
        int cur_digit;
        /* Checa pelas letras minúsculas e as converte para números */
        if(str[i] >= 'a' && str[i] <= 'z')
            cur_digit = str[i] - 'a';
        /* Checa pelas letras maiúsculas e as converte para números */
        else if(str[i] >= 'A' && str[i] <= 'Z')
            cur_digit = str[i] - 'A';

        /*
            Multiplica o digito atual pelo ordem da posição atual
            e adiciona no resultado
            Primeira posição:   6^0 = 1
            Segunda posição:    6^1 = 6
            Terceira posição:   6^2 = 36
            Quarta posição:     6^3 = 216
            Quinta posição:     6^4 = 1.296
        */
        result += cur_digit * power;

        /* Aumenta a ordem atual */
        power *= 6;
    }

    return result;
}