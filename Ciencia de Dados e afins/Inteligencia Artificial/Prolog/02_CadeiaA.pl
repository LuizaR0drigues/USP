% Base de dados
%Definição de animais, plantas e relações de alimentação

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

% EXEMPLOS de consultas
% ?- come(urso, peixe).
% true.

% ?- come(urso, X).
% X = peixe ;
% X = veado ;
% X = guaxinim.

% ?- come(X, grama).
% X = coelho ;
% X = veado.