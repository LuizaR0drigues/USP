% Exemplo com arvore genealogica

% fatos
mulher(pam) .
mulher(liz) .
mulher(ann) .
mulher(pat) .

homem(tom) .
homem(bob) .
homem(jim) .

genitor(pam, bob) .
genitor(tom, bob) .
genitor(tom, liz) .

genitor(bob, ann) .
genitor(bob, pat) .

genitor(pat, jim) .

% Regras
/*
:- equivale ao (SE) - implicação
, equivale ao (E) - conjunção
; equivale ao (OU) - disjunção
*/

irmao(X, Y) :- genitor(P, X), genitor(P, Y), X \= Y.
avo(X, Y)    :- genitor(X, P), genitor(P, Y).
bisavo(X, Y) :- avo(X, P), genitor(P, Y).
/* P: pai/mae de Z
X é irmao de P 
Logo, X é tio de Z*/
tio(X, Z)   :- genitor(P, Z), irmao(X, P).