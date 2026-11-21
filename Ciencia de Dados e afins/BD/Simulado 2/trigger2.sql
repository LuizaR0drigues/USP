
-- ------------------------------------------------------------
-- Trigger 2: Limite de vagas (inscricao com sessao)
-- Somente ouvintes ocupam vaga.
-- ------------------------------------------------------------
CREATE OR REPLACE FUNCTION fn_verifica_limite_vagas()
RETURNS TRIGGER AS $$
DECLARE
    v_vagas    INTEGER;
    v_ocupadas INTEGER;
BEGIN
    -- Somente ouvintes ocupam vaga: outros papeis passam direto
    IF NEW.Papel <> 'ouvinte' THEN
        RETURN NEW;
    END IF;

    -- Trava a linha da sessao para serializar inscricoes concorrentes
    -- (sem isso, duas transacoes simultaneas podem estourar o limite).
    SELECT Vagas
      INTO v_vagas
      FROM sessao
     WHERE AtividadeId  = NEW.AtividadeId
       AND NumeroSessao = NEW.NumeroSessao
       FOR UPDATE;

    -- Conta os ouvintes ja inscritos
    -- (no UPDATE, ignora a propria linha que esta sendo alterada).
    SELECT COUNT(*)
      INTO v_ocupadas
      FROM inscricao
     WHERE AtividadeId  = NEW.AtividadeId
       AND NumeroSessao = NEW.NumeroSessao
       AND Papel = 'ouvinte'
       AND (TG_OP = 'INSERT' OR InscricaoId <> NEW.InscricaoId);

    IF v_ocupadas >= v_vagas THEN
        RAISE EXCEPTION 'Sessao % da atividade % esgotada: % de % vagas preenchidas.',
            NEW.NumeroSessao, NEW.AtividadeId, v_ocupadas, v_vagas
            USING ERRCODE = 'check_violation';
    END IF;

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

DROP TRIGGER IF EXISTS trg_inscricao_limite_vagas ON inscricao;

-- Papel incluido: instrutor/palestrante que vira ouvinte passa a ocupar vaga
CREATE TRIGGER trg_inscricao_limite_vagas
BEFORE INSERT OR UPDATE OF AtividadeId, NumeroSessao, Papel ON inscricao
FOR EACH ROW
EXECUTE FUNCTION fn_verifica_limite_vagas();

