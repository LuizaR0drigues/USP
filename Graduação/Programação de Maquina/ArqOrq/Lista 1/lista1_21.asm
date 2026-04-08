# Estruturas de Controle
# Leitura de int e impressao em loop

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
	add s0, zero ,a0
	
	#impressao de str
	addi a7, zero, 4
	la a0, str_seq
	ecall
	
	#usando um contador
	addi t0, zero, 0
verifica:
	#estrutura condicional
	#enquanto t0> s0, imprima o cont+=1
	blt t0, s0, loop_print

	#finalizando
	addi a7, zero, 10
	ecall
	
loop_print:
	#cont += 1
	addi t0, t0, 1
	
	#imprimindo o numero 1- N
	addi a7, zero, 1
	add a0, zero, t0
	ecall
	
		#impressao de str
	addi a7, zero, 4
	la a0, str_num
	ecall
	
	j verifica
	
	
	
	
	
	
	
	
	