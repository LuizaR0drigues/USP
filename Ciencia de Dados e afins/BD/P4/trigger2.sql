CREATE OR REPLACE FUNCTION fn_valida_status_inscricao_evento()
RETURNS TRIGGER AS $$
BEGIN
    --removendo espacos e convertendo pra minuscula
    NEW.status := LOWER(TRIM(NEW.status));

    -- confirmado -> confirmada
    IF NEW.status = 'confirmado' THEN
        NEW.status := 'confirmada';
    END IF;

    --rejitando nulos e restringindo o dominio
    IF NEW.status IS NULL OR new.status NOT IN ('pendente', 'confirmada', 'cancelada') THEN
        RAISE EXCEPTION 'Status inválido: "%". Valores aceitos: pendente, confirmada ou cancelada.', new.status;
    END IF;

    -- retorna a linha modificada pra gravação
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER tg_valida_status_inscricao_evento
BEFORE INSERT OR UPDATE ON inscricao_evento
FOR EACH ROW
EXECUTE FUNCTION fn_valida_status_inscricao_evento();