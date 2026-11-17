WITH ranking_sessoes AS (
    SELECT e.id as evento_id,
           s.id as sessao_id,
           a.titulo,
           -- realiza a contagem de inscricoes
           COUNT(ins.pessoa_id) as qtd_inscricoes,
           -- calcula a taxa de ocupação
           esp.capacidade,
           (COUNT(ins.pessoa_id)::numeric / esp.capacidade) AS taxa_ocup,
           ROW_NUMBER() OVER ( -- retorna a posicao do ranking
                PARTITION BY e.id --refaz pra cada evento
                ORDER BY (COUNT(ins.pessoa_id)::numeric / esp.capacidade) DESC, s.id ASC
             ) AS posicao
    FROM evento e
     JOIN atividade a ON a.evento_id = e.id
     JOIN sessao s ON s.atividade_id = a.id
     JOIN espaco esp ON esp.id = sessao.espaco_id
     LEFT JOIN inscricao_sessao ins
            ON ins.sessao_id = se.id
            AND ins.status = 'confirmada'
    GROUP BY e.id, s.id, a.titulo, esp.capacidade
)
SELECT evento_id, sessao_id, titulo, qtd_inscricoes, 
        capacidade, taxa_ocup, posicao
    FROM ranking_sessoes
  WHERE posicao <= 3
    ORDER BY evento_id, posicao;


    