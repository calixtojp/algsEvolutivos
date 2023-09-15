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

#define windowWidth 700
#define windowHeight 700
#define MAX_HOSTS 5

//declaring used namespaces
using namespace std;

void draw();
void circle(float x, float y, float radius);
void retangle(float x, float y, float w, float h);

Host *Pijas[5];
int n_hosts = 0;

int main(int argc, char** argv){

    Host Maria(10, 20, 30);
    Maria.change_position(0.5, 0);
    Maria.chage_color(0, 1, 0);//Maria vai ser verde
    Maria.change_shape(0.2, 0.2);
    Pijas[0] = &Maria;
    n_hosts++;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Testando OpenGL");
    glClearColor(1.0, 1.0, 1.0, 1.0);// Limpa a tela (red, green, blue, alpha)
    glutDisplayFunc(draw);// Define qual função irá desenhar
    glutMainLoop();

    return 0;
}

void draw(){
    // Importante: Somente será desenhado o que estiver entre glClear e glEnd
    glClear(GL_COLOR_BUFFER_BIT);

    // A tela padrão do OpenGL tem suas coordenadas X e Y de -1 até 1
    // Coordenada (-1 -1) é o canto inferior esquerdo
    // Coordenada (-1 1) é o canto superior esquerdo
    // Coordenada (0 0) é o centro da tela

    for(int i = 0; i < n_hosts; ++i){
      Host temp = *(Pijas[i]);
      temp.show_host();
    }
    // Maria.show_host();

    // retangle(0, 0, 0.1, 0.1);

    // triangle(0.5, 0.5, 0.4, 0.5);
    circle(-0.5, 0.5, 0.03);
    //   strangePolygon(-0.5, -0.5);
    //   anotherStrangePolygon(0.5, -0.5);

    glutSwapBuffers();
}

void circle(float x, float y, float radius){
    // Um circulo é desenhado como um polígono de muitos pontos

    glColor3f(0, 0, 1);// Define que será desenhar um objeto azul
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i+=5) {
      // Adicionada cada vértice 2D do circulo
      glVertex2d( radius*cos(i/180.0*M_PI) + x, radius*sin(i/180.0*M_PI) + y);
    }
    glEnd();
}

void retangle(float x, float y, float w, float h){
    // Vai desenhar um polígono de 4 vértices

    glColor3f(0, 0, 1);// Define que será desenhar um objeto azul
    glBegin(GL_POLYGON);// Fala para o OpenGL que os próximos pontos serão para desenhar um polígono

    // Adicionada cada vértice do retângulo
    glVertex2d( x-w/2, y-h/2);
    glVertex2d( x-w/2, y+h/2);
    glVertex2d( x+w/2, y+h/2);
    glVertex2d( x+w/2, y-h/2);

    glEnd();// Fala para o OpenGL que terminou de enviar os vértices do polígono
}