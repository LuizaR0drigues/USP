CREATE TABLE pessoa (
    id bigint PRIMARY KEY,
    nome varchar(100) NOT NULL
);

CREATE TABLE evento (
    id bigint PRIMARY KEY,
    nome varchar(100) NOT NULL
);

CREATE TABLE atividade (
    id bigint PRIMARY KEY,
    evento_id bigint NOT NULL REFERENCES evento(id),
    titulo varchar(100) NOT NULL
);

CREATE TABLE espaco (
    id bigint PRIMARY KEY,
    capacidade integer NOT NULL CHECK (capacidade > 0)
);

CREATE TABLE sessao (
    id bigint PRIMARY KEY,
    atividade_id bigint NOT NULL REFERENCES atividade(id),
    espaco_id bigint NOT NULL REFERENCES espaco(id),
    requer_inscricao boolean NOT NULL,
    limite_vagas integer
);

CREATE TABLE inscricao_evento (
    pessoa_id bigint REFERENCES pessoa(id),
    evento_id bigint REFERENCES evento(id),
    status varchar(20) NOT NULL,
    PRIMARY KEY (pessoa_id, evento_id)
);

CREATE TABLE inscricao_sessao (
    pessoa_id bigint REFERENCES pessoa(id),
    sessao_id bigint REFERENCES sessao(id),
    status varchar(20) NOT NULL,
    PRIMARY KEY (pessoa_id, sessao_id)
);