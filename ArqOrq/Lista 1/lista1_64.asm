#Parte 6 - Manipulação de String a partir de funções
#Strcmp - comparação de string

	.data
	.align 0
str_st1: .asciz "Digite a primeira string: "
str_st2: .asciz "DIgite a segunda string: "
str_rt1: .asciz "As strings são IGUAIS!" 
str_rt2: .asciz "As strings NÂO são IGUAIS!" 
	
	 .align 0
buffer1: .space 100
buffer2: .space 100

	.text
	.align 2
	.globl main
main:	
	addi a7, zero, 4
	la a0, str_st1
	ecall
	
	#leitura da primeira string
	la a0, buffer1
	addi a1, zero, 100 #Max de characteres
	addi a7, zero, 8
	ecall
	
	#salvando 
	add s0, zero, a0
	
	addi a7, zero, 4
	la a0, str_st2
	ecall
	
	#leitura da segunda string
	la a0, buffer2
	addi a1, zero, 100 #Max de characteres
	addi a7, zero, 8
	ecall
	
	#t1 e t2: regs temporarios para deslocamento 
	add t1, zero, s1
	add t2, zero, s2
	
	#salvando 
	add s1, zero, a0
	
	la t1, buffer1 #t1 aponta para o inicio do bf1
	la t2, buffer2 #t2 aponta para o inioc do bf2
	jal compara
	
	
finaliza:
	addi a7, zero, 10
	ecall

compara:
loop_compara:
	#perccorendo a string
	lbu t3, 0(t1) #1 byte da primeira string
	lbu t4, 0(t2) #1 byte da segunda string
	
	#se os caracteres forem diferentes, pula pra str_diff
	bne t3, t4, str_diff
	
	#se forem iguais, verifica se chegou no z0
	beq t3, zero, str_iguais
	beq t4, zero, str_iguais
	
	#avança 1 char no endereço das string
	addi t1, t1, 1
	addi t2, t2, 1
	
	j loop_compara
	
str_diff:
	
	addi a7, zero, 4
	la a0, str_rt2
	ecall
	
	j finaliza
	
str_iguais:
	addi a7, zero, 4
	la a0, str_rt1
	ecall
	
	j finaliza