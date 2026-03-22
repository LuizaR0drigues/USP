#codigo desenvolvida pela professora
				.data # diretiva p/ início do seg de dados
		.align 2 # alinha a memória para armazenar inteiro
vlr_inteiro: 	.word 157
		.align 0 # alinha a memória para armazenar caractere
string: 	.asciz "Hello World"
		.text # diretiva p/ início do segmento de texto
		.globl main # diretiva p/ usar rotulo em outro prog.
main: # rótulo para ponto de entrada no processo
		.align 2 # alinha a memória para armazenar as instruções de 32 bits
		addi a7, x0, 4 # Código do serviço 4 (impressão de string)
		la a0, string # Enderço do 1o byte da string
		ecall # Chamada linux
		addi a7, x0, 10 # código do serviço que encerra
		ecall # chamada linux para terminar o programa