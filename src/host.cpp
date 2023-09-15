#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif


#include <stdio.h>
#include "host.h"

void Host::change_position(float new_x, float new_y){
    this->pos.x = new_x;
    this->pos.y = new_y;
}
void Host::change_shape(float new_h, float new_w){
    this->shape.h = new_h;
    this->shape.w = new_w;
}

void Host::chage_color(float new_R, float new_G, float new_B){
    this->color.R = new_R;
    this->color.G = new_G;
    this->color.B = new_B;
}

void Host::show_characteristics(){
    printf("x:%.2f|y:%.2f|h:%.2f|w:%.2f|RGB(%.2f,%.2f,%.2f)\n",
        this->pos.x,
        this->pos.y,
        this->shape.h,
        this->shape.w,
        this->color.R,
        this->color.G,
        this->color.B
    );
}

void Host::show_host(void){
    // Vai desenhar um polígono de 4 vértices
    this->show_characteristics();

    glColor3f(this->color.R, this->color.G, this->color.B);
    glBegin(GL_POLYGON);// Fala para o OpenGL que os próximos pontos serão para desenhar um polígono

    // Adicionada cada vértice do retângulo
    glVertex2d( this->pos.x-this->shape.w/2, this->pos.y-this->shape.h/2);
    glVertex2d( this->pos.x-this->shape.w/2, this->pos.y+this->shape.h/2);
    glVertex2d( this->pos.x+this->shape.w/2, this->pos.y+this->shape.h/2);
    glVertex2d( this->pos.x+this->shape.w/2, this->pos.y-this->shape.h/2);

    glEnd();// Fala para o OpenGL que terminou de enviar os vértices do polígono
}