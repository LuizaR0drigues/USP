import numpy as np
import matplotlib.pyplot as plt
import random
##Funções para a geração de Imagens
#Func01(i, j) =  i*j + 2*j
def func1(i, j):
    return (i*j + 2*j)

#Func02(i, j, q) =  |cois(i/q) + 2 * sin(j/q)|
def func2(i, j, q):
    return abs(np.cos(i/q) + 2*np.sin(j/q))

#Func03(i, j, q) =  |3*(i/q) - ((j/q)^(1/3))|
def func3(i, j, q):
    return abs(3*(i/q) -pow(j/q, 1/3))

#Func04(i, j, s) = random number | x e [-1, 1].
def func4(): 
    return random.random()

#Func05(i, j, 5) = randomwalk
def func5(s,c):
    # Inicializa a seed para garantir reprodutibilidade
    random.seed(s)

    # Cria uma matriz zerada
    matriz = np.zeros((c, c), dtype=int)

    # Define a posição inicial
    i, j, di, dj = 0, 0,0,0
    matriz[i,j] = 1  # posição inicial

    # Número de passos: 1 + C^2
    intervalo = 1 + c**2

    for _ in range(intervalo):
        #deslocamentos aleatórios entre [-1, 0, 1]
        di = random.randint(-1, 1)
        dj = random.randint(-1, 1)
        
        # Atualiza as posições 
        i = (i + di) % c
        j = (j + dj) % c
        #print("coordenadas: ", di, dj, "\ni, j: ", i, j)
        # Marca a nova posição
        matriz[i, j] = 1

    return matriz

#Define qual funcao foi escolhida pelo usuario
def set_func(f, i,j, q,s,c):

    if f ==1:
        return func1(i,j)
    elif f == 2:
        return func2(i,j, q)
    elif  f== 3:
        return func3(i, j, q)
    elif f == 4:
        return func4()
    elif f == 5:
        return func5(s,c) #retorna uma matriz
        
    else:
        print("Opçao incorreta!")   
        return None 
    
#funcao de normalização da matriz img que contem valores entre [0., 1.[ passando para valores entre[0,255]
def normalizacao(img):
    
    img = (img - img.min())/(img.max() - img.min())
    img *= 255 
    
    return img.astype(np.uint8)

##funcao de amostragem, onde dado uma matriz, seu tamanho e e tamanho lateral da nova imagem
##consegue digitalizar as coordenadas da "imagem real" a partir do uso de slicing(cortando) 
def amostragem(grid, c, n,):
    if n > c:
        print("Erro")
        return None
    #realiza o calculo de quantas regioes a img digital tera aka nova dimensao
    regioes = c//n

    ##nova imagem 
    new_grid  = grid[::regioes, ::regioes]
    
    return new_grid

#Funcao de Quantizacao
#dado uma imagem e o numero de bits(b) realiza a discretizacao da imagem 
def quantizacao(img, b):
    ##normalizando a matriz + conversao de float para inteiro sem sinal
    img = normalizacao(img)

    if b <= 0:
        print("Erro")
        return None
    #deixa apenas os B bits mais significativos e zera os outros
    img = img >> 8 - b
    img = img << 8 - b

    return img

#funcao de comaparacao com referencia
#dado uma img de refencia e uma imagem sintetica, realizar a  raiz do erro quadrático para calcular do erro, uma taxa que diz 
# #o quao semelhantes sao as imgs
def comp_ref(ref, grid):
    R = np.load(ref)
    rse = 0
    grid = grid.astype(dtype=float) #transforma a matriz em floats

    # raiz(coordanadas da img sintetica - img de referencia)
    rse = np.sum((grid- R)**2)
    print("{:.4f}".format(rse))

##funcao Gerador de imagens
#dado uma matriz zerada e alguns parametros, gera uma imagem a partir da amostragem e quantizacao e compara as imagens geradas
def gerador(f, grid,c, q,n,b,s, refe):

    #definindo os pontos da matriz
    xs = np.arange(0., 1., 1./c)
    ys = np.arange(0., 1., 1./c)
    
    #inicializa o seed do pacote random
    random.seed(s) 

    ##constroi a matriz de acordo com a funcao requerida
    if f != 5:
        for i, x in enumerate(xs):
            for j, y in enumerate(ys):
                grid[i,j] = set_func(f, i,j, q,s,c)
    else:
        grid = set_func(5, 0,0, 0,s,c) #substitui a matriz
   
    #realizando o processo de amostragem e quantizacao
    img = amostragem(grid, c, n)
    img_quant = quantizacao(img,b)

    #compara a imagem gerada com a referencia
    comp_ref(refe, img_quant)

    #salvando as imagens geradas
    #plt.imsave("img_a.png",img, cmap="grey")
    #plt.imsave("img_q.png",img_quant, cmap="grey")


def main():
## dados de entrada
    ref = input().rstrip()
    c = int(input()) #tamanho da imagem "real"
    f = int(input()) #tipo de funcão [1,5]
    q = int(input()) #paramentro q 
    n = int(input()) #tamanho lateral da img digital
    b = int(input()) #numero de bits da discretizacao
    s = int(input()) #seed

    ##matriz zerada com dimensao CxC
    matriz = np.zeros((c,c))

    #Gerando uma imagem sintétioca
    gerador(f,matriz,c, q,n,b,s, ref)

    
if __name__ == "__main__":
    main()
