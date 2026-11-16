CREATE OR REPLACE FUNCTION verifica_limite()
RETURNS trigger as $$
DECLARE
    v_limite integer;
    v_ocupacao integer;
BEGIN
    -- verifica se a incrição esta como 'confirmada'
    -- updates nao disparam o trigger novamente
    IF NEW.status = 'confirmada' AND (TG_OP = 'INSERT' or OLD.status IS DISTINCT FROM 'confirmada') then

        -- buscando o limite da sessao
        SELECT COALESCE(s.limite_vagas, e.capacidade)
            into v_limite
            from sessao s
            join espaco e ON e.id=s.espaco_id
        where s.id= NEW.sessao_id;

         -- contatgem de qunatas inscricoes tao confirmada
         SELECT COUNT(*)
            into v_ocupacao
            from inscricao_sessao
            WHERE sessao_id =  NEW.sessao_id
                AND status = 'confirmada';
        
        -- verificaçao de limite
        IF v_ocupacao >= v_limite then
            RAISE EXCEPTION 'Limite máximo de participantes (%) atingido para essa sessão.', v_limite;
        END IF;
    END IF;

    RETURN NEW;
    
END;
$$ LANGUAGE plpgsql;

DROP TRIGGER IF EXISTS tg_verifica_limite ON inscricao_sessao;
CREATE TRIGGER tg_verifica_limite
BEFORE INSERT OR UPDATE ON inscricao_sessao
FOR EACH ROW
EXECUTE FUNCTION verifica_limite();

