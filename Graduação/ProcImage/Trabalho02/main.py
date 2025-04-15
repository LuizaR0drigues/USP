###########################################################################
# Disciplina: SCC0251  -> Trabalho 02: melhorias em imagens               #
# Luiza Rodrigues Cardoso - 1459332                                       #
###########################################################################
import imageio.v3 as iio
import matplotlib.pyplot as plt
import numpy as np
import sys

#Normalizacao e Quantizacao
#funcao de normalização da matriz img que contem valores entre [0., 1.[ passando para valores entre[0,255]
def normalizacao(img,c, m):
    img = (img - img.min())/(img.max() - img.min())
    img *= c
    img -= m
    return img

#dado uma imagem e o numero de bits(b) realiza a discretizacao da imagem 
def quantizacao(img, b):
    ##normalizando a matriz + conversao de float para inteiro sem sinal
    img = normalizacao(img, 255,0).astype(np.uint8)

    if b <= 0:
        print("Erro")
        return None
    #deixa apenas os B bits mais significativos da imagem
    img = img >> 8 - b
    img = img << 8 - b

    return img

##FUNCÕES DE REALCE 
#Histograma
#Computa a distribuição de intensidades de pixel em uma img
def histograma(img, tam):
    acumulador = np.zeros((tam,))
    h, w = img.shape
    for i in range(h):
        for j in range(w):
            acumulador[img[i, j]] += 1
    return acumulador

#Histograma Cumulativo
#Computa a proporcao de intensidades
def histo_cumulativo(h, L):
    acumulador = np.zeros((L,))
    acumulador[0] = h[0]
    for i in range(1, L):
        acumulador[i] = acumulador[i - 1] + h[i]
    return acumulador

#Funcao que aplica uma equalizacao no histograma
#T(z) = ((L-1)/ total_pixels) * Hc(z)
def transf(hc, img, total=None):
    h, w = img.shape
    L = 256  # níveis de cinza
    if total is None:
        total = float(h * w)
    new_img = np.zeros_like(img, dtype=np.uint8)
    aux = (L-1)/total
    for i in range(h):
        for j in range(w):
            z = img[i, j]
            new_val = aux * hc[z]
            new_img[i, j] = new_val
    
    return new_img.astype(np.uint8)

#Realiza a equalizacao de forma individual
def equaliza_indiv(imagens):
    img_eq =  []
    for img in imagens:
        h = histograma(img, 256)
        hc = histo_cumulativo(h, 256)
        img_eq.append(transf(hc, img))
        
    return img_eq

#realiza a equalizacao de forma conjunta, i.e, para n imagens
def equaliza_conj(imagens):
    h_conjunto = np.zeros(256)
    for img in imagens:
        h_conjunto += histograma(img, 256)
    
    hc_conjunto = histo_cumulativo(h_conjunto, 256)
    total_pixels = sum(img.size for img in imagens)  # total de pixels do conjunto
    imagens_eq = [transf(hc_conjunto, img, total=total_pixels) for img in imagens]
    
    return imagens_eq, hc_conjunto

#Define a equação do realce gama
def realce_gama(img, gama):
    img_norm  = normalizacao(img.astype(float), 1.0, 0)
    img_gama = img_norm**(1/gama)
    img_gama = normalizacao(img_gama,255, 0).astype(np.uint8)
    return img_gama
#Aplica a correção gama na imagem
def correc_gamma(imagens, gama):
    imagens_gama = [realce_gama(img, gama) for img in imagens]
    return imagens_gama
  
#Funcao de Superresolucao
#Ĥ terá o dobro do tamanho da img orginal
def supperresolucao(imagens, high_img=None):  # high_img é opcional
    l1, l2, l3, l4 = imagens #gerando as 4 imagens li
    h, w = l1.shape #obtendo as dimensoes da imagem

    #matriz com dimensões duplicadas -> matris de superresolução
    super_img = np.zeros((2*h, 2*w), dtype=l1.dtype)
    
    #Preenchimento dos pixels da matriz de superresolução
    for i in range(h):
        for j in range(w):
            #superior esquerdo
            super_img[2*i,   2*j]   = l1[i,j]  # Pixel l1
            #superior direito
            super_img[2*i,   2*j+1] = l2[i,j]  # Pixel l2
            #inferior esquerdo
            super_img[2*i+1, 2*j]   = l3[i,j]  # Pixel l3
            #inferior direito
            super_img[2*i+1, 2*j+1] = l4[i,j]  # Pixel l4
    
    #Plotando a Super_img
    plt.imshow(super_img, cmap="gray")
    plt.title("Imagem com Superresolução")
    plt.axis('off')
    plt.show()
    return super_img

#Transformação Geométricas - Rotação, Translacao e Scale
#matriz inv de rotacao
def r_inversa(theta):
    #theta = np.radians(theta)
    return np.array([[np.cos(theta), np.sin(theta), 0],
            [-np.sin(theta), np.cos(theta), 0],
            [0,             0,             1]])

#matriz inv de escala
def s_inversa(si, sj):
    return np.array([[1.0/si, 0 , 0],
            [0, 1.0/si, 0 ],
            [0, 0 , 1]])

#matriz inv de translação
def t_inversa(ti, tj):
    return np.array([[1, 0, -ti],
            [0, 1, -tj],
            [0, 0, 1]])

#interpolacao bilinear 
def interpo_bilinear(img, cont_i, cont_j):
    i0 = np.floor(cont_i).astype(int)
    j0 =  np.floor(cont_j).astype(int)

    i1 =  i0 + 1 if i0 < img.shape[0]-1 else i0
    j1 = j0 + 1 if j0 < img.shape[1]-1 else j0

    #definindo os 4 pontos da imagem
    c0 = img[i0,j0]
    c1 = img[i0,j1]
    c2 = img[i1,j0]
    c3 = img[i1,j1]

    #definindo as distancias em i, j
    s = cont_j - j0
    t = cont_i - i0

    #equações 
    c23 = (1-s)*c2 + s*c3
    c01 = (1-s)*c0 + s*c1
    c   = (1-t)*c01 + t*c23

    return c

#Transformacao Geometrica
def transf_geo(theta, img):
    h, w =  img.shape

    #gerando a m^-1 = S^−1 T^−1 R^−1
    new_img =  np.zeros_like(img)
    mat_inver = s_inversa(1.0,1.0)
    #mat_inver =  mat_inver@t_inversa(-h/2.0, -w/2.0)
    mat_inver =  mat_inver@r_inversa(theta)
    #mat_inver =  mat_inver@t_inversa(h/2.0, w/2.0)
    for i in range(h):
        for j in range(w):
            p = np.array([i, j, 1]) #vetor coord homogeneas
            pl = mat_inver@p #produto vetorial entre as matrizes m e p

            new_i = np.round(pl[0]) #nova linha
            new_j = np.round(pl[1]) #nova coluna

            #verificando se as novas coordenadas estão de acordo com a imagem original
            #aplicacao da interpolacao bilinear
            if not (new_i >= h or new_j >= w or new_i < 0 or new_j < 0):
                new_img[i, j] = interpo_bilinear(img, new_i, new_j)
            else:
                new_img[i, j] = 0
    return new_img


#Computa a diferença entre duas imagens
def comp_ref(ref, grid):
    dim_ref = ref.shape[0]
    dim_grid = grid.shape[0]

    grid = grid.astype(float)
    ref = ref.astype(float)
    
    rse = np.sqrt(np.sum((grid - ref) ** 2) / (dim_ref * dim_grid))
    print("{:.4f}".format(rse))

#Funcao de Processamento 
#carrega as imagens para o processamento
def carrega_images(baixa_resol, alta_resol):
    paths = [f"{baixa_resol}{x}.png" for x in range(4)]

    low_imgs = [iio.imread(path) for path in paths]
    high_img = iio.imread(alta_resol)
    return *low_imgs, high_img
#Dado um valor entre[0,3], eh aplicado uma função de realce nas imagens li, i e [1,4]
def process_images(baixa_resol, alta_resol, f, gama):
    l1, l2, l3, l4, high_img = carrega_images(baixa_resol, alta_resol)
    imagens = [l1, l2, l3, l4]
    
    if f == 0: #sem realce
        plot_images_e_histograms(imagens,["Img1 Eq", "Img2 Eq", "Img3 Eq", "Img4 Eq"], "Sem realce")
        return *imagens, high_img
    #Realce baseado em Histograma Cumulativo Individual
    elif f == 1:
        imagens_eq = equaliza_indiv(imagens)
        plot_images_e_histograms(imagens_eq,["Img1 Eq", "Img2 Eq", "Img3 Eq", "Img4 Eq"],"Equalizacao Individual")

        return *imagens_eq, high_img
    
    #Realce baseado em Histograma Cumulativo em Conjunto
    elif f == 2:
        imagens_eq, hc_conjunto = equaliza_conj(imagens)
        plot_images_e_histograms(imagens_eq,["Img1 Eq", "Img2 Eq", "Img3 Eq", "Img4 Eq"],"Equalizacao Conjunta")

        return *imagens_eq, high_img
    
    #Realce Gamma
    elif f == 3:
        imagens_gama = correc_gamma(imagens, gama) 
        plot_images_e_histograms(imagens_gama,["Img1 γ", "Img2 γ", "Img3 γ", "Img4 γ"],f"Realce Gamma (γ = {gama})")
                       
        return *imagens_gama, high_img
    
    else:
        print("Valor invalido")
        return None

def plot_images_e_histograms(images, titles, main_title):
    plt.figure(figsize=(15, 10))
    
    for i, (img, title) in enumerate(zip(images, titles)):
        plt.subplot(2, len(images), i+1)
        plt.imshow(img, cmap='gray')
        plt.title(title)
        plt.axis('off')
        
        plt.subplot(2, len(images), i+1+len(images))
        hist = histograma(img, 256)
        plt.bar(range(256), hist)
        plt.title(f'Histograma {title}')
    
    plt.suptitle(main_title)
    plt.tight_layout()
    plt.show()

def main():
    #entrada
    baixa_resol = sys.stdin.readline().strip()
    alta_resol = sys.stdin.readline().strip()
    f = int(input())
    gama = float(input())
    theta =  float(input())

    # Processamento das Imagens a partir das funções de realce
    *imagens, high_img = process_images(baixa_resol, alta_resol, f, gama)
    
    #Gerando uma imagem com superresolução
    img_superreso = supperresolucao(imagens, high_img)
   
    #Aplicando trasnformação geometrica na img
    img_geo = transf_geo(theta, img_superreso)

    #Calculando o erro entre a imagem de alta qualidade e a imagem resultante
    comp_ref(high_img, img_geo)

    #Plotando a img transformada/final
    plt.imshow(img_geo, cmap="gray")
    plt.title("Imagem Final")
    plt.axis('off')
    plt.show()


if __name__ == "__main__":
    main()