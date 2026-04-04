# Estruturas de Controle
# Leitura de int e somatorio da sequencia 

	.data
	.align 0
str_wcm: .asciz "Digite um número positivo e não nulo: "
str_seq: .asciz "O somatório de 1 até N: \n"
str_plu: .asciz " + "
str_eq: .asciz " = "
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
	addi t0, zero, 0  #contador
	addi t1, zero, 0 #auxiliar
	
verifica:
	#estrutura condicional
	#enquanto t0 < s0, imprima o somatorio
	bge t0, s0, fim

	
loop_print:
	
	addi t0, t0, 1
	
	#soma += t0
	add t1, t1, t0
	
	#imprime int
	addi a7, zero, 1
	add a0, zero, t0
	ecall
	
	#impreme +
	addi a7, zero, 4
	la a0, str_plu
	ecall
	
	j verifica
	
fim:	
	#imprime =
	addi a7, zero, 4
	la a0, str_eq
	ecall
	
	#imprime soma final
	addi, a7, zero, 1
	add a0, zero, t1
	ecall
	  
	#finalizando
	addi a7, zero, 10
	ecall
	
	
	
	
	