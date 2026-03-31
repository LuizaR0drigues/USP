#Fundamentos de Assembly
#Impressão de string

	.data
	.align 0 #alinha a memoria para string
str_wel: .asciz "Hello Assembly World"

	.text
	.align 2 #alinha a memoria à palavra
	.globl main
main:
	#Chamando a syscall(4) de impressao de string
	addi a7, zero, 4
	#carregando a string pro registrador
	la a0, str_wel
	ecall #imprimindo a mensagem
	
	#finalizando o programa com o serviço 10
	addi a7, zero, 10
	ecall
	