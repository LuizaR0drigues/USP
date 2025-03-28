import numpy as np
import matplotlib.pyplot as plt

def cont_fun(x, y):

    return x*y + 2*y

def cont_fun_sin(x, y, freq=10):

    return np.sin(2*np.pi*x*freq) + np.sin(2*np.pi*y*freq)

def normalizacao(img):
    img = (img - img.min())/(img.max() - img.min())
    img *= 255
    return img.astype(np.uint8)

def quantization(img, B):
    img = img >> 8 - B
    img = img << 8 - B
    return img

def interp(img, i_cont, j_cont):

    i0 = np.floor(i_cont).astype(int)
    i1 = i0 + 1 if i0 < img.shape[0]-1 else i0
    j0 = np.floor(j_cont).astype(int)
    j1 = j0 + 1 if j0 < img.shape[1]-1 else j0

    c0 = img[i0, j0]
    c1 = img[i0, j1]
    c2 = img[i1, j0]
    c3 = img[i1, j1]

    t = i_cont - i0
    s = j_cont - j0

    c01 = c0*(1 - s) + c1*s
    c23 = c2*(1 - s) + c3*s
    c = c01*(1 - t) + c23*t
    return c

def main():

    freq = 100
    xs = np.arange(0., 1., 1./freq)
    ys = np.arange(0., 1., 1./freq)
    sample_grid = np.zeros((freq, freq))

    for i, x in enumerate(xs):
        for j, y in enumerate(ys):
            sample_grid[i, j] = cont_fun_sin(x, y, freq=10)

    
    
    sample_grid = normalizacao(sample_grid)
    plt.imshow(sample_grid, cmap='grey')
    plt.show()

    quant = quantization(sample_grid, B=8)
    plt.imshow(quant, cmap='grey')
    plt.show()

    freq_interp = freq*20
    xs = np.arange(0., freq, freq/freq_interp)
    ys = np.arange(0., freq, freq/freq_interp)
    sample_grid = np.zeros((freq_interp, freq_interp))
    for i, i_cont in enumerate(xs):
        for j, j_cont in enumerate(ys):
            sample_grid[i, j] = interp(quant, i_cont, j_cont)

    plt.imshow(sample_grid, cmap='grey')
    plt.show()

if __name__ == "__main__":
    main()