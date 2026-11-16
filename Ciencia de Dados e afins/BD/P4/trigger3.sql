CREATE OR REPLACE FUNCTION fn_valida_requer_inscricao_sessao()
RETURNS TRIGGER AS $$
DECLARE
    v_requer BOOLEAN;
BEGIN
    --Busca na tabela sessao se ela exige inscricao
    SELECT requer_inscricao
        INTO v_requer
        FROM sessao
     WHERE id = NEW.sessao_id;

    -- verifica se é false
    IF v_requer = false THEN
        RAISE EXCEPTION 'Inscrição rejeitada!Esta sessão não exige inscrição!.';
    END IF;
    
    RETURN NEW;

END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER tg_valida_requer_inscricao_sessao
BEFORE INSERT OR UPDATE ON inscricao_sessao
FOR EACH ROW
EXECUTE FUNCTION fn_valida_requer_inscricao_sessao();