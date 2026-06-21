% Entrada e Saída de dados
start() :- write('Digite um valor para X: '),nl, 
           read(X), nl,
           write('O valor digitado foi: '), 
           Write(X), nl.