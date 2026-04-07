#Parte 5 - FUnções e Pilha
#Uma função que recebe 1 numeros e retorna seu fatorial

	 .data
	 .align 0
str_wcm: .asciz "Digite um numero: "
str_fat: .asciz "\nO fatorial é: "

	 .text
	 .align 2
	 .globl main
main:	
	#Imprime msg
	addi a7, zero, 4
	la a0, str_wcm
	ecall
	
	#lendo o int
	addi a7, zero, 5
	ecall
	
	#salvando o valor
	add s0, zero, a0
	
	#chamando a funcao
	jal fatorial
	
	#salvando o retorno
	add s1, zero, a1
	
	#Imprindo o valor
	addi a7, zero, 4
	la a0, str_fat
	ecall
	
	add a0, zero, s1
	addi a7, zero, 1
	ecall 
	
	#finaliza
	addi a7, zero, 10
	ecall
	
fatorial:	
	#empilhando os argumento e retorno
	addi sp, sp, -8
	sw ra, 0(sp)
	sw a0, 4(sp)
	
	#caso base-> N! = 1
	beq a0, zero, retorna_um
	
	#chamada recursiva para n-1
	addi a0, a0, -1
	jal fatorial
	
	#recupera o valor originala(N) que foi salvo
	lw t0, 4(sp)
	
	#calcula a multiplicação
	mul a1, a1, t0
	
	j retorna_fat
	
retorna_um:
	#a1 = 1
	addi a1, zero, 1
	
retorna_fat:
	#desempilhando pra voltar pra main
	lw ra, 0(sp)
	lw a0, 4(sp)
	addi sp, sp, 8 #volta o ptr pro inicio da heap
	
	jr ra