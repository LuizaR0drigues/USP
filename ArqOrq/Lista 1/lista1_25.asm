# Estruturas de Controle
# Leitura de int e verificação se é Primo

	.data
	.align 0
str_wcm: .asciz "Digite um número positivo e não nulo: "
str_num: .asciz "O número "
str_nep: .asciz " é PRIMO\n"
str_nnp: .asciz " NAO é primo\n"


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
	addi a1, zero, 1
	
	#impressao de str
	addi a7, zero, 4
	la a0, str_num
	ecall
	
	#impressao de str
	addi a7, zero, 1
	add a0, zero, s0
	ecall
	
	#caso basico
	ble s0, a1, nao_primo # se menor que 1, nao é
	
	#t0 = 2
	addi t0, zero, 2
loop:
	#estrutura condicional
	#se to >- N é primo
	bge t0, s0, primo
	
	rem t1, s0, t0 #t1 = N % t0
	beq t1, zero, nao_primo #se o resto == 0. não é

	addi t0, t0, 1
	j loop
	
nao_primo:
	
	#impressao de str
	addi a7, zero, 4
	la a0, str_nnp
	ecall
	
	j fim

primo: 
	#impressao de str
	addi a7, zero, 4
	la a0, str_nep
	ecall
	
	j fim
fim:
	#impressao de str
	addi a7, zero, 10
	ecall
	

	
	
	
	
	
	
	
	