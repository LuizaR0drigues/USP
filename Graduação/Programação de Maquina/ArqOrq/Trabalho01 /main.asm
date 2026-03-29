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
str_mnu: .asciz "Menu - Vagões Encadeados \n1 -  Adicionar vagao no inicio \n2 - Adicionar vagao no final \n3 - Remover vagao pelo id\n4 - Listar trem\n5 - Buscar Vagao\n6 - Sair \n"
str_opc: .asciz "\nDigite um opção para continuar: "
str_1id: .asciz "O vagao de ID: "
str_2id: .asciz " foi removido!"
str_3id: .asciz " foi encontrado!"
str_ad1: .asciz "O vagão foi adicionado ao inicio " 
str_ad2: .asciz "O vagão foi adicionado ao final " 
str_rmv: .asciz "O vagão foi removido"
str_out: .asciz "Jogo encerrado!"
#mensagens de erro
str_all: .asciz "Erro na alocação de memoria"
	
	.align 2 #linhando a palavra
#ponteiro que vai guardar a head da lista encadeada
ptr_init: .word 0

	.text
	.align 2 #alinha a memoria a palavra
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
	
	#variaveis de opcao
	addi a1, zero, 1
	addi a2, zero, 2
	addi a3, zero, 3
	addi a4, zero, 4
	addi a5, zero, 5
	addi a6, zero, 6
	
	#Chegando se a opcao foi 6 -> encerra o programa
	beq s0, a6, finaliza
	
	#Adiciona  No - inicio
	#beq s0, a1, add_inicio
	
	#Adiciona No - final
	beq s0, a2, add_final
	
	j finaliza
	
add_final:
	la t0, ptr_init
	lw t1, 0(t0) #t1: cabeça da lista
	
	#se a lista estiver vaiza-> criaremos a locomotiva
	beq t1, zero, cria_locomotiva
	
	#se ja existir, vamos até o ultimo vagao e adicionaremos um novo
	add t2, zero, t1 #t2: no atual
	
loop_final:
	lw t3, 4(t2) #t3: o proximo no/vagao
	
	beq t3, zero, insere_final
	
	#Caso ainda tenha vagao
	add t2, zero, t3 #avança pro proximo
	j loop_final 

insere_final:
	addi a0, zero, 8
	addi a7, zero, 9
	ecall
	
	beq a0,zero, erro_all
	
	#Inicializa novo no
	addi t4, zero, 0
	sw t4, 4(a0) #escreve prox como Null
	
	#Ligando o ultimo ao novo vagao
	sw a0, 4(t2)
	
	#imprimindo mensagem
	addi a7, zero, 4
	la a0, str_ad2
	ecall
	
	j main #voltando pro menu
cria_locomotiva:
	#Senao, cria a locomotiva(primeiro oo)
	#vamos guardar um ptr inicial na heap
	#alocando 2 palavra - 8 bytes (Atual + proximo)
	addi a0, zero, 8 
	addi a7, zero, 9 #serviço relacionado ao malloc
	ecall #a0 recebe o endereço
	
	#checa se falhou
	beq a0, zero, erro_all
	
	#guardando o ptr
	#a0: reg com endereço
	#t1: valor
	la t0, ptr_init #t1 possui o enderço do init
	sw a0, 0(t0) # a0 possui o endereço do no na heap
	
	#Como é o primeiro nó, teremos
	addi t1, zero, 0 #valor inicial da locomotiva
	# [valor | proximo] -> [ 0 | 0]
	sw t1, 0(a0)
	sw t1, 4(a0)
	
	j main
	
#Finalização do codigo
erro_all:
	#Imprime mensagem de erro
	addi a7, zero, 4
	la a0, str_all
	ecall 
	#encerra
	
	addi a7, zero, 10
	ecall
	
finaliza:
	#Imprime mensagem de despedida
	addi a7, zero, 4
	la a0, str_out
	ecall 
	#encerra
	
	addi a7, zero, 10
	ecall
	