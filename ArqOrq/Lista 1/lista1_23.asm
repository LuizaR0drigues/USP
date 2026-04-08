# Estruturas de Controle
# Leitura de int 
# Impressao da tabuada

	.data
	.align 0
str_wcm: .asciz "Digite um número positivo e não nulo: "
str_seq: .asciz "A tabuada é:\n"
str_mu1: .asciz " * "
str_mu2: .asciz " = "
str_num: .asciz "\n"
	.text 
	.align 2
	.globl main
main: 
	#impressao de str
	addi a7, zero, 4
	la a0, str_wcm
	ecall
	
	#leitura do inteiro
	addi a7, zero, 5
	ecall
	
	#transferindo para s0
	add s0, zero ,a0
	
	#impressao de str
	addi a7, zero, 4
	la a0, str_seq
	ecall
	
	#usando um contador
	addi t0, zero, 1  #contador
	addi t1, zero, 10 #limite
	
verifica:
	#estrutura condicional
	#enquanto t0> 10, imprima o cont+=1
	bgt t0, t1, fim

loop_tab:
	#imprimindo o numero
	addi a7, zero, 1
	add a0, zero, s0
	ecall
	
	#impressao de str
	addi a7, zero, 4
	la a0, str_mu1
	ecall
	
	#imprimindo o numero
	addi a7, zero, 1
	add a0, zero, t0
	ecall 
	
	
	#realizando a multiplicaçãp
	#t2 =  s0 *  t0
	mul t2, s0, t0
	
	
	#impressao de str
	addi a7, zero, 4
	la a0, str_mu2
	ecall
	
	#imprimindo o numero
	addi a7, zero, 1
	add a0, zero, t2
	ecall
	
	#impressao de str
	addi a7, zero, 4
	la a0, str_num
	ecall
	
	#cont += 1
	addi t0, t0, 1
	
	j verifica
	
fim:	#finalizando
	addi a7, zero, 10
	ecall
	
	
	
	
	
	
	
	