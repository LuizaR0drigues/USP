import numpy as np
from scipy.ndimage import gaussian_filter
import matplotlib.pyplot as plt  # For visualization (optional)

def operador_laplaciano():
    """Retorna um operador Laplaciano simples 3x3."""
    return np.array([[0, -1, 0],
                     [-1, 4, -1],
                     [0, -1, 0]])

def filter_min_quad_rest(sigma, tam_f, img_deg, gama):
    """
    Aplica o filtro de mínimos quadrados restritos para restaurar uma imagem degradada.

    Args:
        sigma (float): Desvio padrão do filtro gaussiano.
        tam_f (int): Tamanho do filtro gaussiano (neste caso, do kernel).
        img_deg (np.ndarray): Imagem degradada.
        gama (float): Parâmetro de regularização.

    Returns:
        np.ndarray: Imagem restaurada.
    """

    # 1. Gerar os filtros
    laplace = operador_laplaciano()
    #filt_deg = gaussian_filter(img_deg, sigma=sigma) # gaussian_filter already applies the filter
    filt_deg = np.ones((tam_f, tam_f)) # Create a simple kernel for demonstration

    # 2. Calcular o padding
    a = img_deg.shape[0] // 2 - filt_deg.shape[0] // 2
    c = img_deg.shape[0] // 2 - laplace.shape[0] // 2

    # 3. Aplicar o padding (ANTES da FFT)
    filt_h_pad = np.pad(filt_deg, ((a, a - 1), (a, a - 1)), 'constant', constant_values=(0))
    laplace_pad = np.pad(laplace, ((c, c - 1), (c, c - 1)), 'constant', constant_values=(0))

    # 4. Aplicar a Transformada de Fourier (FFT)
    img_deg_ft = np.fft.fft2(img_deg)
    filt_h = np.fft.fft2(filt_h_pad)
    filt_h_conj = np.conjugate(filt_h)
    op_laplace = np.fft.fft2(laplace_pad)

    # Visualização dos filtros (opcional)
    # plt.imshow(np.log(np.abs(filt_h) + 1e-8), cmap='gray')
    # plt.title("Filtro Gaussiano (padded) no domínio da frequência")
    # plt.show()
    # plt.imshow(np.log(np.abs(op_laplace) + 1e-8), cmap='gray')
    # plt.title("Filtro Laplaciano (padded) no domínio da frequência")
    # plt.show()

    # 5. Realizar a filtragem no domínio da frequência
    result = (filt_h_conj / (np.abs(filt_h) ** 2 + gama * np.abs(op_laplace) ** 2 + 1e-8)) * img_deg_ft

    # 6. Aplicar a Transformada Inversa de Fourier (IFFT)
    img_result = np.fft.ifft2(result)
    img_result = np.real(img_result)

    return img_result


if __name__ == '__main__':
    # Criar uma imagem de exemplo (256x256)
    img_exemplo = np.zeros((256, 256))
    img_exemplo[100:150, 100:150] = 255  # Quadrado branco no centro
    img_exemplo = gaussian_filter(img_exemplo, sigma=5) # Blur the image

    # Parâmetros de exemplo
    sigma = 1.0
    tam_f = 5
    gama = 0.01

    # Aplicar o filtro
    img_restaurada = filter_min_quad_rest(sigma, tam_f, img_exemplo.copy(), gama)

    # Visualizar os resultados
    plt.figure(figsize=(10, 5))
    plt.subplot(1, 2, 1)
    plt.imshow(img_exemplo, cmap='gray')
    plt.title('Imagem Degradada')
    plt.subplot(1, 2, 2)
    plt.imshow(img_restaurada, cmap='gray')
    plt.title('Imagem Restaurada')
    plt.show()