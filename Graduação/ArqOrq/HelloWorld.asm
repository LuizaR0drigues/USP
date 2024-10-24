.data
	hello: .asciz "Hello World"  # Define uma string terminada em NULL ("Hello World\0") na seção de dados
.text
li a7, 4     # Número da syscall para escrita
la a0, hello # Carrega o endereço da string "Hello World"
ecall        # Executa a syscall
