#estrutura da lista/tabela
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
    #print('hash', nv, palavra)
    scode = nv
    i = 0
    primeir_po__vazia =-1 
    while i < tam:
        scode = rehash(nv, c1, c2, tam, i) 
        if vetor[scode].palavra == '##':
           return scode, -1# Espaço vago, nunca teve nada
             
        elif vetor[scode].palavra == '**':  # Em algum momento foi ocupado
         #guardo o primeiro espaço vago
            primeir_po__vazia = scode
        
         
        elif vetor[scode].palavra == palavra: 
            #encontrou uma palavra no dicionario
            return scode, 1
        
        elif primeir_po__vazia != -1:
            
            return primeir_po__vazia, 2 #ja foi um lugar ocupado e pode ser inserido uma nova palavra
        i += 1  # Incrementa i para tentar o próximo índice
         
    return -1, -1 #tabela cheia ou erro 

    


def leitura(vetor, c1, c2):
    #dividindo a sequenca de entrada em pequenos blocos
    sentenca = input()
    texto = sentenca.split()
    
    qtd = 0 #quantidade de palavras no dicio
     
    #analisando o hash de cada palavra
    for  word in texto: 
        pos, flag = procura(word, vetor, c1, c2)
        
        if flag == -1 or flag == 2: #espaço vago, novas palavr #-1, posição nunca ocupada; #2, posição ocupada previamentea
            qtd += 1
            vetor[pos]= Dicio(word, 1)
            

        elif flag == 1: #essa palavra ja esta no dicionario 
            vetor[pos].repeticoes += 1
         
    return vetor, qtd

def qtdElem(tam, lista_palavra, qtd):                 
    tam =len(lista_palavra)-1
    i = 0
    #inicializo o aux com o primeiro elem
    while i< len(lista_palavra) and lista_palavra[i].palavra =='##':
       i += 1

       if i == len(lista_palavra):
           print('Nenhuma palavra')
           return
    #verificacao da palavra mais frequente e tratamento em caso de empate
    auxfreq = lista_palavra[i].palavra
    maxrep = lista_palavra[i].repeticoes
 
    
    for wsearch in lista_palavra:
        if wsearch.palavra == '##' or wsearch.palavra == '**':
            continue
        if wsearch.repeticoes > maxrep:
            auxfreq = wsearch.palavra
            maxrep = wsearch.repeticoes
        elif wsearch.repeticoes ==  maxrep:#lexografia
            if wsearch.palavra < auxfreq:
                auxfreq = wsearch.palavra
                maxrep = wsearch.repeticoes
        else:
            auxfreq = auxfreq
            maxrep = maxrep
       
    print(f"foram encontradas {qtd} palavras diferentes")            
    print(f"palavra mais frequente = {auxfreq}, encontrada {maxrep} vezes")
         
def remocao(wsear, vetor, c1, c2, tam, qtd):
    
    for aux in (wsear):
       
        pos, flag = procura(aux, vetor, c1, c2)
        
        if flag == 1:
            vetor[pos].palavra = '**'
            vetor[pos].qtd = None
            qtd -=1
            print(f'{aux} removida')
        
        else:
            print(aux, 'nao encontrada')
           
    return qtd
 
# Testes
tam, c1, c2 = map(int, input().split())
codhash = []
# Criando a lista de objetos Dicio com valores padrão 
lista_palavra = [Dicio('##', None) for _ in range(tam)] 
quant = 0
while True:
    t = int(input())
    if t == 0:
        break
    elif t == 1:
        lista_palavra, adicionado = leitura(lista_palavra, c1, c2)
        quant += adicionado
        
    elif t == 2: #exibir a qtd de palavras do dicionario e a palavra mais frequente
       qtdElem(tam, lista_palavra, quant) 
    elif t ==3:
        n = int(input())
        wsearch = []
        for i in range(n):
            wsearch.append(input())
       
        for word in wsearch: 
            encontrado= False
            for item in lista_palavra:
                if word  == item.palavra:
                    print(f'{word} encontrada {item.repeticoes}') 
                    encontrado = True
                    break
            if not encontrado:
                print(f'{word} nao encontrada')
                
    elif t==4:  #remove de elementos 
        num = int(input())
        aux = []
        wsearch = []
        for i in range(num):
            wsearch.append(input())
        
        quant =remocao(wsearch,lista_palavra, c1, c2, tam, quant)
        
    elif t == 5: #impressao da tabela hash
         print("imprimindo tabela hash")
         for i, item in enumerate(lista_palavra):
            if item.palavra != '##' and item.palavra != '**' :
                print(f"{item.palavra} {i}")
         print('fim da tabela hash')
    else:
        break



        

