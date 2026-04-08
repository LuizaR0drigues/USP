###########################################################################
# Disciplina: SCC0251  -> Trabalho 03: filtros no domínio das frequências #
# Luiza Rodrigues Cardoso - 1459332                                       #
###########################################################################
import imageio.v3 as iio
import matplotlib.pyplot as plt
import numpy as np
import sys

#Funções de implementação de filtros
#Função que calcula a distancia euclideana em relação a um dado pixel
def dist_euclideana(u, v, p, q):
    return np.sqrt(((u-p)**2+(v-q)**2))

#Funcao do filtro de Passa-Baixa_Ideal
# H(u,v) = 1, se d(u,v) <= R ou 0, cc.  
def passa_baixa_ideal(p, q, raio): 
    h, w = int(2*p), int(2*q)
    H = np.zeros((h,w), dtype=np.float32)
    for u in range(h):
        for v in range(w):
            if dist_euclideana(u,v,p,q) <= raio:
                H[u,v] = 1
            else:
                H[u,v] = 0
    
    return H

#Funcao do filtro de Passa-Alta_Ideal
# H(u,v) = 0, se d(u,v) <= R ou 1, cc.
def passa_alta_ideal(p, q, raio): 

    h, w = int(2*p), int(2*q)
    H = np.zeros((h,w), dtype=np.float32)
    
    for u in range(h):
        for v in range(w):
            if dist_euclideana(u,v,p,q) <= raio:
                H[u,v] = 0
            else:
                H[u,v] = 1
    
    return H
#Funcao do filtro de Passa-Faixa_Ideal
def passa_faixa(p,q, r0, r1):
    r_min = min(r0,r1)
    r_max = max(r0,r1)

    #limita as freq até o maior raio
    mask_out =  passa_baixa_ideal(p,q, r_max)
    #limita as freq até o r minimo
    mask_in = passa_baixa_ideal(p,q, r_min)

    #subtraia as duas mascaras - Passa
    passa_faixa = mask_out - mask_in

    
    return passa_faixa

#Filtro passa-alta  Lapaciano
# H(u,v) = 4pi²((u-c*05)²+(v-q*0,5)²)
def filt_laplace( p, q):
    h, w = 2*p, 2*q

    H = np.zeros((h,w), dtype=np.float32)
    for u in range(h):
        for v in range(w):
            H[u,v] = 4*(np.pi**2) * ((u-p)**2 + (v-q)**2)
    
    return H

#Filtro Gaussiano
#x = ((u-p*0,5)²/2 sig0² + (v-1*0,5)²/2sig1²)
#H(u,v) = exp(-x)
def filt_pb_gauss(p, q,sig1, sig2):
    h, w = int(2*p), int(2*q)

    H = np.zeros((h,w), dtype=np.float32)
    for u in range(h):
        for v in range(w):
           x = (((u-p)**2)/(2*sig1**2) + ((v-q)**2)/(2*sig2**2))
           H[u, v] = np.exp(-x)
    return H

#H(u, v) =1/1+(D(u,v)/D0)²”
def butterworth_pb( img, d0, n):
    h, w = img.shape
    p = h//2
    q = w//2
    H = np.zeros((h,w), dtype=np.float32)
    for u in range(h):
        for v in range(w):
           d = dist_euclideana(u, v, p, q)
           H[u, v] = 1/(1+(d/d0)**(2*n))
    return H

#H(u, v) =1/1+(D0/D(u,v))²”
def butterworth_pa( p, q,d0, n):
    h, w = int(2*p), int(2*q)

    H = np.zeros((h,w), dtype=np.float32)
    for u in range(h):
        for v in range(w):
            d = dist_euclideana(u, v, p, q)
            if d <= 0:
               H[u, v] = 1
            else:
                H[u, v] = 1/(1+(d0/d)**(2*n))
    return H
#H(u, v) = 1 − (H(d0,n0) (u, v) − H(d1,n1) (u, v))
def butterworth_rejeita_faixa(img,d0, n0, d1, n1):
    
    h, w = img.shape
    p = h//2
    q = w//2
    H = np.zeros((h,w), dtype=np.float32)
    h0 = butterworth_pb( img, d0, n0)
    h1 = butterworth_pb( img, d1, n1)
    
    if d0 >d1:
        H = 1 - (h0 - h1)
    elif d0 == d1:
        H = 1  
    else:
        H = 1- (h1- h0)
        
    return H

#H(u, v) = H(d0,n0) (u, v) − H(d1,n1) (u, v)
def butterworth_passa_faixa( img,d0, n0, d1, n1):
    h, w = img.shape
    
    H = np.zeros((h,w), dtype=np.float32)
    h0 = butterworth_pb(img, d0, n0)
    h1 = butterworth_pb(img, d1, n1)
    if d0 >d1:
        H = (h0 - h1)
    else:
        H = (h1- h0)
    return H
def filtro_convolucao(img):
    kernel = np.ones((3,3))
    for i in range(3):
        for j in range(3):
            kernel[i,j] = float(input())
        
    # TF da imagem
    f = np.fft.fft2(img)

    # TF do kernel (padding auto)
    h = np.fft.fft2(kernel, s=img.shape)

    # Produto ponto a ponto nna frequência
    result = f * h

    # Inversa para o domínio espacial
    img_result = np.fft.ifft2(result)
    img_result = np.real(img_result)
    return img_result

def app_filt( img, id):
    h, w = img.shape
    p = h//2
    q = w//2

    if id == "a":
        param = float(input())
        h = passa_baixa_ideal(p, q, param)

    if id == "b":
        param = float(input())
        h = passa_alta_ideal(p, q, param)

    if id == "c":
        param0 = float(input())
        param1 = float(input())
        h = passa_faixa(p,q, param0, param1)

    if id == "d":
        h = filt_laplace(p, q)
    
    if id == "e":
        sig1 = float(input())
        sig2 = float(input())
        h = filt_pb_gauss( p, q, sig1, sig2)
    if id == "f":
        d0 =  float(input())
        n = float(input())
        h = butterworth_pb( img, d0, n)
    if id == "g":
        d0 =  float(input())
        n = float(input())
        h = butterworth_pa( p, q, d0, n)
    if id == "h":
        d0 =  float(input())
        n0 = float(input())
        d1 =  float(input())
        n1 = float(input())
        h = butterworth_rejeita_faixa( img, d0, n0, d1, n1)
    if id == "i":
        d0 =  float(input())
        n0 = float(input())
        d1 =  float(input())
        n1 = float(input())
        h = butterworth_passa_faixa( img, d0, n0, d1, n1)

    
    if id == "j":
        img_result = filtro_convolucao(img)
        return img_result
    
    #aplicando a transformada de furier 2D
    img_ft = np.fft.fftshift(np.fft.fft2(img))

    #aplicando o filtro
    result =  img_ft * h

    #calculando a inversa
    img_result = np.fft.ifft2(np.fft.ifftshift(result))
    img_result = np.real(img_result)

    return img_result

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
    name_in = sys.stdin.readline().strip()
    name_h = sys.stdin.readline().strip()
    id_filter =  sys.stdin.readline().strip()
    
    
    #definindo img
    img_in = iio.imread(name_in)
    if len( img_in.shape ) > 2:
        img_in = luminance(img_in)
    img_h =  iio.imread(name_h)
    
    
    img_filter = app_filt(img_in, id_filter)
    img_filter = normalizacao(img_filter)

    comp_ref(img_filter, name_h)
    
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