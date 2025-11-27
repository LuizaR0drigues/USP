from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *

# Transformações globais
tx, ty, tz = 0.0, 0.0, 0.0       # translação
rx, ry = 0.0, 0.0                # rotação
scale_factor = 1.0               # escala

def drawCube():
    glBegin(GL_QUADS)

    # Frente (Azul celeste)
    glColor3f(0.0, 0.5, 0.8) 
    glVertex3f(-0.5, -0.5,  0.5)
    glVertex3f(-0.5,  0.5,  0.5)
    glVertex3f( 0.5,  0.5,  0.5)
    glVertex3f( 0.5, -0.5,  0.5)

    # Trás (Preto)
    glColor3f(0.0, 0.5, 0.8) 
    glVertex3f(-0.5, -0.5, -0.5)
    glVertex3f(-0.5,  0.5, -0.5)
    glVertex3f( 0.5,  0.5, -0.5)
    glVertex3f( 0.5, -0.5, -0.5)

    glColor3f(0, 0, 0)
    glVertex3f(-0.5,  0.5, -0.5)
    glVertex3f(-0.5,  0.5,  0.5)
    glVertex3f( 0.5,  0.5,  0.5)
    glVertex3f( 0.5,  0.5, -0.5)

    # Baixo (Azul escuro)
    glColor3f(0, 0, 0)
    glVertex3f(-0.5, -0.5, -0.5)
    glVertex3f(-0.5, -0.5,  0.5)
    glVertex3f( 0.5, -0.5,  0.5)
    glVertex3f( 0.5, -0.5, -0.5)

    # Direita (Branco)
    glColor3f(1, 1, 1)
    glVertex3f( 0.5, -0.5, -0.5)
    glVertex3f( 0.5, -0.5,  0.5)
    glVertex3f( 0.5,  0.5,  0.5)
    glVertex3f( 0.5,  0.5, -0.5)

    # Esquerda (Azul celeste)
    glColor3f(1, 1, 1)
    glVertex3f(-0.5, -0.5, -0.5)
    glVertex3f(-0.5, -0.5,  0.5)
    glVertex3f(-0.5,  0.5,  0.5)
    glVertex3f(-0.5,  0.5, -0.5)

    glEnd()


def display():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glLoadIdentity()

    gluLookAt(3, 3, 5, 0.5, 0.5, 0.5, 0, 1, 0)

    # Aplicando transformações
    glTranslatef(tx, ty, tz)
    glScalef(scale_factor, scale_factor, scale_factor)
    glRotatef(rx, 1, 0, 0)
    glRotatef(ry, 0, 1, 0)

    drawCube()
    glutSwapBuffers()


def specialKeys(key, x, y):
    global tx, ty, tz

    step = 0.1

    if key == GLUT_KEY_UP:    ty += step
    if key == GLUT_KEY_DOWN:  ty -= step
    if key == GLUT_KEY_LEFT:  tx -= step
    if key == GLUT_KEY_RIGHT: tx += step

    glutPostRedisplay()


def keyboard(key, x, y):
    global rx, ry, scale_factor

    k = key.decode("utf-8")

    # Rotação WASD
    if k in ('w', 'W'): rx += 5
    if k in ('s', 'S'): rx -= 5
    if k in ('a', 'A'): ry += 5
    if k in ('d', 'D'): ry -= 5

    # Escala
    if k in ('+', '='): scale_factor *= 1.1   # +10%
    if k in ('-', '_'): scale_factor *= 0.9   # -10%

    glutPostRedisplay()


def init():
    glEnable(GL_DEPTH_TEST)
    glClearColor(0.5, 0.5, 0.5, 1)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(45, 1, 0.1, 50.0)
    glMatrixMode(GL_MODELVIEW)


def main():
    glutInit()
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH)
    glutInitWindowSize(600, 600)
    glutCreateWindow(b"Cubo 3D - Transformacoes")

    init()
    glutDisplayFunc(display)
    glutKeyboardFunc(keyboard)
    glutSpecialFunc(specialKeys)

    glutMainLoop()

if _name_ == "_main_":
    main()