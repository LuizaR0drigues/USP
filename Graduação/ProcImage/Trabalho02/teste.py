import imageio.v3 as iio
import matplotlib
matplotlib.use("TkAgg")
import matplotlib.pyplot as plt
import numpy as np

##FUNCÕES DE REALCE 
def histograma(img, tam):
    acumulador = np.zeros((tam,))
    h, w = img.shape
    for i in range(h):
        for j in range(w):
            acumulador[img[i, j]] += 1
    return acumulador

def histo_culmut(h, L):
    acumulador = np.zeros((L,))
    acumulador[0] = h[0]
    for i in range(1, L):
        acumulador[i] = acumulador[i - 1] + h[i]
    return acumulador

def transf(hc):
    m = hc.size
    max_val = np.max(hc)
    return ((max_val - 1) / (m * m)) * hc 

def realce_gama(li, gama):
    return (255*(li/255.0)**(1/gama)).astype(np.uint8)

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

def carrega_images(baixa_resol, alta_resol):
    paths = [f"{baixa_resol}{x}.png" for x in range(4)]

    low_imgs = [iio.imread(path) for path in paths]
    high_img = iio.imread(alta_resol)
    return *low_imgs, high_img

def equaliza_indiv(imagens):
    imagens_eq = []
    for img in imagens:
        h = histograma(img, 256)
        hc = histo_culmut(h, 256)
        img_eq = transf(hc)[img].astype(np.uint8)
        imagens_eq.append(img_eq)
    return imagens_eq

def equaliza_conj(imagens):
    h_conjunto = np.zeros(256)
    for img in imagens:
        h_conjunto += histograma(img, 256)
    
    hc_conjunto = histo_culmut(h_conjunto, 256)
    transf_conjunto = transf(hc_conjunto)
    
    imagens_eq = [transf_conjunto[img].astype(np.uint8) for img in imagens]
    return imagens_eq, hc_conjunto

def correc_gamma(imagens, gama):
    imagens_gama = [realce_gama(img, gama) for img in imagens]
    return imagens_gama

def process_images(baixa_resol, alta_resol, f):
    l1, l2, l3, l4, high_img = carrega_images(baixa_resol, alta_resol)
    imagens = [l1, l2, l3, l4]
    
    plot_images_e_histograms(imagens, 
                             ["Imagem 1", "Imagem 2", "Imagem 3", "Imagem 4"], 
                             "Imagens Originais")
    
    if f == 0: #sem realce
        return *imagens, high_img
    elif f == 1:
        imagens_eq = equaliza_indiv(imagens)
        plot_images_e_histograms(imagens_eq,
                                 ["Imagem 1 Eq", "Imagem 2 Eq", "Imagem 3 Eq", "Imagem 4 Eq"],
                                 "Equalização Individual")
        return *imagens_eq, high_img
    elif f == 2:
        imagens_eq, hc_conjunto = equaliza_conj(imagens)
        
        plt.figure(figsize=(10, 5))
        plt.bar(range(256), hc_conjunto)
        plt.title("Histograma Cumulativo Conjunto")
        plt.show()
        
        plot_images_e_histograms(imagens_eq,
                                 ["Imagem 1 Conj", "Imagem 2 Conj", "Imagem 3 Conj", "Imagem 4 Conj"],
                                 "Equalização Conjunta")
        return *imagens_eq, high_img
    elif f == 3:
        gama = float(input())
        print(gama)
        imagens_gama = correc_gamma(imagens, gama)
        plot_images_e_histograms(imagens_gama,
                                 ["Imagem 1 γ", "Imagem 2 γ", "Imagem 3 γ", "Imagem 4 γ"],
                                 f"Realce Gamma (γ = {gama})")
        return *imagens_gama, high_img
    else:
        print("Opção de realce inválida")
        return 0

def supperresolucao(imagens, high_img=None):  # high_img é opcional
    '''h, w = imagens[0].shape
    
    # Concatena as imagens para formar a super-resolução
    super_img = np.array(list(concatena(imagens[0], imagens[1], imagens[2], imagens[3])))
    
    # Exibe a imagem resultante
    plt.imshow(super_img, cmap='gray')  # 'gray' para imagens em preto e branco
    plt.title("Imagem Super-Resolvida")
    plt.axis('off')  # Remove os eixos
    plt.show()
    
    teste(imagens)
    return super_img

def teste(imagens):'''

    l1, l2, l3, l4 = imagens
    h, w = l1.shape

    # matriz com dimensões duplicadas
    super_img = np.zeros((2*h, 2*w), dtype=l1.dtype)
    
    # Preenche os pixels da super matriz
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
    # Exibe a imagem resultante
    print(super_img)
    plt.imshow(super_img, cmap='gray')
    plt.title("Imagem Super-Resolvida")
    plt.axis('off')
    plt.show()

    return super_img
    
def comp_ref(ref, grid):
    grid = grid.astype(float)
    ref = ref.astype(float)
    rse = np.sum((grid - ref) ** 2)
    print(f"Erro Quadrático Relativo: {rse:.4f}")

def main():
    # Exemplo de uso (valores hardcoded)
    baixa_resol = input()
    alta_resol = input()
    f = int(input())
    
    # Imagens após os processos de realce
    *imagens, high_img = process_images(baixa_resol, alta_resol, f)
    
    H = supperresolucao(imagens, high_img)

    comp_ref(high_img, H)
if __name__ == "__main__":
    main()