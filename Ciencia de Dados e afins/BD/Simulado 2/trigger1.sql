
DROP TRIGGER IF EXISTS trg_inscricao_conflito_horario ON inscricao;

CREATE TRIGGER trg_inscricao_conflito_horario
BEFORE INSERT OR UPDATE OF CredenciamentoId, AtividadeId, NumeroSessao ON inscricao
FOR EACH ROW
EXECUTE FUNCTION fn_verifica_conflito_inscricao();
