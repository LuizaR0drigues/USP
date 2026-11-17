SELECT e.id,
       e.nome
FROM evento e
WHERE EXISTS
        (SELECT 1
         FROM atividade a None
         JOIN sessao s ON s.atividade_id = a.id
         JOIN espaco ep ON ep.id = s.espaco_id
         WHERE a.evento_id = e.id
             AND ep.capacidade >= 50);

/*
DIagnóstico: na consulta acima, verifica apenas se há uma sessão cuja cpacidade seja maior ou igual a 50 pessoas, ou seja, se houver pelo menos uma sessao do evento que cumpra esse requisito, será retornado eventos que também possuem espaços menores.
Correção: para que todas as sessoes selecionadas tenham capacidade supeior ou igual a 50, é necessário adicionar AND NOT EXISTS que irá barrar sessao com capacidade inferior ao limite imposto(50)
Versao corrigida abaixo
*/
SELECT e.id,
       e.nome
FROM evento e
WHERE EXISTS
        (SELECT 1
         FROM atividade a 
         JOIN sessao s ON s.atividade_id = a.id
         JOIN espaco ep ON ep.id = s.espaco_id
         WHERE a.evento_id = e.id
             AND NOT EXISTS
                 (
                 SELECT 1
                  FROM atividade a2
                  JOIN sessao s2 ON s2.atividade_id = a2.id
                  JOIN espaco ep2 ON ep2.id = s2.espaco_id
                 WHERE a2.evento_id = e2.id
                      AND ep2.capacidade < 50
                )
                      
        );