#Fundamentos de Assembly
#Leitura de 2 Inteiros
#Soma e impressao deles
	.data
	.align 0 #alinhando pra string
str_cm1: .asciz "\nDigite o primeiro número inteiro: "
str_cm2: .asciz "\nDigite o segundo número inteiro: "
str_o00: .asciz "\nO número { "
str_o01: .asciz " } é MAIOR que {"
str_o10: .asciz " } é MENOR que {"
str_o11: .asciz " }"
str_out: .asciz "Os número digitados são iguais!"

	.text
	.align 2 #alinhando pra palavra/inteiro
	.globl main
main:
	#imprimindo a mensagem
	addi a7, zero, 4
	la a0, str_cm1
	ecall
	
	#lendo o primerio numero do teclado - syscall 5
	addi a7, zero, 5
	ecall #a0 recebeu o valor
	
	#copiando o valro pra um local seguro
	add s0,  a0, zero
	
	#imprimindo a mensagem
	addi a7, zero, 4
	la a0, str_cm2
	ecall
	
	#lendo o segundo numero do teclado - syscall 5
	addi a7, zero, 5
	ecall #a0 recebeu o valor
	
	#copiando o valro pra um local seguro
	add s1,  a0, zero
	
	#possiveis casos
	#igualdade
	beq s0, s1, iguais
	
	addi a7, zero, 4
	la a0, str_o00
	ecall
	
	#printando o numero 2
	addi a7, zero, 1
	add a0, zero, s0
	ecall
	
	#o primeiro é maior s0> s1
	bgt s0, s1, menor
	
	
	#caso do segundo ser maior
	#s1 > s0
	j maior
	

	
menor:
	#printamdp a msg
	addi a7, zero, 4
	la a0, str_o01
	ecall
	 j continua

maior:
	#printamdp a msg
	addi a7, zero, 4
	la a0, str_o10
	ecall
	
	j continua

continua:
	#printando o numero 2
	addi a7, zero, 1
	add a0, zero, s1
	ecall
	
	#printamdp a msg
	addi a7, zero, 4
	la a0, str_o11
	ecall
	
	j finaliza

iguais: 
	#printamdp a msg
	addi a7, zero, 4
	la a0, str_out
	ecall
	
	j finaliza	

finaliza:	
	#finalizando o programa com o serviço 10
	addi a7, zero, 10
	ecall
	
	