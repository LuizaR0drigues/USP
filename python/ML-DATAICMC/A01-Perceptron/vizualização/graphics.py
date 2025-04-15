import matplotlib.pyplot as mpl
from mpl_toolkits import mplot3d
import numpy as np
import pandas as dp

def Function_2D(theta, x):
    y = (theta[0] / theta[1]) * x
    y += theta[2] / theta[1]

    return -y

def Function_3D(theta, x, y):
    z = (theta[0] / theta[2]) * x
    z += (theta[1] / theta[2]) * y
    z += theta[3] / theta[2]

    return -z

def Max(array):
    max = array[0]
    for i in range(len(array)):
        if (array[i] > max):
            max = array[i]
    return max        

def Gráfico_2D(points, theta):
    fig, ax = mpl.subplots()

    ax.set_xlim(-4,14)
    ax.set_ylim(-4,14)

    ax.scatter(points[0][:30], points[1][:30], color = 'red', label = 'Grupo Vermelho')
    ax.scatter(points[0][30:], points[1][30:], color = 'blue', label = 'Grupo Azul')

    X = np.linspace(-4, 14, 100)
    Y = Function_2D(theta, X)

    ax.plot(X, Y, label = 'Perceptron', color = 'black')

    mpl.title('Algoritmo do Perceptron em ação')
    mpl.xlabel('X')
    mpl.ylabel('Y')
    mpl.legend()
    mpl.show()    

def Gráfico_3D(points, theta):
    colunas = points.columns.tolist()

    x_name, y_name, z_name = colunas[0], colunas[1], colunas[2]

    points = points.to_numpy().T
    aux = np.full(150,1)
    points = np.vstack((points, aux))

    fig = mpl.figure()
    ax = fig.add_subplot(111, projection = '3d')

    xlim = Max(points[0])
    ylim = Max(points[1])
    zlim = Max(points[2])

    x = np.linspace(0, xlim, 100)
    y = np.linspace(0, ylim, 100)
    X, Y = np.meshgrid(x, y)

    Z = Function_3D(theta, X, Y)

    ax.scatter(points[0][:50], points[1][:50], points[3][:50], color='green', label = 'Setosa')
    ax.scatter(points[0][50:99], points[1][50:99], points[3][50:99], color='purple', label = 'Versoza')
    ax.plot_surface(X, Y, Z, cmap = 'viridis', alpha = .7)

    mpl.title('Algoritmo do Perceptron em ação')
    ax.set_xlabel(x_name)
    ax.set_ylabel(y_name)
    ax.set_zlabel(z_name)

    ax.set_xlim(0, xlim)
    ax.set_ylim(0, ylim)
    ax.set_zlim(0, zlim)

    mpl.title('Algoritmo do Perceptron em ação')
    mpl.legend()
    mpl.show()