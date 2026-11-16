CREATE OR REPLACE FUNCTION fn_verifica_limitacao_evento()
RETURNS TRIGGER AS $$
DECLARE 
    v_capacidade INTEGER;
BEGIN
    IF NEW.limite_vagas IS NOT NULL THEN
        
        -- encontrando o valor de capacidade
        SELECT capacidade
            INTO v_capacidade
            FROM sessao s
         WHERE id =  NEW.evento_id;
   
    -- verificando se o limite de vagas é superior à capacidade do evento
    IF NEW.limite_vagas > v_capacidade THEN
        RAISE EXCEPTION 'Evento com capacidade limitada! Espere uma nova chamada ou vagas serem abertas.';
    END IF;
END IF;

END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER verifica_limitacao_evento
BEFORE INSERT OR UPDATE OF limite_vagas, espaco_id ON sessao
FOR EACH ROW
EXECUTE FUNCTION fn_verifica_limitacao_evento();