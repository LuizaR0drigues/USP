% ========= Fatorial ============
fatorial(0, 1). % caso base
fatorial(N, F) :- N > 0, 
                  N1 is N-1, % diminui a variavel pra chamada recursiva
                  fatorial(N1, F1),
                  F is N * F1.

% Cadeia Alimentar e recursao
% fatos: Tipos de Seres vivos
animal(urso).
animal(peixe).
animal(peixinho).
animal(cachorro).
animal(gato).
animal(lince).
animal(raposa).
animal(coelho).
animal(veado).
animal(guaxinim).

planta(alga).
planta(grama).

% Relaçoes de alimentação
% come(X,Y) significa: X come Y

come(urso, peixe).
come(lince, veado).
come(urso, veado).
come(peixe, peixinho).
come(peixinho, alga).
come(guaxinim, peixe).
come(raposa, coelho).
come(coelho, grama).
come(veado, grama).
come(urso, guaxinim).

% Regras
% X é predador se ele come outro animal

predador(X) :- come(X,Y), animal(Y).

% X é herbivoro se ele come planta

herbivoro(X) :- come(X,Y), planta(Y).

pertence-cadeia(X, Y) :- animal(X), come(Y, X). % ideia base
pertence-cadeia(X, Y) :- come(Y, W), pertence-cadeia(X, W).