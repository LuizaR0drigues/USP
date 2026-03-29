# Trabalho 1 - Vagoes encadeados
#Componentes do vagão
#ID, tipo, ptr pro próximo

#Tutorial de jogo
#1 -  Adicionar vagao no inicio
#2 - Adicionar vagao no final
#3 - Remover vagao pelo id
#4 - Listar trem
#5 - Buscar Vagao
#0 - Sair

	.data
	.align 0
str_mnu: .asciz "Menu - Vagões Encadeados \n1 -  Adicionar vagao no inicio \n2 - Adicionar vagao no final \n3 - Remover vagao pelo id\n4 - Listar trem\n5 - Buscar Vagao\n0 - Sair \n"
str_opc: .asciz "Digite um opção para continuar: "
str_1id: .asciz "O vagao de ID: "
str_2id: .asciz " foi removido!"
str_3id: .asciz " foi encontrado!"
str_add: .asciz "O vagão foi adicionado à " 
str_rmv: .asciz "O vagão foi removido"
str_out: .asciz "Jogo encerrado!"


	.text
	.align 0 #alinha a memoria a palavra
	.globl main
main: #Codigo principal
	
	#imprimindo o menu do jogo
	addi a7, zero, 4
	la a0, str_mnu
	ecall
	
	#imprimindo as opcoes
	addi a7, zero, 4
	la a0, str_opc
	ecall
	
	#Recebendo a opção em a0 e salvado em s0
	addi a7, zero, 5
	ecall
	add s0, a0, zero
	
	#Chegando se a opcao foi 6 -> encerra o programa
	beq s0, zero, finaliza
	
	
	
	
finaliza:
	#Imprime mensagem de despedida
	addi a7, zero, 4
	la a0, str_out
	ecall 
	#encerra
	
	addi a7, zero, 10
	ecall
	