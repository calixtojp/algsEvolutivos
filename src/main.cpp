#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

//deafault libraries used
#include <iostream>
#include <bits/stdc++.h>

//created libraries
#include "host.h"
#include "food.h"
#include "world.h"

#define windowWidth 700
#define windowHeight 700

#define POPULATION_SIZE 10

//declaring used namespaces
using std::vector;

//Draw funcition
void draw();

//Animator function
void timer(int);

World *world;
void OpenGlSetup(int *argc, char** argv);

int main(int argc, char** argv){
    world = new World(POPULATION_SIZE);

    OpenGlSetup(&argc, argv);

    return 0;
}

void draw(){
    // Importante: Somente será desenhado o que estiver entre glClear e glEnd
    glClear(GL_COLOR_BUFFER_BIT);

    // A tela padrão do OpenGL tem suas coordenadas X e Y de -1 até 1
    // Coordenada (-1 -1) é o canto inferior esquerdo
    // Coordenada (-1 1) é o canto superior esquerdo
    // Coordenada (0 0) é o centro da tela
    world->update();

    glutSwapBuffers();
}

void timer(int){
    // Executa a função draw para desenhar novamente
    glutPostRedisplay();

    // O primeiro parâmetro define de quanto em quanto tempo em milissegundos timer será chaamdo
    // Eu coloquei 1000/60 para definir que vai atualizar a 60hz
    glutTimerFunc(1000/60, timer, 0);// Garante que esta função será chamada de novo
}

void OpenGlSetup(int *argc, char** argv) {
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Testando OpenGL");
    glClearColor(1.0, 1.0, 1.0, 1.0);// Limpa a tela (red, green, blue, alpha)
    glutDisplayFunc(draw);// Define qual função irá desenhar
    glutTimerFunc(0, timer, 0);// Define qual será a função de loop
    glutMainLoop();
}