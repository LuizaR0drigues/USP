#Fatorial recursivo
	.data
	.text 
	.align 2
	.globl main
main: 
	#leitura do numero
	addi a7, zero, 5
	ecall
	
	#salvando-o em s0
	add s0, zero, a0
	
	#chamando a funcao
	jal fatorial #seu reorno vira em a1
	
	#imprimindo a saida
	addi a7,zero, 1
	add a0, zero, a1
	ecall
	
	#finaliza
	addi a7, zero, 10
	ecall
	
fatorial:
	#empilhando ra e a0 -> 8 bytes(4 p/ cada)
	addi sp, sp, -8 
	sw ra, 0(sp)
	sw a0, 4(sp)
	
	#caso base n==0 -> return 1
	beq a0, zero, retorna_1
	
	#recursao f(n-1)
	#caso nao, decrementa n
	addi a0, a0, -1
	#chama a funcao recursivamente
	jal fatorial
	
	#recupera o valor original
	lw t0, 4(sp)
	
	#result = f(n-1) * n
	mul a1, a1, t0 # ai *= t0
	
	j retorna_fat
	
retorna_1:
	#ai =1
	addi a1, zero, 1
	
	
retorna_fat:
	#desempilhando pra voltar pra min
	lw ra, 0(sp)
	lw a0, 4(sp)
	addi sp, sp, 8 #volta o ponteiro pro inicio da heap
	jr ra
	