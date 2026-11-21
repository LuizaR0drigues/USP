
-- ------------------------------------------------------------
-- Trigger 4 (em RECURSOS_SESSAO): o espaco da sessao tem o recurso?
-- ------------------------------------------------------------
CREATE OR REPLACE FUNCTION fn_verifica_recurso_sessao()
RETURNS TRIGGER AS $$
DECLARE
    v_espaco     INTEGER;
    v_disponivel INTEGER;
BEGIN
    -- FOR SHARE impede que o espaco da sessao mude durante a validacao
    SELECT EspacoId
      INTO v_espaco
      FROM sessao
     WHERE AtividadeId  = NEW.AtividadeId
       AND NumeroSessao = NEW.NumeroSessao
       FOR SHARE;

    -- Sessao sem espaco: nada a validar (sera validado quando o espaco for definido)
    IF v_espaco IS NULL THEN
        RETURN NEW;
    END IF;

    SELECT Quantidade
      INTO v_disponivel
      FROM estoque
     WHERE EspacoId  = v_espaco
       AND RecursoId = NEW.RecursoId;

    IF v_disponivel IS NULL THEN
        RAISE EXCEPTION
            'O espaco % nao possui o recurso % no estoque.',
            v_espaco, NEW.RecursoId
            USING ERRCODE = 'check_violation';
    ELSIF v_disponivel < NEW.QtdNecessaria THEN
        RAISE EXCEPTION
            'Recurso % insuficiente no espaco %: necessario %, disponivel %.',
            NEW.RecursoId, v_espaco, NEW.QtdNecessaria, v_disponivel
            USING ERRCODE = 'check_violation';
    END IF;

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

DROP TRIGGER IF EXISTS trg_recursos_sessao_requisitos ON recursos_sessao;

CREATE TRIGGER trg_recursos_sessao_requisitos
BEFORE INSERT OR UPDATE OF AtividadeId, NumeroSessao, RecursoId, QtdNecessaria ON recursos_sessao
FOR EACH ROW
EXECUTE FUNCTION fn_verifica_recurso_sessao();

