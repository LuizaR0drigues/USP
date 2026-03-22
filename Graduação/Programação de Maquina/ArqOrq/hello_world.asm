		.data #diretiva pro incio do segmento de dados
vlr_inteiro: 	.word 157
string:		.asciz "Hello Assembly's World!"

		.text #diretiva pro incio do segmento de  textp
		.globl main #diretiva pra usar rotulo em outro programa
main:			#rotulo pra ponto de entrada no processo
		li t0,0
		li t1,10
loop: 		beq t0, t1, fim_loop #se to=t1 vá para fim_loop
		#onde viria o codigo interno do loop
		addi t0, t0, 1   # incrementa t0
		
		j loop #retorna pro inicio do loop
fim_loop: 	
		la a0, string   # carrega endereço da string
		li a7, 4        # syscall de print string
		ecall
		
		li a7, 10 #codigo da syscall de saida
		ecall #encerra o programa