import skimage
import cv2
import imageio.v3 as iio
import matplotlib.pyplot as plt
import numpy as np
import scipy.signal
import sys

def hog(img):
    #filtro de sobel
    sobelx = np.array([[-1,-2,-1],[0,0,0],[1,2,1]])
    sobely = np.array([[-1,0,1],[-2,0,2],[-1,0,1]])

    #aplicando os filtros em cada direção
    gx = scipy.signal.convolve2d(img, sobelx)
    gy = scipy.signal.convolve2d(img, sobely)

    #calculo da magnitude
    raiz = np.sqrt((gx**2)+(gy**2))
    mag_xy = raiz / raiz.sum

    #calculo do angulo
    tetha_xy = np.atan((gy+0.00001)/gx)
    if gx == 0:
        tetha_xy = np.pi/2
    tetha_xy += np.pi
   
    hog = np.zeros((12,))
    for a, m in zip(tetha_xy.reshape((-1)), mag_xy.reshape((-1))):
        for id_x, possible_bin in enumerate(np.arange(0, np.pi*2, np.pi*2 / 12)):
            if a > possible_bin and a < possible_bin + (np.pi*2 / 12):
                hog[id_x] += m
    
    return hog

def local_binary_patterns(img):