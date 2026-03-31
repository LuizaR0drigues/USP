#Fundamentos de Assembly
#Leitura de Inteiro
#Dobra e trplo
	.data
	.align 0 #alinhando pra string
str_cmd: .asciz "\nDigite um número inteiro: "
str_ou1: .asciz "\nO dobro do número digitado é: "
str_ou2: .asciz "\nO triplo do número digitado é: "

	.text
	.align 2 #alinhando pra palavra/inteiro
	.globl main
main:
	#imprimindo a mensagem
	addi a7, zero, 4
	la a0, str_cmd
	ecall
	
	#lendo um numero do teclado - syscall 5
	addi a7, zero, 5
	ecall #a0 recebeu o valor
	
	#copiando o valor pra um local seguro
	add t0,  a0, zero
	
	#realizando os calculos
	#dobro
	mul t1, t0,t0
	
	#trplo
	mul t2, t1, t0
	
	#printamdp a msg
	addi a7, zero, 4
	la a0, str_ou1
	ecall
	
	#printando o numero
	addi a7, zero, 1
	add a0, zero, t1
	ecall
	
	#printamdp a msg
	addi a7, zero, 4
	la a0, str_ou2
	ecall
	
	#printando o numero
	addi a7, zero, 1
	add a0, zero, t2
	ecall
	
	#finalizando o programa com o serviço 10
	addi a7, zero, 10
	ecall
	
	