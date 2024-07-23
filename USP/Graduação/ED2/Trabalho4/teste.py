#Luiza Rodrigues Cardoso - 14593332
#Uma classe que guardara o valor, peso, e valor unitario de cada elemento
class Item:
    def __init__(self, valor, peso, valunit, index):
        self.valor = valor
        self.peso = peso
        self.valorunit = valunit
        self.indice = index

# Algoritmo de Programação Dinâmica 
def mochila_prog_dinamica(vetor, capacidade):
    n = len(vetor)
    # Cria a tabela dp com (n+1) x (capacidade+1)
    dp = [[0 for _ in range(capacidade + 1)] for _ in range(n + 1)]

    # Construindo a tabela dp em bottom-up
    for i in range(1, n + 1):
        for w in range(1, capacidade + 1):
            if vetor[i-1].peso <= w:
                dp[i][w] = max(dp[i-1][w], dp[i-1][w - vetor[i-1].peso] + vetor[i-1].valor)
            else:
                dp[i][w] = dp[i-1][w]

    # O valor máximo estará em dp[n][capacidade]
    valor_maximo = dp[n][capacidade]

    # achando os itens
    w = capacidade #usando uma copia
    itens_selecionados = []
    for i in range(n, 0, -1):
        if valor_maximo <= 0:
            break
        # Se o valor na célula dp[i][w] é diferente de dp[i-1][w], então o item i-1 foi incluído
        if valor_maximo != dp[i-1][w]:
            itens_selecionados.append(i-1)
            valor_maximo -= vetor[i-1].valor
            w -= vetor[i-1].peso

    # Os itens em ordem reversa
    itens_selecionados.reverse()
    return dp[n][capacidade], itens_selecionados


# Algoritmo Guloso
def mochila_gulosa(vetor, cap):
    n = len(vetor)
    valor_total, peso = 0, 0
    itens_selecionados = []

    # Ordena o vetor com base no valor unitário em ordem decrescente
    vetor.sort(key=lambda item: item.valorunit, reverse=True)
    
    for i in range(n): 
         if peso + vetor[i].peso> cap:#caso a mochila esteja cheia
            break
         else:
            peso +=  vetor[i].peso
            valor_total += vetor[i].valor
            itens_selecionados.append(vetor[i].indice)
    
    return valor_total, itens_selecionados

#Main
capacidade, quantidade_itens = map(int, input().split())
vetor = []

for i in range(quantidade_itens):
    peso, valor = map(int, input().split())
    vetor.append(Item(valor, peso, round(valor/peso, 2), i))

# programação dinâmica
valor_maximo, itens_selecionados_prog_dinamica = mochila_prog_dinamica(vetor, capacidade)

# algoritmo guloso
valor_guloso, itens_selecionados_guloso = mochila_gulosa(vetor, capacidade)

# itens selecionados pela programação dinâmica e guloso
for aux in itens_selecionados_prog_dinamica:
        print(aux, end=' ') 
print()

for aux2 in itens_selecionados_guloso:
        print(aux2, end=' ') 
print()

# valor total gerado pela programação dinâmica e pelo algoritmo guloso
print(valor_maximo, valor_guloso)

#a porcentagem do valor obtido pelo algoritmo guloso em relação ao valor ótimo
porcentagem = (valor_guloso / valor_maximo) * 100.0
print(f'{porcentagem:.2f}')
