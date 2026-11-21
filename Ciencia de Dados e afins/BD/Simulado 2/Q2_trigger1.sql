CREATE OR REPLACE FUNCTION fn_coerencia_inscricao
RETURNS TRIGGER AS $$
DECLARE 
    v_insc_palestra
BEGIN
    SELECT e.EventoId, cred.EventoId
     FROM evento e
     JOIN credenciamento cred ON e.EventoId = cred.EventoId
     JOIN inscricao ins ON inscricao.credenciamentoId = cred.credeciamentoID
    WHERE ins.inscriaoid = NEW.inscricaoid

END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER tg_coerencia_inscricao
BEFORE INSERT OR UPDATE OF inscricao 
FOR EACH ROW
EXECUTE FUNCTION tg_coerencia_inscricao();
