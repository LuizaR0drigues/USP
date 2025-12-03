📔 MANUAL DE TECLAS DO POL²IGONOS 3D 
*******************************************************************
COMANDOS DE COMPILAÇÃO(via terminal )
*******************************************************************
g++ main.cpp piramide.cpp esfera.cpp cubo.cpp camera.cpp iluminacao.cpp glad.c -o app -I include -lGL -lglut -lGLU -ldl

OU

g++ *.cpp glad.c -o app -I include -lGL -lglut -lGLU -ldl
g++ main.cpp src/*.cpp src/glad.c -o build/app2 -I include -lGL -lglut -lGLU -ldl

Execução:
./app

*******************************************************************
 VARIÁVEIS DO TECLADO
*******************************************************************
Movimentação da CAMERA:

WASD -> para rotação

Setas -> para translação

+- -> para aplicar zoom - não funciona para a visão ortografica

Movimentação dos objetos 3D:

ZXCVRF -> para rotação(todos os eixos)

BN -> para aplicar escala

GHJK -> para aplicar translação


