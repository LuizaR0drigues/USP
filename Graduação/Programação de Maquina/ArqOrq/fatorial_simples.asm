#Fatorial
	.data
	.align 0 
str_00: .asciz "Entre com um número inteiro: "
str_01: .asciz "O fatorial de "
str_02: .asciz " é "
str_er: .asciz "O numero precisa ser >=0. Tente novamente\n"

	.text 
	.align 2
	.globl main
main: 
	#imprimindo a primeira string
loop_oi:
addi a7, zero, 4
	la a0, str_00
	ecall
	
	#lendo o numero digitado
	addi a7, zero, 5
	ecall
	
	#verificando se o numero é nao nulo e positivo
	bge a0, zero, continua
	
	addi a7, zero, 4
	la a0, str_er
	ecall
	
	j loop_oi
	
	
continua:
	#passando o numero digitado para s0
	add s0, a0, zero
	jal fatorial
	
	#imprimindo o resultado
	addi a7, zero, 4
	la a0, str_01 #string
	ecall
	
	addi a7, zero, 1 #serviço de impressao de inteiro
	add a0, zero, s0 #imprime n
	ecall
	
	addi a7, zero, 4 #imprime string
	la a0, str_02 
	ecall
	
	addi a7, zero, 1
	add a0, zero, a1 #o resultado
	ecall
	
	#finaliza
	addi a7, zero, 10
	ecall
#a0 = n
#a1 = n!
fatorial:
	add t0, zero, a0 #to = n
	#caso base
	li a1, 1 #result = 1
	#caso n=0, retorna 1
	beq t0, zero, fim_fat
	
loop_fat:
	mul a1, a1, t0 #result *= t0
	addi t0, t0, -1 #pega o antecesspr t0--
	
	bgt t0, zero, loop_fat # contiua até zeo
	
fim_fat: 
	jr ra
	
