#Fundamentos de Assembly
#Leitura de Inteiro

	.data
	.align 0 #alinhando pra string
str_cmd: .asciz "\nDigite um número inteiro: "
str_out: .asciz "\nO número digitado foi: "

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
	
	#copiando o valro pra um local seguro
	add s0,  a0, zero
	
	#printamdp a msg
	addi a7, zero, 4
	la a0, str_out
	ecall
	
	#printando o numero
	addi a7, zero, 1
	add a0, zero, s0
	ecall
	
	#finalizando o programa com o serviço 10
	addi a7, zero, 10
	ecall
	
	