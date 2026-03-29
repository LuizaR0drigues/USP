Todo o projeto foi desenvolvido em Ubuntu. Recomenda-se o uso do mesmo sistema
operacional para rodar a aplicação. Não foram feitos testes em outras SOs

*******************************************************************
COMANDO DE COMPILAÇÃO (via terminal)
*******************************************************************

g++ main.cpp src/*.cpp src/glad.c -o build/app -I include -lGL -lglut -lGLU -ldl

Execução:
./build/app

*******************************************************************
MANUAL DE TECLAS
*******************************************************************

Desenho 2D:
Botão esquerdo do mouse -> Cria o vértice


Menu de opções:
Botão direito do mouse -> abre o menu


Movimentação da CÂMERA:

WASD -> para rotação
Setas -> para translação
+- -> para aplicar zoom - não funciona para a visão ortografica


Movimentação dos objetos 3D:

ZXCVRF -> para rotação (todos os eixos)
BN -> para aplicar escala
GHJK -> para aplicar translação