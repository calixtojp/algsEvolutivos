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
using std::vector;

//Draw funcition
void draw();

//Animator function
void timer(int);

vector <Host*> Hostes;

int main(int argc, char** argv){

    Host Maria(0.002, 20, 30);
    Maria.change_position(0.5, 0);
    Maria.chage_color(0, 1, 0);//Maria vai ser verde
    Maria.change_shape(0.2, 0.2);

    Host Jose(0.003, 10, 30);
    Jose.change_position(0, 0.7);
    Jose.chage_color(1, 0, 0);//Jose vai ser vermelho
    Jose.change_shape(0.1, 0.1);

    Hostes.push_back(&Maria);
    Hostes.push_back(&Jose);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Testando OpenGL");
    glClearColor(1.0, 1.0, 1.0, 1.0);// Limpa a tela (red, green, blue, alpha)
    glutDisplayFunc(draw);// Define qual função irá desenhar
    glutTimerFunc(0, timer, 0);// Define qual será a função de loop
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

    for(auto &it : Hostes ){
        // Host temp = *it;
        // temp.show_host();
        it->show_host();
    }

    // Host temp = *(Hostes[0]);//desenha só Maria
    // temp.show_host();

    // retangle(0, 0, 0.1, 0.1);

    // triangle(0.5, 0.5, 0.4, 0.5);
    // circle(-0.5, 0.5, 0.03);
    //   strangePolygon(-0.5, -0.5);
    //   anotherStrangePolygon(0.5, -0.5);

    glutSwapBuffers();
}

void timer(int){

    Hostes[0]->move_up();
    Hostes[1]->move_down();
    // Temp->move_right();
    // Temp->move_down();
    // Temp->move_left();

    // Executa a função draw para desenhar novamente
    glutPostRedisplay();

    // O primeiro parâmetro define de quanto em quanto tempo em milissegundos timer será chaamdo
    // Eu coloquei 1000/60 para definir que vai atualizar a 60hz
    glutTimerFunc(1000/60, timer, 0);// Garante que esta função será chamada de novo
}