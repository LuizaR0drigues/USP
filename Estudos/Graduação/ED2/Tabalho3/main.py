class Dicio:
    def __init__(self, data, cont):
        self.palavra = data
        self.repeticoes = cont

 
def hash(palavra, TamTable):
    # Calculando o código hash de uma palavra e salvando na variável v
    v = 0
    for caracter in palavra:
        v += v * 3 + ord(caracter) 
        v = v % TamTable
        #print("Cada caractere: ", ord(palavra[j]), v)
    return v

def rehash(v,  c1, c2, TamTable, i):
    # Código hash para colisões 
    return (v + c1 * i + c2 * i**2) % TamTable

def procura(palavra, vetor, c1, c2):
    tam = len(vetor)
    nv = hash(palavra, tam)
    print('hash inicial', nv, palavra)
    scode = nv
    i = 0
    primeir_po__vazia = -1
    
    while i < tam:
        scode = rehash(nv, c1, c2, tam, i)
        print(f'Tentativa {i}: scode = {scode}, palavra na tabela = {vetor[scode].palavra}')
        
        if vetor[scode].palavra == '##':  # Espaço vago, nunca teve nada
            return scode, -1
        
        elif vetor[scode].palavra == '**':  # Em algum momento foi ocupado
            if primeir_po__vazia == -1:  # Guardo o primeiro espaço vago
                primeir_po__vazia = scode
        
        elif vetor[scode].palavra == palavra:  # Encontrou a palavra, retorna a posição
            return scode, 1
        
        i += 1  # Incrementa i para tentar o próximo índice
    
    if primeir_po__vazia != -1:
        return primeir_po__vazia, 2  # Já foi um lugar ocupado e pode ser inserido uma nova palavra
    
    return -1, -1  # Tabela cheia ou erro


def leitura(vetor, tam, c1, c2):
    # Dividindo a sequência de entrada em pequenos blocos
    sentenca = input()
    texto = sentenca.split()
    
    qtd = 0  # Quantidade de palavras no dicionário
    
    # Analisando o hash de cada palavra
    for word in texto:
        posicao, flag = procura(word, vetor, c1, c2)
        
        if flag == -1 or flag == 2:  # Espaço vago ou novas palavras
            vetor[posicao] = Dicio(word, 1)
            qtd += 1
        
        elif flag == 1:  # Essa palavra já está no dicionário
            vetor[posicao].repeticoes += 1
    
    return vetor, qtd


def leitura(vetor, tam, c1, c2):
    # Dividindo a sequência de entrada em pequenos blocos
    sentenca = input()
    texto = sentenca.split()
    
    qtd = 0  # Quantidade de palavras no dicionário
    
    # Analisando o hash de cada palavra
    for word in texto:
        posicao, flag = procura(word, vetor, c1, c2)
        
        if flag == -1 or flag == 2:  # Espaço vago ou novas palavras
            vetor[posicao] = Dicio(word, 1)
            qtd += 1
        
        elif flag == 1:  # Essa palavra já está no dicionário
            vetor[posicao].repeticoes += 1
    
    return vetor, qtd

# Exemplo de uso

tam, c1, c2 = 15, 2, 2  # Tamanho da tabela e constantes para rehash
vetor = [Dicio('##', None) for _ in range(tam)]

# Inserindo algumas palavras
lista_palavra, quant = leitura(vetor, tam, c1, c2)

# Exibir a tabela de hash resultante
print("Tabela de hash resultante:")
for i, item in enumerate(lista_palavra):
    if item.palavra != '##' and item.palavra != '**':
        print(f"Posição {i}: Palavra = {item.palavra}, Repetições = {item.repeticoes}")
