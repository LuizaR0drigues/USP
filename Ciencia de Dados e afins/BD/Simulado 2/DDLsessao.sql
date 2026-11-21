/* ENUNCIADO
Novo requisito: uma sessão poderá utilizar simultaneamente mais de um espaço (por
exemplo, um auditório e uma sala auxiliar). Hoje sessao.EspacoId associa um único
espaço. Modifique o esquema para atender ao requisito, preservando as associações já
existentes

*/
CREATE TABLE espaco_sessao (
    id             INTEGER NOT NULL,
    NumeroSessao   INTEGER      NOT NULL,      -- chave parcial
    EspacoId       INTEGER,                    -- pode ficar sem espaco definido
    
    CONSTRAINT pk_espaco_sessao PRIMARY KEY (NumeroSessao, EspacoId),
    CONSTRAINT fk_sessao_espaco
        FOREIGN KEY (EspacoId) REFERENCES espaco (EspacoId)
        ON DELETE SET NULL ON UPDATE CASCADE
);