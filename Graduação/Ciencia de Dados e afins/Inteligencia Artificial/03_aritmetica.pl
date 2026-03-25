maiorQueCem() :- write("Digite um número: "),
                read(X),
                (
                    (X> 100, write("O número é maior que cem"));
                    (X<100, write("O número é menor que cem"))
                ).

% Base de dados do diário
nota(joao, 5.0).
nota(maria, 6.0).
nota(josefa, 4.0).
nota(mariana, 9.0).
nota(jose, 6.5).
nota(mara, 1.0).
nota(mary, 10.0).

diario(X) :- nota(X, Nota),(
                    (Nota >= 7, Nota< 10,write("Aprovado!"));
                    (Nota >= 5, Nota<6.9, write("Recuperação"));
                    (Nota >= 0, Nota<4.9, write("Reprovado"))
                    ).