#Parte 5 - FUnções e Pilha
#Uma função que recebe dois numeros e retorna a soma

	 .data
	 .align 0
str_num1: .asciz "\nDigite o primeiro numero: "
str_num2: .asciz "\nDigite o segundo numero: "
str_sum: .asciz "A soma de "
str_sym: .asciz " + "
str_and: .asciz " é "

	 .text
	 .align 2
	 .globl main
main:	
	#recebendo os numeros
	addi a7, zero, 4
	la a0, str_num1
	ecall
	
	#primeiro numero
	addi a7, zero, 5
	ecall
	add s1, zero, a0
	
	#recebendo os numeros
	addi a7, zero, 4
	la a0, str_num2
	ecall
	
	#segundo numero
	addi a7, zero, 5
	ecall
	add s2, zero, a0 
	
	#chamando a função de soma
	add a0, zero, s1 #primeiro argumento
	add a1, zero, s2 #segundo argumento 
	jal ra, soma
	
	#salvando o valor de retorno 
	add s3, zero, a0
	
	#imprimindo o valor
	addi a7, zero, 4
	la a0, str_sum
	ecall 
	
	add a0, zero, s1
	addi a7, zero, 1
	ecall
	
	addi a7, zero, 4
	la a0, str_sym
	ecall
	
	add a0, zero, s2
	addi a7, zero, 1
	ecall
	
	addi a7, zero, 4
	la a0, str_and
	ecall
	
	add a0, zero, s3
	addi a7, zero, 1
	ecall
	
	#finaliza
	addi a7, zero, 10
	ecall
	

soma:
	#empilhando
	#12: endereço de retorno e 2 parametros
	addi sp, sp, -8
	sw s0, 0(sp) #salvando os paramteros
	sw ra, 4(sp) #guardando o end de retorno
	

	#resultado - soma dos parametros
	add a0, a0, a1 
	
	#desempilhando 
	lw s0, 0(sp)
	lw ra, 4(sp)
	
	
	addi sp, sp, 8 #ptr de volta ao inicio da heap
	
	jr ra#volta pro main
	