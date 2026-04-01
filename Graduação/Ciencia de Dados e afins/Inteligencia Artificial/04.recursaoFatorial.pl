% ========= Fatorial ============
fatorial(0, 1). % caso base
fatorial(N, F) :- N > 0, 
                  N1 is N-1, % diminui a variavel pra chamada recursiva
                  fatorial(N1, F1),
                  F is N * F1. % volta multiplicando

