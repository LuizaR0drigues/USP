INSERT INTO pessoa (id, nome) VALUES 
(1, 'Ana'),
(2, 'Bruno'),
(3, 'Carla')
ON CONFLICT (id) DO NOTHING;

INSERT INTO evento (id, nome) VALUES (1, 'Semana de Tecnologia')
ON CONFLICT (id) DO NOTHING;

INSERT INTO atividade (id, evento_id, titulo) VALUES (1, 1, 'Workshop de Banco de Dados')
ON CONFLICT (id) DO NOTHING;

INSERT INTO espaco (id, capacidade) VALUES (99, 1)
ON CONFLICT (id) DO NOTHING;

INSERT INTO sessao (id, atividade_id, espaco_id, requer_inscricao, limite_vagas) VALUES 
(101, 1, 99, true, 2),
(102, 1, 99, true, NULL)
ON CONFLICT (id) DO NOTHING;


-- TESTE 1: Preencher as 2 vagas da Sessão 101 (Ambos DEVEM FUNCIONAR)
INSERT INTO inscricao_sessao (pessoa_id, sessao_id, status) VALUES (1, 101, 'confirmada');
INSERT INTO inscricao_sessao (pessoa_id, sessao_id, status) VALUES (2, 101, 'confirmada');

-- TESTE 2: Inserir Carla como 'pendente' na Sessão 101 já lotada (DEVE FUNCIONAR)
INSERT INTO inscricao_sessao (pessoa_id, sessao_id, status) VALUES (3, 101, 'pendente');

-- TESTE 3: Alterar Carla de 'pendente' para 'confirmada' na Sessão 101 (DEVE DAR ERRO do trigger)
UPDATE inscricao_sessao SET status = 'confirmada' WHERE pessoa_id = 3 AND sessao_id = 101;

-- TESTE 4: Atualizar Ana que JÁ estava 'confirmada' (DEVE FUNCIONAR, não conta 2 vezes)
UPDATE inscricao_sessao SET status = 'confirmada' WHERE pessoa_id = 1 AND sessao_id = 101;

-- TESTE 5: Testar limite_vagas NULL na Sessão 102 (herda capacidade = 1 do espaço 99)
-- 5a. Primeira inscrição confirmada (DEVE FUNCIONAR)
INSERT INTO inscricao_sessao (pessoa_id, sessao_id, status) VALUES (1, 102, 'confirmada');
-- 5b. Segunda inscrição confirmada (DEVE DAR ERRO do trigger)
INSERT INTO inscricao_sessao (pessoa_id, sessao_id, status) VALUES (2, 102, 'confirmada');