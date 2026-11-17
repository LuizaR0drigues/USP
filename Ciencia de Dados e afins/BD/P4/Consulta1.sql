SELECT p.id, p.nome
    FROM pessoa p 
    JOIN inscricao_evento ie ON ie.pessoa_id = p.id
 WHERE ie.evento_id = 10
    AND ie.status = 'confirmada'
    AND NOT EXISTS (
        -- busca sessoes obrigatorio do evento 10
        SELECT 1 -- existe pelo menos uma linha
         FROM sessao s
         JOIN atividade a ON a.id=s.atividade_id
        WHERE a.evento_id = 10
            AND NOT EXISTS (
                SELECT 1
                  FROM inscricao_sessao ins
                  WHERE ins.pessoa_id = p.id
                    AND ins.sessao_id = s.id 
                    AND ins.status = 'confirmada'           
                    )
    );

