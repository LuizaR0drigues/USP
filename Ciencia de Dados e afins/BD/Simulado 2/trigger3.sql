
-- ------------------------------------------------------------
-- Trigger 3 (em SESSAO): capacidade do espaco + recursos ja exigidos
-- ------------------------------------------------------------
CREATE OR REPLACE FUNCTION fn_verifica_requisitos_sessao()
RETURNS TRIGGER AS $$
DECLARE
    v_limite   INTEGER;
    v_recurso  VARCHAR(100);
    v_exigido  INTEGER;
    v_estoque  INTEGER;
BEGIN
    -- Sessao sem espaco definido nao tem requisitos a validar
    IF NEW.EspacoId IS NULL THEN
        RETURN NEW;
    END IF;

    -- FOR SHARE evita que o espaco seja alterado/removido durante a validacao
    SELECT LimitePessoas
      INTO v_limite
      FROM espaco
     WHERE EspacoId = NEW.EspacoId
       FOR SHARE;

    -- (a) Vagas da sessao nao podem exceder a capacidade do espaco
    IF NEW.Vagas > v_limite THEN
        RAISE EXCEPTION
            'Sessao "%": % vagas excedem o limite de % pessoas do espaco %.',
            NEW.Nome, NEW.Vagas, v_limite, NEW.EspacoId
            USING ERRCODE = 'check_violation';
    END IF;

    -- (b) Recursos que a sessao ja exige devem existir no estoque do espaco
    --     (no INSERT ainda nao ha recursos_sessao; vale para troca de espaco)
    SELECT r.Nome, rs.QtdNecessaria, COALESCE(e.Quantidade, 0)
      INTO v_recurso, v_exigido, v_estoque
      FROM recursos_sessao rs
      JOIN recursos r        ON r.RecursoId = rs.RecursoId
      LEFT JOIN estoque e    ON e.EspacoId  = NEW.EspacoId
                            AND e.RecursoId = rs.RecursoId
     WHERE rs.AtividadeId  = NEW.AtividadeId
       AND rs.NumeroSessao = NEW.NumeroSessao
       AND COALESCE(e.Quantidade, 0) < rs.QtdNecessaria
     LIMIT 1;

    IF FOUND THEN
        RAISE EXCEPTION
            'Espaco % nao atende a sessao "%": recurso "%" exige % unidade(s), mas ha %.',
            NEW.EspacoId, NEW.Nome, v_recurso, v_exigido, v_estoque
            USING ERRCODE = 'check_violation';
    END IF;

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

DROP TRIGGER IF EXISTS trg_sessao_requisitos ON sessao;

CREATE TRIGGER trg_sessao_requisitos
BEFORE INSERT OR UPDATE OF EspacoId, Vagas ON sessao
FOR EACH ROW
EXECUTE FUNCTION fn_verifica_requisitos_sessao();

