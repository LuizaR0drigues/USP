# Compilar tudo e gerar o executável
all: 
	gcc registro.c cabecalho.c comandos.c bcabecalho.c bregistro.c  main.c -o runnable -lm

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

zip:
	zip runcodes.zip Makefile *.c *.h