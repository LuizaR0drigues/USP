# Parte 4 : Vetores e Memória
# Leitura de Inteiro e armazenamento na memoria

	.data
	.align 0
str_wcm: .asciz "Digite a quantidade de numéros que você gostaria de armazenar: "
str_w2:  .asciz "Digite o número: "

str_fim: .asciz "Os números foram armazenados na memória!"
#debug
str_err: .asciz "Erro na alocação de memória! "

	.data
	.align 2
	.globl main
main:
	#imprime  qtd
	addi a7, zero, 4
	la a0, str_wcm
	ecall
	
	#leitura de qtd
	addi a7, zero, 5
	ecall
	
	#salvando um copia pro contador
	addi s0, zero, a0
	
	#calculando a qtd de bytes
	# a0 =  (s0 * 4) bytes
	addi t0, zero, 4
	mul a0, s0, t0
	
	#alocando a memoria
	addi a7, zero, 9
	ecall
	
	#em caso de erro na alocação, finaliza
	beq a0, zero, erro
	
	#caso sucesso, percorre loop para guardar
	#t1 =  primeiro endereço que o ponteiro vai mostrar
	addi t1, zero, a0
loop:
	beq s0, zero, fim
	
	#pede o numero
	addi a7, zero, 4
	la a0, str_w2
	ecall
	
	#le o inteiro em a0
	addi a7, zero, 5
	ecall
	
	#escreve o conteudo de a0 na posicao offset+qtd
	sw a0, 0(t1)
	
	#avança o ponteiro
	addi t1, t1, 4
	
	#decrementa o contador
	addi s0, s0, -1
	
	j loop
	
fim: 	
	#carrega a msg de sucesso
	addi a7, zero, 4
	la a0, str_fim
	ecall
	
	#finaliza
	addi a7, zero, 10
	ecall

 erro:  
	#carrega a msg de erro
	addi a7, zero, 4
	la a0, str_err
	ecall
	
	#finaliza
	addi a7, zero, 10
	ecall
	
	
	
	