#Luiza Rodrigues Cardoso - 1459332 :)
#Definições 
class Item: #definindo uma classe que guardara os valores de peso e valores dos itens que almejamos guaradar na mochila
    def __init__(self, valor, pes0, unitval):
        self.valor = valor
        self.peso = peso
        self.valorunit = unitval

#Paradigma Guloso
#abocanha o objeto de maior valor especifico dentre os objetos disponiveis
def backpackGreedy(vetor,  q):
    cap = q-1
    n = len(vetor)
    print('tam', n)
    aux = [0] * n
    valorf = 0

    # Sort the vector based on unit value (valorunit) in descending order
    vetor.sort(key=lambda item: item.valorunit, reverse=True)

    j = 0
    while j < n and vetor[j].peso <= cap:
        print(vetor[j].peso, cap)
        aux[j] = 1
        cap -= vetor[j].peso  # Reducing the capacity in each iteration
        print(cap)
        valorf += vetor[j].valor
        
        j += 1
        

    '''if j < n:
        aux[j] = cap / vetor[j].peso
        valorf += vetor[j].valor * aux[j]
        print('Partial selection for:', vetor[j].valor, 'Fraction:', aux[j], valorf)
'''
    return aux,valorf, j

# Algoritmo de Programação Dinâmica para o Problema da Mochila
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

    # Para encontrar quais itens foram incluídos
    w = capacidade
    itens_selecionados = []
    for i in range(n, 0, -1):
        if valor_maximo <= 0:
            break
        # Se o valor na célula dp[i][w] é diferente de dp[i-1][w], então o item i-1 foi incluído
        if valor_maximo != dp[i-1][w]:
            itens_selecionados.append(i-1)
            valor_maximo -= vetor[i-1].valor
            w -= vetor[i-1].peso

    # Os itens selecionados estão na ordem reversa
    itens_selecionados.reverse()
    return dp[n][capacidade], itens_selecionados

p, q = map(int, input().split()) #leitura do pexo maximo e qtdd de itens
vet = []

for i in range(q):
    peso, valor = map(int, input().split())
    vet.append(Item(valor, peso, round(valor/peso, 3)))

# Print items
for i in range(q):
    print('Item:', i+1, 'Weight:', vet[i].peso, 'Value:', vet[i].valor, 'Unit Value:', vet[i].valorunit)

guloso, valorfinal, indice = backpackGreedy(vet, p)  # Pass the capacity (p) to the function
valor_maximo, itens_selecionados = mochila_prog_dinamica(vet, q)  # Chama a função com a capacidade
print('Selected fractions:', guloso, indice, valorfinal)
print(valor_maximo, itens_selecionados)

'''
    i = 0 
    # Seleciona os itens enquanto houver capacidade
    while i < n and vetor[i].peso <= cap:
        print('test',vetor[i].valor, vetor[i].indice)
    
        cap -= vetor[i].peso
        valor_total += vetor[i].valor
        itens_selecionados.append(vetor[i].indice)
        i +=1'''