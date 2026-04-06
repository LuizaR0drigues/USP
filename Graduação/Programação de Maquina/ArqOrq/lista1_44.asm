# Parte 4 : Vetores e Memória
# Armazenamento na memoria e Recuperação dos dados
# Soma dos N elementos de um vetor

	 .data
	 .align 0
str_wcm: .asciz "\nDigite a quantidade de numéros que você gostaria de armazenar: "
str_w2:  .asciz "Digite o número: "
str_val: .asciz "Número armazenado: "
str_str: .asciz "\n"
str_fim: .asciz "\nA soma de todos os elementos é: "
#debug
str_err: .asciz "\nErro na alocação de memória! "

	 .text
	 .align 2
	 .globl main
	 
main:	
	addi a7, zero, 4
	la a0, str_wcm
	ecall
	
	#Lendo a qtd de elementos do vetor
	addi a7, zero, 5
	ecall
	
	#salvando a qtd em s0
	add s0, zero, a0
	
	#calculando a qtd de bytes necessarios
	addi t0, zero, 4
	mul  a0, s0,  t0
	
	#alocando a memoria
	addi a7, zero, 9
	ecall
	
	#erro de alocacao
	beq a0, zero, erro
	
	#ptr necessarios aos procedimentos
	#t1: ptr atual 
	add t1, zero, a0
	
	#t2: inicio do vetor
	add t2, zero, a0
	
	#t5: contador de leitura
	add t5, zero, s0
	
	#acumulador
	add t4, zero, zero
	
loop_read:
	beq s0, zero, loop_recupera
	
	#pede que o user digite a sequencia
	addi a7, zero, 4
	la a0, str_w2
	ecall
	
	#le o inteiro
	addi a7, zero, 5
	ecall
	
	#escreve o conteudo de a0 na posicao atual (offset+qtd)
	sw a0, 0(t1)
	
	#avança o ponteiro na memoria
	addi t1, t1, 4
	
	#decrementa o contador
	addi s0, s0, -1
	
	j loop_read
	
loop_recupera:
	
	beq t5, zero, result_soma
	
	#Imprime msg 
	addi a7, zero, 4
	la a0, str_val
	ecall 
	
	#busca o valor na memoria e armazena em t3
	lw t3, 0(t2)
	
	#guarda o conteudo em a0
	add a0, zero, t3
	
	#realiza o somatorio
	add t4, t4, t3
	
	#imprime na tela
	addi a7, zero, 1
	ecall
	
	#Imprime \n
	addi a7, zero, 4
	la a0, str_str
	ecall 
	
	#avança na memoria
	addi t2, t2, 4
	
	#decrementa o contador
	addi t5, t5, -1
	
	j loop_recupera
	
result_soma:
	#imprime a msg
	addi a7,zero, 4
	la a0, str_fim
	ecall
	
	#Imprime o valor do somatorio
	add a0, zero, t4
	addi a7, zero, 1
	ecall
	
	j fim
fim: 	
	
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
	
	
	
	
	