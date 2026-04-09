# Parte 4 : Vetores e Memória
# Armazenamento na memoria e Recuperação dos dados
# Comparação de elementos
	.data
	.align 0
str_wcm: .asciz "\nDigite a quantidade de numéros que você gostaria de armazenar: "
str_w2:  .asciz "\nDigite o número: "
str_val: .asciz "\nNúmero armazenado: "
str_str: .asciz "\n"
str_gt1: .asciz "\nO maior elemento é: "
str_fim: .asciz "\nOs números foram armazenados e recuperados na memória!\n"
#debug
str_err: .asciz "\nErro na alocação de memória! "

	.text
	.align 2
	.globl main
main:
	#imprime  qtd
	addi a7, zero, 4
	la a0, str_wcm
	ecall
	
	#leitura de qtd
	addi a7, zero, 5
	ecall
	
	#salvando um copia pro contador
	add s0, zero, a0
	
	#calculando a qtd de bytes
	# a0 =  (s0 * 4) bytes
	addi t0, zero, 4
	mul a0, s0, t0
	
	#alocando a memoria
	addi a7, zero, 9
	ecall
	
	#em caso de erro na alocação, finaliza
	beq a0, zero, erro
	
	#t1: ptr atual 
	add t1, zero, a0
	
	#t2: inicio do vetor
	add t2, zero, a0
	
	#t6: guarda o inicio -  comparação
	add t6, zero, a0
	
	#t5: contador de leitura
	add t5, zero, s0
	
loop:	#seção de leitura e armazenamento dos dados na memoria
	beq s0, zero, recupera
	
	#pede o numero
	addi a7, zero, 4
	la a0, str_w2
	ecall
	
	#le o inteiro em a0
	addi a7, zero, 5
	ecall
	
	#escreve o conteudo de a0 na posicao offset+qtd
	sw a0, 0(t1)
	
	#avança o ponteiro
	addi t1, t1, 4
	
	#decrementa o contador
	addi s0, s0, -1
	
	j loop
	
recupera: #recuperação da memoria e imprime os dados
	
	beq t5, zero, loop_comp
	
	#Imprime msg 
	addi a7, zero, 4
	la a0, str_val
	ecall 
	
	#busca na memoria o dados e imprime na tela
	#carrega da memoria o valor em offset(t2)
	lw t3, 0(t2)
	
	
	#guarda em a0 o valor que sera imprimido
	add a0, zero, t3
	add t4, zero, t3
	
	#imprime na tela
	addi a7, zero, 1
	ecall
	
	#Imprime \n
	addi a7, zero, 4
	la a0, str_str
	ecall 
	
	#avança na memoria
	addi t2, t2, 4
	
	#decrementa o contador
	addi t5, t5, -1
	
	j recupera
	
#Comparação dos elementos
dados_comp:
	#t6 = inicio do vetor
	#t1 = final do vetor
	
	#maior = priemiro elem
	lw t4, 0(t6)
	
	
loop_comp: #comparação
	
	addi t6, t6, 4 #avanaça em 1 posicao
	beq t6, t1, fim_comp
	
	#elemento atual
	lw t3, 0(t6)
	
	blt t4, t3, atualiza
	
	j loop_comp

atualiza:	
	add t4, zero, t3
	j loop_comp
	
	
fim_comp: 
	addi a7, zero, 4
	la a0, str_gt1
	ecall
	
	add a0, zero, t4
	addi a7, zero, 1
	ecall
	
	addi a7, zero, 4
	la a0, str_str
	ecall
	
	j fim

fim: 	
	
	#finaliza
	addi a7, zero, 10
	ecall

 erro:  
	#carrega a msg de erro
	addi a7, zero, 4
	la a0, str_err
	ecall
	
	#finaliza
	addi a7, zero, 10
	ecall
	
	
	
	