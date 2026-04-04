# Estruturas de Controle
# Leitura de int e impressao reversa em loop

	.data
	.align 0
str_wcm: .asciz "Digite um número positivo e não nulo: "
str_seq: .asciz "Esse número é dado pela sequencia: \n"
str_num: .asciz "\n"
	.text 
	.align 2
	.globl main
main: 
	#impressao de str
	addi a7, zero, 4
	la a0, str_wcm
	ecall
	
	#leitura do inteiro
	addi a7, zero, 5
	ecall
	
	#transferindo para s0
	add s0, zero, a0
	
	#impressao de str
	addi a7, zero, 4
	la a0, str_seq
	ecall
	
	#passando o N pro decrementador
	add t0, zero, s0
	
verifica:
	#estrutura condicional
	#enquanto t0 != 0, imprima o cont-=1
	bne t0, zero, loop_print

	#finalizando
	addi a7, zero, 10
	ecall
	
loop_print:
	
	#imprimindo o numero 1- N
	addi a7, zero, 1
	add a0, zero, t0
	ecall
	
	#impressao de str
	addi a7, zero, 4
	la a0, str_num
	ecall
	
	#decrementa
	#cont -= 1
	addi t0, t0, -1
	
	j verifica
	
	
	
	
	
	
	
	
	