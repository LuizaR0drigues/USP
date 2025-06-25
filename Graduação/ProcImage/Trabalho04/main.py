###########################################################################
# Disciplina: SCC0251  -> Trabalho 04: Recuperação de Imagens             #
# Luiza Rodrigues Cardoso - 1459332                                       #
###########################################################################
import imageio.v3 as iio
import matplotlib.pyplot as plt
import numpy as np
import sys

#Filtro Adaptativo de Remocação de Ruido
#Paramteros: imagem degradada, fator limitante gama. coordenadas de um sub-regiao da imagem
#tamanho do filtro e mode = {average, robust}
def filter_adapt(img_deg, gama):
    #paramteros do filtro
    i1,i2,j1,j2 =  map(int, input().split())
    tam_filt = int(input())
    mode = sys.stdin.readline().strip()
    
    k = tam_filt//2
    img_deg_pad = np.pad(img_deg, ((k,k), (k,k)), 'symmetric') #app do padding 
    h,w = img_deg_pad.shape
    
    #selecionando a sub-região da imagem
    reg_disp = img_deg_pad[i1+k:i2+k, j1+k:j2+k].flatten()

    #calculo da dispersao de ruido estimada através do desvio padrão da sub-regiao
    dispN = np.std(reg_disp)
    if dispN == 0 :
        dispN =1
    
    
    F = np.zeros_like(img_deg_pad)
    vizin  = []
    #Modo = Average
    #Utiliza a media aritmetica como medida de  dispersao local e o desvio padrao da vizinhaça nxn como medida de centralidade local
    if mode == "average":
        for i in range(k, h-k):
            for j in range(k, w-k):
                
                vizin = img_deg_pad[i-k:i+k+1, j-k:j+k+1]
                dispL = np.std(vizin) 
                if dispL == 0:
                    dispL =  dispN
                centL = np.mean(vizin)
                F[i,j] = (img_deg_pad[i,j] - gama * dispN/dispL * (img_deg_pad[i,j] - centL)) #calculo  e aplicacao do filtro
    #Modo = Average
    #Utiliza a mediana como medida de  centralidade local e o intervalo quartil da vizinhaça nxn como medida de dispersao local
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
                F[i,j] = (img_deg_pad[i,j] - gama * dispN/dispL * (img_deg_pad[i,j] - centL)) #calculo e aplicação do filtro
        
    else:
        print("Valor incorreto!")
        return 0
    
    #retirando o padding da imagem
    F = F[k:h-k, k:w-k]

    return F

#Filtro de ruído 
def gaussian_filter(k=3, sigma=1.0):
    arx = np.arange((-k//2) + 1.0, (k//2) + 1.0)
    x,y = np.meshgrid(arx, arx)
    filt = np.exp(-(1/2) * (np.square(x) + np.square(y)) / np.square(sigma))

    return np.array(filt/np.sum(filt))

#Filtro Laplaciano
def operador_laplaciano():
    return np.array([[0,-1,  0],
                     [-1, 4, -1],
                     [0, -1, 0]])

#Filtro de Minimos Quadrados Restritos
def filter_min_quad_rest(sigma, tam_f, img_deg, gama):
    #criando os filtros de degradação(gaussiano) e limitante(laplace)
    laplace = operador_laplaciano()
    filt_deg = gaussian_filter(k = tam_f, sigma=sigma) 
    
    #realizando o padding nos filtros
    a = int(img_deg.shape[0] // 2 - filt_deg.shape[0] // 2)
    c = int(img_deg.shape[0] // 2 - laplace.shape[0] // 2)

    filt_h_pad = np.pad(filt_deg, ((a, a - 1), (a, a - 1)), 'constant', constant_values=(0))
    laplace_pad = np.pad(laplace, ((c, c - 1), (c, c - 1)), 'constant', constant_values=(0))
    
    #aplicando a tf na imagem e filtros
    img_deg_ft = np.fft.fft2(img_deg)
    filt_h = np.fft.fft2(filt_h_pad)
    filt_h_conj = np.conjugate(filt_h)
    op_laplace = np.fft.fft2(laplace_pad)

    #realizando a filtragem do dominio da frequencia ( produto na frequencia)
    result = (filt_h_conj / (np.abs(filt_h) ** 2 + gama *( np.abs(op_laplace) ** 2))) * img_deg_ft

    #aplicando a tf inversa e voltando pro dominio real
    img_result = np.fft.ifft2(result)
    img_result = np.fft.ifftshift(img_result)
    img_result = np.real(img_result)

    return img_result

def app_filter(img_g):
    #Parametros-> Id: identificador do tipo de filtro e  fator gama
    id =  int(input())
    gama = float(input())
    if id == 1: #aplica o remoção por filtros adaptativos
        img_filt= filter_adapt(img_g, gama)

    elif id == 2: #aplica o filtro de minimos quadrados restirtos para restauração das imagens
        tam_f = int(input())
        sigm =  float(input())
        img_filt = filter_min_quad_rest(sigm, tam_f, img_g, gama)
    return img_filt

#Computa a diferença entre duas imagens
def comp_ref(img, H):
    rse = np.sqrt(np.mean(np.power(img.astype(np.int32) - H.astype(np.int32), 2)))
    print("{:.4f}".format(rse))

#Aplicando a liminacia para deixar a imagem colorida em tons de cinza
def luminance ( l ) :
    if len( l.shape ) > 2:
       l = 0.2126*l[:,:,0] + 0.7152 * l[:,:,1] + 0.0722 * l[:,:,2]
       l = l.astype(np.uint8) 
    return l

def visualiza_img(img, titulo):
    plt.imshow(img, cmap="gray")
    plt.title(titulo)
    plt.show()

def main():
    #nome dos arquivos que serão utilizados
    name_f = sys.stdin.readline().strip()
    name_in = sys.stdin.readline().strip()
    
    #Criando os objs de imagens e aplicando a luminancia para imagens coloridas
    img_deg = iio.imread(name_in)
    if len( img_deg.shape ) > 2:
        img_deg = luminance(img_deg)
    img_h =  iio.imread(name_f)
    
    #aplicando os filtros 
    img_filter = app_filter(img_deg)
    #clippando as imagens pois pode ocorrer valores que ultrapassem os limites [0,55]
    img_filter_clip = np.clip(img_filter, 0, 255)

    #computando as diferenças entre as imagens filtradas e as imagens "perfeitas"
    comp_ref(img_filter_clip, img_h)

    #salvando o resultado obtido com a filtragem de ruido
    plt.imsave("imgout.png", img_filter_clip)
    
    #visualizando os resultados
    visualiza_img(img_deg, "Imagem degrada por ruídos")
    visualiza_img(img_filter, "Imagem Filtrada")
    visualiza_img(img_filter_clip, "Imagem com limites definidos")

    return 0

if __name__ == "__main__":
    main()