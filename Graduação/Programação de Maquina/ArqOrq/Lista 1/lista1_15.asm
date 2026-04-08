#Fundamentos de Assembly
#Leitura de Inteiro
#Par ou Impar
	.data
	.align 0 #alinhando pra string
str_cmd: .asciz "\nDigite um número inteiro: "
str_o00: .asciz "\nO número digitado { "
str_o01: .asciz " } é PAR"
str_o10: .asciz "\nO número digitado { "
str_o11: .asciz " } é ÍMPAR"
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
	add t0,  a0, zero
	
	#nosso divisor
	addi t1, zero, 2
	
	#realizando a divisao
	#T2: resto da 
	div t2, t0, t1 #quociente
	rem t3, t0, t1 #resto
	
	#verificando a paridade
	beq t3, zero, par
	
	j impar
par:
	#printamdp a msg
	addi a7, zero, 4
	la a0, str_o00
	ecall
	
	#printando o numero
	addi a7, zero, 1
	add a0, zero, t0
	ecall
	
	#printamdp a msg
	addi a7, zero, 4
	la a0, str_o01
	ecall
	
	j finaliza

impar:
	#printamdp a msg
	addi a7, zero, 4
	la a0, str_o10
	ecall
	
	#printando o numero
	addi a7, zero, 1
	add a0, zero, t0
	ecall
	
	#printamdp a msg
	addi a7, zero, 4
	la a0, str_o11
	ecall
	
	j finaliza

finaliza:
	#finalizando o programa com o serviço 10
	addi a7, zero, 10
	ecall
	