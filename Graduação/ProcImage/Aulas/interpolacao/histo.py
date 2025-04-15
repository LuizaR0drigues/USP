import imageio.v3 as iio
import matplotlib
#matplotlib.use("TkAgg")
import matplotlib.pyplot as plt
import numpy as np
import sys

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
def normalizacao(img):
    img = (img - img.min())/(img.max() - img.min())
    img *= 255 
    return img.astype(np.uint8)

def transf(hc, img):
    h, w = img.shape
    L = 256  # níveis de cinza
    total = float(h * w)
    new_img = np.zeros_like(img, dtype=np.uint8)

    for i in range(h):
        for j in range(w):
            new_val = (L - 1) * hc[img[i, j]] / total
            new_img[i, j] = new_val
    print(new_img. max())
    return new_img

def equaliza_indiv(img):
    img_eq =  np.zeros_like(img)
    h = histograma(img, 256)
    hc = histo_culmut(h, 256)
    img_eq = transf(hc, img)
    return img_eq

def equaliza_conj(imagens):
    h_conjunto = np.zeros(256)
    for img in imagens:
        h_conjunto += histograma(img, 256)
    plt.bar(range(256), h_conjunto)
    plt.show()
    hc_conjunto = histo_culmut(h_conjunto, 256)
    plt.bar(range(256), hc_conjunto)
    plt.show()
    imagens_eq = [transf(hc_conjunto, img) for img in imagens]
    return imagens_eq, hc_conjunto


def main():
    baixa_resol = [iio.imread("teste.png"), iio.imread("teste2.png")]
    teste = iio.imread("teste.png")

    # Equalização conjunta
    img_eqs, h_conj = equaliza_conj(baixa_resol)


    imagem_eq = equaliza_indiv(teste)
    histo_eq = histograma(imagem_eq.astype(np.uint8), 256)

    plt.imshow(imagem_eq, cmap="gray")
    plt.show()
    # Plotando os resultados
    plt.figure(figsize=(12, 8))

    plt.subplot(2, 2, 1)
    plt.imshow(baixa_resol[0], cmap='gray')
    plt.title('Imagem Original 1')
    plt.axis('off')

    plt.subplot(2, 2, 2)
    plt.imshow(img_eqs[0], cmap='gray')
    plt.title('Imagem Equalizada 1')
    plt.axis('off')

    plt.subplot(2, 2, 3)
    plt.imshow(baixa_resol[1], cmap='gray')
    plt.title('Imagem Original 2')
    plt.axis('off')

    plt.subplot(2, 2, 4)
    plt.imshow(img_eqs[1], cmap='gray')
    plt.title('Imagem Equalizada 2')
    plt.axis('off')

    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    main()