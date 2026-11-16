CREATE TABLE Clientes(
    ClienteID BIGINT GENERATED ALWAYS AS IDENTITY,
    NomeC TEXT NOT NULL,
    Email  TEXT NOT NULL, 
    Cidade TEXT,

    CONSTRAINT pk_clientes
        PRIMARY KEY (ClienteID),

    CONSTRAINT uq_clientes_email
        UNIQUE (Email)
);

CREATE TABLE Restaurantes(
    RestauranteID  BIGINT GENERATED ALWAYS AS IDENTITY,
    NomeR TEXT NOT NULL,
    Categoria TEXT NOT NULL,
    TaxaEntrega NUMERIC,

    CONSTRAINT pk_restaurantes
        PRIMARY KEY (RestauranteID),

    CONSTRAINT uq_restaurantes_nome
        UNIQUE (NomeR)
);


CREATE TABLE Pedidos(
    PedidoID BIGINT GENERATED ALWAYS AS IDENTITY,
    ClienteID BIGINT NOT NULL,
    RestID BIGINT NOT NULL,
    Data DATE NOT NULL,
    Status TEXT NOT NULL,
    Valor NUMERIC,

    CONSTRAINT pk_pedidos
        PRIMARY KEY(PedidoID),
    
    CONSTRAINT uq_pedido_cliente_rest_data
        UNIQUE (ClienteID, RestID, Data),
    
    CONSTRAINT fk_pedido_cliente
        FOREIGN KEY(ClienteID)
        REFERENCES Clientes(ClienteID)
        ON DELETE RESTRICT
        ON UPDATE CASCADE,

    CONSTRAINT fk_pedido_restaurante
        FOREIGN KEY(RestID)
        REFERENCES Restaurantes(RestauranteID)
        ON DELETE RESTRICT
        ON UPDATE CASCADE,

    CONSTRAINT ck_pedido_status
        CHECK(Status in (
            'Recebido',
            'Em preparo',
            'Entregue',
            'Cancelado'
        ))
);

CREATE TABLE Entregadores (
    EntregadorID BIGINT GENERATED ALWAYS AS IDENTITY,
    NomeE TEXT NOT NULL,
    Veiculo TEXT NOT NULL,
    Placa TEXT,

    CONSTRAINT pk_entregadores
        PRIMARY KEY (EntregadorID),

    CONSTRAINT uq_entregadores_nome
        UNIQUE (NomeE),

    CONSTRAINT ck_entregadores_veiculo
        CHECK (Veiculo IN ('Moto', 'Bicicleta', 'Carro')),

    CONSTRAINT ck_entregadores_placa
        CHECK (
            Veiculo = 'Bicicleta'
            OR Placa IS NOT NULL
        )
);

CREATE TABLE Entrega_Pedido (
    PedidoID BIGINT,
    EntregadorID BIGINT,
    DataEntrega DATE NOT NULL,

    CONSTRAINT pk_entrega_pedido
        PRIMARY KEY (PedidoID, EntregadorID),

    CONSTRAINT fk_entrega_pedido
        FOREIGN KEY (PedidoID)
        REFERENCES Pedidos (PedidoID)
        ON DELETE CASCADE
        ON UPDATE CASCADE,

    CONSTRAINT fk_entrega_entregador
        FOREIGN KEY (EntregadorID)
        REFERENCES Entregadores (EntregadorID)
        ON DELETE RESTRICT
        ON UPDATE CASCADE
);