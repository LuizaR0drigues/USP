# Compilar tudo e gerar o executável
all: 
	gcc cabecalho.c bcabecalho.c bregistro.c registro.c funcoesFornecidas.c comandos.c  main.c -o runnable -lm

# Executar o programa
run: runnable
	./runnable

# Limpar os arquivos compilados
clear:
	rm -f *.o runnable

# Executar um ciclo completo de testes
test:
	clear
	make clear
	make all
	make run

batata:
	clear
	make all
	./runnable < input.txt > output.txt

caso8:
	clear
	make all
	./runnable < input8.txt > output8.txt

zip:
	zip runcodes.zip Makefile *.c *.h