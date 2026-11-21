
-- ------------------------------------------------------------
-- Trigger 5 (em PESSOA_PROMOTOR e ORGANIZACAO): especializacao disjunta
-- Um promotor e pessoa fisica OU organizacao, nunca os dois.
-- ------------------------------------------------------------
CREATE OR REPLACE FUNCTION fn_verifica_promotor_disjunto()
RETURNS TRIGGER AS $$
DECLARE
    v_promotor INTEGER;
BEGIN
    IF TG_TABLE_NAME = 'pessoa_promotor' THEN
        v_promotor := NEW.PessoaPId;
    ELSE
        v_promotor := NEW.OrganizacaoId;
    END IF;

    -- Trava o promotor para que duas transacoes nao o especializem ao mesmo tempo
    PERFORM 1
       FROM promotor
      WHERE PromotorId = v_promotor
        FOR UPDATE;

    -- Procura o mesmo promotor na outra subclasse
    IF TG_TABLE_NAME = 'pessoa_promotor' THEN
        PERFORM 1 FROM organizacao     WHERE OrganizacaoId = v_promotor;
    ELSE
        PERFORM 1 FROM pessoa_promotor WHERE PessoaPId     = v_promotor;
    END IF;

    IF FOUND THEN
        RAISE EXCEPTION
            'Especializacao disjunta: o promotor % ja esta cadastrado como %.',
            v_promotor,
            CASE WHEN TG_TABLE_NAME = 'pessoa_promotor'
                 THEN 'organizacao' ELSE 'pessoa fisica' END
            USING ERRCODE = 'check_violation';
    END IF;

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

DROP TRIGGER IF EXISTS trg_pessoa_promotor_disjunto ON pessoa_promotor;

CREATE TRIGGER trg_pessoa_promotor_disjunto
BEFORE INSERT OR UPDATE OF PessoaPId ON pessoa_promotor
FOR EACH ROW
EXECUTE FUNCTION fn_verifica_promotor_disjunto();

DROP TRIGGER IF EXISTS trg_organizacao_disjunto ON organizacao;

CREATE TRIGGER trg_organizacao_disjunto
BEFORE INSERT OR UPDATE OF OrganizacaoId ON organizacao
FOR EACH ROW
EXECUTE FUNCTION fn_verifica_promotor_disjunto();