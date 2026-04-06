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
str_mnu: .asciz "\nMenu - Vagões Encadeados \n1 - Adicionar vagao no inicio \n2 - Adicionar vagao no final \n3 - Remover vagao pelo id\n4 - Listar trem\n5 - Buscar Vagao\n6 - Sair \n"
str_opc: .asciz "\nDigite um opção para continuar: "
str_1id: .asciz "O vagao de ID: "
str_2id: .asciz " foi removido!"
str_3id: .asciz " foi encontrado!"
str_ad1: .asciz "\nO vagão foi adicionado ao inicio " 
str_ad2: .asciz "\nO vagão foi adicionado ao final " 
str_rmv: .asciz "\nO vagão foi removido"
str_out: .asciz "Jogo encerrado!"

str_0vg:
	# String suporte para início da listagem dos vagões
	.asciz "Trem: "
str_1vg:
	# String suporte para print de vagões encadeados 
	.asciz " -> "
str_list_tipos:
	# Menu para tipos permitidos de vagão para inserir
	.asciz "\nTipos de vagão disponívels:\n 1 - Carga\n 2 - Passageiro\n 3 - Combustível\n"
str_get_tipo:
	# String suport para obter tipo de  vagão a inserir
	.asciz "\nDigite uma opção para continuar: "
str_get_id:
	# String suporte para solicitar ID de busca
	.asciz "\nDigite um ID do vagão a ser buscado: "
	
str_busca_vagao1:
	# String suport para print do vagão encontrado
	.asciz "Vagão encontrado: ID "

str_busca_vagao2:
	# String suport para print do vagão encontrado
	.asciz " | Tipo "
	
str_new_line:
	.asciz "\n"

str_resp_add_inicio:
	# String resposta para adição ao inicio
	.asciz "Vagão inserido ao início com sucesso!"
	
str_resp_add_final:
	# String resposta para adição ao inicio
	.asciz "Vagão inserido ao final com sucesso!"

#mensagens de  teste
str_all: .asciz "Erro na alocação de memoria"
str_tst1: .asciz "\nA locomotiva (head) foi criada\n"
str_tst2: .asciz "\nAndando na locomotiva"
str_tst3: .asciz "\nLigando os vagoes"
	.align 2 #linhando à palavra
#ponteiro que vai guardar a head da lista encadeada
ptr_init: .word 0

# Tipos de vagão
tp_lcmt:	 .word 0 # Locomotiva
tp_carg:	 .word 1 # Carga
tp_pass:	 .word 2 # Passageiro
tp_cbtv:	 .word 3 # Combustível

# ID incremental
id_prox: .word 1 # Id inicial 

	.text
	.align 2 #alinha a memoria a palavra
	.globl main
main: #Codigo principal

	# Inicialização de locomotiva (vagão 0)
	jal cria_locomotiva
	
menu_inicial:
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
	
	add s0, zero, a0
	
	#variaveis de opcao
	addi a1, zero, 1
	addi a2, zero, 2
	addi a3, zero, 3
	addi a4, zero, 4
	addi a5, zero, 5
	addi a6, zero, 6
	
	#Chegando se a opcao foi 6 -> encerra o programa
	beq s0, a6, finaliza	
	
cases:	#Adiciona  No - inicio
	beq s0, a1, add_inicio
	
	#Adiciona No - final
	beq s0, a2, add_final
	
	#Remover vagão por id
	# TODO 
	#beq s0, a3, del_vagao
	
	#Listar trem
	beq s0, a4, list_trem
	
	#Buscar vagão
	beq s0, a5, get_vagao
	
	j finaliza

input_infos_novo_vagao:
	# Permite inserir ID e Tipo de vagão pela usuária
	# Retorno: a1 = ID_novo_vagao
	# 	   a2 = TIPO_novo_vagao
	
	# Obter próximo id
	la t5, id_prox # t5 = id_prox (end)
	lw a1, 0(t5) # a1 = <conteudo de t5>
	addi t6, a1, 1 # t6 = a1 + 1
	
	# Salvar próximo id no endereço t5
	sw t6, 0(t5)
	
	# Print menu de tipos
	addi a7, zero, 4
	la a0, str_list_tipos
	ecall # print(sListTipos)
	
	# Print suporte obter tipo
	la a0, str_get_tipo
	ecall # print(sGTipo)
	
	# Obter tipo
	addi a7, zero, 5
	ecall # a0 = <tipo>
	
	# Armazena temporario
	add a2, zero, a0 # a1 = a0
	
	jr ra
	
input_get_id:
	# Obtenção de ID para busta
	# Retorno:
	#  a5: ID inserido para busca
	
	# Print msg input a usuaria
	la a0, str_get_id
	addi a7, zero, 4
	ecall 
	
	# Obter ID
	addi a7, zero, 5
	ecall
	
	# salvar em a5
	add a5, zero, a0
	
	jr ra

buscar_vagao_por_id:
	# Obtenção do vagão via ID
	# Argumentos esperados:
	#  a5: ID para busca
	
	# a1 = 2 para percorrer trem e imprimir caso  encontre ID
	addi a1, zero, 2
	
	# End primeiro vagão anterior
	#  precisamos dos últimos 4 bytes (total de 16)
	#  a partir do endereço da locomotiva 
	add a4, zero, s1

	# Caminhar pelo trem até o final
	#  ou até encontrar ID buscado
	j loop_percorre_trem
	
	
criar_novo_vagao:
	# Criação de novos vagões soltos (i.e. não conectados inicialmente)
	# Tamanho: 16 bytes reservados
	# Padrão de endereços:
	#   0-3 bytes: end vagão anterior (= 0 default)
	#   4-7 bytes: ID vagão
	#   8-12 bytes: TIPO vagão
	#   13-16 bytes: end vagão próximo (= 0 default)
	
	# Argumentos esperados: 
	#   a1: ID vagão
	#   a2: TIPO vagão
	
	# Retorno:
	#   a3: End vagão criado
	
	#alocando o novo no
	addi a0, zero, 16 # total de byter alocados
	addi a7, zero, 9
	ecall
	
	add a3, zero, a0 # a3 = a0
	
	beq a0, zero, erro_all
	
	#o atual|prox apontara pra  head
	#a0: novo no
	#t1: a head
	sw zero, 0(a0) # novo->prev
	sw a1, 4(a0) # novo->id
	sw a2, 8(a0) # novo->tipo
	sw zero, 12(a0) # novo->next
	
	jr ra

carrega_locomotiva:
	# Carregar locomotiva
	# Retorno: 
	#   s1: End da locomotiva (heap)
	
	la t0, ptr_init #carrega o endereço do ptr pro t0
	lw s1, 0(t0) # end heap: locomotiva
	
	jr ra

anexar_vagao_ao_inicio:
	# Adicionar como primeiro vagão da locomotiva
	# Argumentos esperados
	#   s1: End locomotiva (heap)
	#   a3: End novo vagão (heap)
	
	# End primeiro vagão anterior
	#  precisamos dos últimos 4 bytes (total de 16)
	#  a partir do endereço da locomotiva 
	lw t0, 12(s1)
	
	# End do novo vagão passa a ser o 
	#  próximo vagão da locomotiva
	sw a3, 12(s1)
	
	# End do vagão seguinte ao vagão novo
	#  passa a ser o vagão antigo
	sw t0, 12(a3)
	
	jr ra
	
loop_percorre_trem:
	# Loop para percorrer cada item (vagão) 
	#  da lista linkada (trem)
	# Argumentos esperados
	#  a1: opção de função a ser executada por vagão
	#  a3: end do vagão novo (válido para o caso inserir novo vagão)
	#  a4: end do próximo vagão
	#  a5: id do vagão buscado (válido para o caso de busca por vagão)
	
	# Condição de continuação: endereço de proximo vagão não nulo
	lw t0, 12(a4)
	bne t0, zero, func_por_vagao	# if a4 != 0: func_por_vagao
	
	addi t1, zero, 1
	addi t2, zero, 2
	
	# Retorno às funções originais
	beq a1, zero, fim_loop_add_final
	beq a1, t1, fim_loop_print
	
	j menu_inicial
	
func_por_vagao:
	# Aplicação de função por vagão de trem
	# Argumentos esperados:
	#  a1: opção de função a ser executada por vagão
	#  a1 = 0: inserção ao final
	#  a1 = 1: print vagão
	#  a1 = 2: busca por id
	
	addi t0, zero, 1
	addi t1, zero, 2
	beq a1, zero, func_pass
	beq a1, t0, print_suporte_por_vagao
	beq a1, t1, reconhecer_vagao_por_id
	
	j loop_percorre_trem

func_pass:
	# Passa para novo vagão, preservando o último em registro
	# Retorno:
	#  a4: end próximo vagão
	#  a3: end vagão atual
	lw a4, 12(a4) #novo->next = head
	j loop_percorre_trem

reconhecer_vagao_por_id:
	# Caso Id inserido confere com atual vagão, imprimir
	# Argumentos esperados
	#  a5: ID vagão buscado
	#  a4: end próximo vagão
	
	# Id vagao
	lw t0, 4(a4)
	
	beq a5, t0, print_vagao_encontrado
	
	# Mover para novo vagão
	lw a4, 12(a4) #novo->next = head
	
	j loop_percorre_trem
	
print_vagao_encontrado:
	# Print vagão quando encontrado
	# Argumentos esperados
	#  a4: end vagão atual
	# Formato de print
	#   ID: <id> | Tipo: tipo_vagão
	
	# Print suporte
	la a0, str_busca_vagao1
	addi a7, zero, 4
	ecall
	
	# Print ID
	lw t0, 4(a4)
	add a0, zero, t0
	addi a7, zero, 1
	ecall
	
	# print suporte
	la a0, str_busca_vagao2
	addi a7, zero, 4
	ecall
	
	# Print tipo
	lw t0, 8(a4)
	add a0, zero, t0
	addi a7, zero, 1
	ecall
	
	# Pula linha
	la a0, str_new_line
	addi a7, zero, 4
	ecall
	
	# Retornar à chamada da função
	jr ra

anexar_vagao_ao_final:
	# Adicionar como último vagão da locomotiva
	# Argumentos esperados
	#   s1: End locomotiva (heap)
	#   a3: End novo vagão (heap)
	
	# a1 = 0 para percorrer trem e adicionar ao final
	addi a1, zero, 0
	
	# End primeiro vagão anterior
	#  precisamos dos últimos 4 bytes (total de 16)
	#  a partir do endereço da locomotiva 
	add a4, zero, s1
	
	# Caminhar pelo trem até o último vagão
	j loop_percorre_trem
	
fim_loop_add_final:	
	
	# End do vagão seguinte ao vagão novo
	#  passa a ser o vagão antigo
	sw a3, 12(a4)
	
	jr ra
	
fim_loop_print:
	# Imprimir último vagão
	# Argumentos esperados:
	#  a4: end último vagão
	lw a0, 4(a4)
	addi a7, zero, 1
	ecall
	
	jr ra

add_inicio:
	#temos que verificar se ja existe
	jal carrega_locomotiva
	
	#criando um novo no
	
	# Solicitar inserção de ID e Tipo do vagão
	jal input_infos_novo_vagao
	
	# Criar novo vagão e anexar à locomotiva
	jal criar_novo_vagao
	
	# Vincular novo vagão à locomotiva
	jal anexar_vagao_ao_inicio
	
	# Print op com sucesso
	addi a7, zero, 4
	
	la a0, str_resp_add_inicio
	ecall
	
	# Print new line
	la a0, str_new_line
	ecall
	
	#voltando pro menu principal
	j menu_inicial
	
add_final:
	#temos que verificar se ja existe
	jal carrega_locomotiva
	# s1: End da locomotiva (heap)
		
	# Solicitar inserção de ID e Tipo do vagão
	jal input_infos_novo_vagao
	# a1: ID_novo_vagao
	# a2: TIPO_novo_vagao
	
	# Criar novo vagão e anexar à locomotiva
	jal criar_novo_vagao
	# a3: End vagão criado
	
	# Vincular novo vagão à locomotiva
	jal anexar_vagao_ao_final
	
	# Print op com sucesso
	addi a7, zero, 4
	
	la a0, str_resp_add_final
	ecall
	
	# Print new line
	la a0, str_new_line
	ecall
	
	#voltando pro menu principal
	j menu_inicial
	
get_vagao:
	#temos que verificar se ja existe
	jal carrega_locomotiva
	# s1: End da locomotiva (heap)
	
	# Solicitar inserção de ID para busca
	jal input_get_id
	# a5: ID_novo_vagao
	
	# Buscar id solicitado
	jal buscar_vagao_por_id
	
	# Voltando ao menu principal
	j menu_inicial
	
cria_locomotiva:
	#Cria a locomotiva(primeiro oo)
	#vamos guardar um ptr inicial na heap
	#alocando 4 palavra - 16 bytes
	# 0-3 bytes: end vagão anterior
	# 4-7 bytes: ID vagão
	# 8-12 bytes: TIPO vagão
	# 13-16 bytes: end vagão próximo
	
	addi a0, zero, 16
	addi a7, zero, 9 #serviço relacionado ao malloc
	ecall #a0 recebe o endereço
	
	#checa se falhou
	beq a0, zero, erro_all
	
	#Inicializando o nó
	# [valor | proximo] -> [ 0 | 0]
	addi t2, zero, 0
	sw t2, 0(a0)
	sw t2, 4(a0)
	sw t2, 8(a0)
	sw t2, 12(a0)
	
	#Atualiza a head
	la t0, ptr_init #t1 possui o enderço do init
	sw a0, 0(t0) # a0 possui o endereço do no na heap
	
	#mensagem de criação da locomotiva
	#imprimindo mensagem
	addi a7, zero, 4
	la a0, str_tst1
	ecall
	
	#voltar pro estado anterio
	jr ra
	
print_suporte_por_vagao:
	# Função print a ser executada por vagão
	# Argumentos esperados
	#  a4: Endereço do próximo vagão
	
	# Print id vagão
	lw a0, 4(a4)		# a0 = vagao->id
	addi a7, zero, 1
	ecall
		
	# Print eixo
	la a0, str_1vg
	addi a7, zero, 4
	ecall

	# Caminha para próximo vagão
	lw a4, 12(a4) #novo->next = head
	
	# Retorna ao laço inicial, percorrendo todo o trem
	j loop_percorre_trem
		
list_trem:
	# Listagem de todos os vagões do trem criado
	#  formato de saída: Trem: 1 -> 2 -> 3 -> 4	
	
	jal carrega_locomotiva
	# s1: End da locomotiva (heap)

	# Print msg trem 0
	la a0, str_0vg
	addi a7, zero, 4
	ecall # print(trem)
	
	# Salvando em a4 ponteiro para inicio do trem
	add a4, zero, s1 # a4 = end locomotiva
	
	# a1 como argumento para laço. Aqui
	#  queremos que a função utilizada seja de 
	#  print por vagão: a1 = 1
	
	addi a1, zero, 1 # a1 = 1
	
	# Redirecionando para loop de suporte para  listagem do trem
	jal loop_percorre_trem
	
	# Print new line
	addi a7, zero, 4
	la a0, str_new_line
	ecall
	
	# Retorno ao menu inicial
	j menu_inicial
	
	
	
#Finalização do codigo
#Em caso de má alocação de memoria
erro_all:
	#Imprime mensagem de erro
	addi a7, zero, 4
	la a0, str_all
	ecall 
	#encerra
	
	addi a7, zero, 10
	ecall
#Por opção do jogador	
finaliza:
	#Imprime mensagem de despedida
	addi a7, zero, 4
	la a0, str_out
	ecall 
	#encerra
	
	addi a7, zero, 10
	ecall
	
