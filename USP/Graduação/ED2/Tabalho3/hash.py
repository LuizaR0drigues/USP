#estrutura da lista/tabela
class Dicio:
    def __init__(self, data, cont, codehash, qtd):
        self.palavra = data
        self.repeticoes = cont
        self.codehash = codehash
        self.qtd = qtd

 
def hash(palavra, TamTable):
    # Calculando o código hash de uma palavra e salvando na variável v
    v = 0
    for j in range(len(palavra)):
        v += v * 3 + ord(palavra[j])
        v = v % TamTable
        #print("Cada caractere: ", ord(palavra[j]), v)
    return v

def rehash(v, c1, c2, TamTable, i):
    # Código hash para colisões
    return (v + c1 * i + c2 * i**2) % TamTable

def leitura(tam):
    sentenca = input()
    texto = sentenca.split()
    palavra = {}
    vetor = []
    qtd =0
    for word in texto:
        if word in palavra:
            rep = texto.count(word)
            palavra[word].repeticoes = rep
            #qtd +=
        else:
            qtd += 1
            codehash = hash(word, tam)
            rep = texto.count(word)
            palavra[word] = Dicio(word, rep, codehash, qtd)
            vetor.append(palavra[word])
    return vetor, qtd

def qtdElem(tam, lista_palavra):                 
    
    #inicializo o aux com o primeiro elem
    aux = lista_palavra[0]
    #verificacao da palavra mais frequente e tratamento em caso de empate
    quant = 1
    for i in range(1, len( lista_palavra)):
        
        if lista_palavra[i].repeticoes > aux.repeticoes:
            aux = lista_palavra[i]
                #print(aux.palavra)
        elif lista_palavra[i].repeticoes == aux.repeticoes:
            if lista_palavra[i].palavra < aux.palavra:
                aux = lista_palavra[i]
                  # print(aux.palavra)
        quant +=1
    print(f"foram encontradas {quant} palavras diferentes")            
    print(f"palavra mais frequente = {aux.palavra}, encontrada {aux.repeticoes} vezes")
         
def remocao(wsear, vetor, c1, c2, tam, qtd):
     indice =0
     print(wsear)
     aux = False 
     aux = False  # Variável para controlar a quebra do loop externo
     for i, word in enumerate(vetor):
        if aux:
            break
        for palavra in wsear:
            if word.palavra == palavra:
                del vetor[i]
                print(f'{word.palavra} removida')
                if word.repeticoes > 1:
                    word.repeticoes -= 1
                #aux = True  # Define aux como True para quebrar o loop externo
                break  # Sai do loop interno após encontrar uma correspondência
            else:
                print(f"{word.palavra} não encontrada")
                aux = False


              
        '''
          if not any(palavra == word.palavra for word in vetor):
            print(f"{palavra} não encontrada") 
           # print(word.palavra, wsear)
            if word.palavra in wsear:
                print(word.palavra, wsear)
                print(f'{word.palavra} removida')
                #vetor[indice].palavra, vetor[indice].codehash, vetor[indice].repeticoes, vetor[indice].qtd= '##',None, None, None
                vetor.remove(word)
                if word.repeticoes >1:
                    word.repeticoes -= 1
        '''
            
     

     for i,aux in enumerate(vetor):
         Ncode =rehash(word.codehash, c1, c2, tam, i)
         aux.codehash = Ncode 
         #print(aux.palavra, aux.codehash, aux.repeticoes)         

# Testes
tam, c1, c2 = map(int, input().split())
codhash = []
lista_palavrapalavra = []
#print(tam, c1, c2)
while True:
    t = int(input())
    #print(t)
    if t == 0:
        break
    elif t == 1:
        #print(t)
        lista_palavra, quant = leitura(tam)
        
    elif t == 2: #exibir a qtd de palavras do dicionario e a palavra mais frequente
       qtdElem(tam, lista_palavra) 
    elif t ==3:
        n = int(input())
        wsearch = []
        for i in range(n):
            wsearch.append(input())

        for word in wsearch: 
            aux = False
            for item in lista_palavra: 
                if word  == item.palavra:
                    print(f'{word} encontrada {item.repeticoes}') 
                    aux = True
                    break
            if not aux:
                print(f'{word} nao encontrada')
                
    elif t==4:   
        num = int(input())
        aux = []
        wsearch = []
        for i in range(num):
            wsearch.append(input())
        
        remocao(wsearch,lista_palavra, c1, c2, tam, quant)
        '''for i,aux in enumerate(lista_palavra):
            print(aux.palavra, aux.codehash, aux.repeticoes)
            print(i)''' 
    elif t == 5:
         print("imprimindo a tabela hash")
         for i, aux in enumerate(lista_palavra):
             print(aux.palavra, aux.codehash) 


        

