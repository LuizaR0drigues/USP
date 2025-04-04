import imageio.v3 as iio
import matplotlib
matplotlib.use("TkAgg")  # Garante um backend interativo
import matplotlib.pyplot as plt
import numpy as np





def main():
    
    img = iio.imread("../Transf_geometric/images.jpeg")
    
    print(img.shape)

    
if __name__ == "__main__":
    main()
