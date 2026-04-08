#Fundamentos de Assembly
#Leitura de 2 Inteiros
#Soma e impressao deles
	.data
	.align 0 #alinhando pra string
str_cm1: .asciz "\nDigite o primeiro número inteiro: "
str_cm2: .asciz "\nDigite o segundo número inteiro: "
str_out: .asciz "\nA soma dos número é igual a: "

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
	
	#printamdp a msg
	addi a7, zero, 4
	la a0, str_out
	ecall
	
	#realizando a soma
	add s2, s0, s1
	
	#printando o numero
	addi a7, zero, 1
	add a0, zero, s2
	ecall
	
	#finalizando o programa com o serviço 10
	addi a7, zero, 10
	ecall
	
	