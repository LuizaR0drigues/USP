# Compilar tudo e gerar o executável
all: runnable

# Regras para a compilação do executável final
runnable: main.o registro.o cabecalho.o
	gcc main.o registro.o cabecalho.o -o runnable

# Regras para a compilação dos arquivos .o
main.o: main.c registro.h cabecalho.h
	gcc -c main.c -o main.o

registro.o: registro.c registro.h
	gcc -c registro.c -o registro.o

cabecalho.o: cabecalho.c cabecalho.h
	gcc -c cabecalho.c -o cabecalho.o

# Executar o programa
run: runnable
	./runnable

# Limpar os arquivos compilados
clear:
	rm -f *.o runnable

# Executar um ciclo completo de testes
test:
	make clear
	make all
	make run
