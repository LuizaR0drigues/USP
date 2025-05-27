###########################################################################
# Disciplina: SCC0251  -> Trabalho 04: Recuperação de Imagens             #
# Luiza Rodrigues Cardoso - 1459332                                       #
###########################################################################
import imageio.v3 as iio
import matplotlib.pyplot as plt
import numpy as np
import sys

def filter_adapt(img_deg):
    #paramteros do filtro
    gama = float(input())
    i1,i2,j1,j2 =  map(int, input().split())
    tam_filt = int(input())
    mode = input()

    img_deg_pad = np.pad(img_deg, ((k,k), (k,k)), 'symmetric')
    h,w = img_deg_pad.shape
    k = tam_filt//2 
    reg_disp = img_deg_pad[i1+k:i2+k, j1+k:j2+k].flatten()
    
    dispN = np.std(reg_disp)
    if dispN == 0 :
        dispN =1
    
    F = np.zeros_like(img_deg_pad)
    vizin  = []
    if mode == "average":
        for i in range(k, h-k):
            for j in range(k, w-k):
                #print(k, i-k,j-k, i+k,j+k)
                vizin = img_deg_pad[i-k:i+k+1, j-k:j+k+1]
                dispL = np.std(vizin) 
                if dispL == 0:
                    dispL =  dispN
                centL = np.mean(vizin)
                F[i,j] = (img_deg_pad[i,j] - gama * dispN/dispL * (img_deg_pad[i,j] - centL))

    elif mode == "robust":
         for i in range(k, h-k):
            for j in range(k, w-k):
                vizin = img_deg_pad[i-k:i+k+1, j-k:j+k+1]

                centL = np.median(vizin)
                Q1 = np.percentile(vizin, 25)
                Q3 = np.percentile(vizin, 75)
                dispL = Q3 - Q1 
                if dispL == 0:
                    dispL = dispN
                
                F[i,j] = img_deg_pad[i,j] - gama * dispN/dispL * (img_deg_pad[i,j] - centL)
        
    else:
        print("Valor incorreto!")
        return 0
    
    F = F[k:h-k, k:w-k]

    return F

def gaussian_filter(k=3, sigma=1.0):
    arx = np.aragne((-k//2) + 1.0, (k//2) + 1.0)
    x,y = np.meshgrid(arx, arx)
    filt  =np.exp(-(1/2) * np.square(x) + np.square(y) / np.square(sigma))

    return filt/np.sum(filt)

#def min_quad_rest(img_deg, img_H):

def app_filter(img_g):
    param =  int(input())
    if param == 1: #aplica o remoção por filtros adaptativos
        img_filt= filter_adapt(img_g)
    return img_filt
def normalizacao(img):
    img = (img - img.min())*255/(img.max() - img.min())
    return img.astype(np.uint8)
#Computa a diferença entre duas imagens
def comp_ref(img, name_h):
    H = iio.imread(name_h)
    rse = np.sqrt(np.mean(np.power(img.astype(np.int32) - H.astype(np.int32), 2)))
    print("{:.4f}".format(rse))

def luminance ( l ) :
    if len( l.shape ) > 2:
       l = 0.2126*l[:,:,0] + 0.7152 * l[:,:,1] + 0.0722 * l[:,:,2]
       l = l.astype(np.uint8) 
    return l
def main():
    name_f = sys.stdin.readline().strip()
    name_in = sys.stdin.readline().strip()
    
    
    #definindo img
    img_deg = iio.imread(name_in)
    if len( img_deg.shape ) > 2:
        img_deg = luminance(img_deg)
    img_h =  iio.imread(name_f)
    
    plt.imshow(img_deg, cmap="gray")
    plt.title("Imagem original")
    plt.show()
    img_filter = app_filter(img_deg)
    plt.imsave("imgout.png", img_filter)
    #img_filter = normalizacao(img_filter)
    plt.imshow(img_filter, cmap="gray")
    plt.title("Imagem original")
    plt.show()
    comp_ref(img_filter, name_f)
    
    '''
    plt.imshow(img_in, cmap="gray")
    plt.title("Imagem original")
    plt.show()

    plt.figure(figsize=(10,5))

    # Imagem original (esquerda)
    plt.subplot(1, 2, 1)  # 1 linha, 2 colunas, posição 1
    plt.imshow(img_h, cmap="gray")
    plt.title("Imagem Original")
    plt.axis('off')

    # Imagem filtrada (direita)
    plt.subplot(1, 2, 2)  # 1 linha, 2 colunas, posição 2
    plt.imshow(img_filter, cmap="gray")
    plt.title("Imagem Filtrada")
    plt.axis('off')

    plt.tight_layout()  # evita sobreposição de títulos
    plt.show()
    
    '''
    return 0

if __name__ == "__main__":
    main()