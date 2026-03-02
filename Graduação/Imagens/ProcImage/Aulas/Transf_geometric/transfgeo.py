import imageio.v3 as iio
import matplotlib
matplotlib.use("TkAgg")  # Garante um backend interativo
import matplotlib.pyplot as plt

import matplotlib.pyplot as plt
import numpy as np

def inv_scale_matrix(si, sj):
    return np.array([[1.0 / si, 0, 0],
            [0, 1.0 / sj, 0],
            [0, 0, 1]] )
           

#matriz de translação inversa
def inv_translacao(ti, tj):
    t_inv = np.array([[1,0,-ti],
                  [0,1,-tj],
                  [0,0,1]])
    return t_inv

#matriz de rotação
def inv_rotacao(theta):
    theta = np.radians(theta)
    rot = np.array([[np.cos(theta), np.sin(theta), 0],
                    [-np.sin(theta), np.cos(theta),0],
                    [0,0,1]])
    return rot

def main():
    
    img = iio.imread("images.jpeg")
    #plt.imshow(img)
    #plt.show()
    
    print(type(img))  # Deve ser um array numpy
    print(img.shape)
    
    new_img = np.zeros_like(img)
    h, w, c = new_img.shape

    #matriz de transformacao geometricas
    mat_inv = inv_scale_matrix(1.2, 1.2)
    mat_inv = mat_inv@inv_translacao(-h/2.0, -w/2.0)
    mat_inv = mat_inv@inv_rotacao(90)
    mat_inv = mat_inv@inv_translacao(h/2.0, w/2.0)
    mat_inv = mat_inv@inv_translacao(10, 0)


    for i in range(h):
        for j in range(w):

            p = np.array([i, j, 1]) #vetor coord homogeneas
            pl = mat_inv@p #faz o produto vetorial entre as matrizes

            i_og = int(np.round(pl[0])) #nova dimensao da linha
            j_og = int(np.round(pl[1])) #nova dimensao da coluna

            #verifica se as novas coordenadas estão dentro dos limites da imagem original.
            if not (i_og >= h or j_og >= w or i_og < 0 or j_og < 0):
                new_img[i, j] = img[i_og, j_og]

    plt.imshow(new_img)
    plt.show()

    plt.imsave("tf_img.jpeg",new_img)
if __name__ == "__main__":
    main()
