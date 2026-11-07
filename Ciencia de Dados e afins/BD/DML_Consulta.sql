SELECT
    P.PedidoID,
    P.Data,
    C.NomeC,
    R.NomeR
FROM Pedidos P
JOIN Clientes C
    ON P.ClienteID =  C.clienteid
JOIN restaurantes R
    ON P.RestID = R.restauranteid
WHERE P.Status =  'Entregue';

