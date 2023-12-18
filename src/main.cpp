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
#include "config.h"

#define windowWidth 700
#define windowHeight 700

std::unordered_map<std::string, float> CONFIG; // Definition of the global variable

//declaring used namespaces
using std::vector;

//Draw funcition
void draw();

//Animator function
void timer(int);

World *world;
//Function to enable OpenGL
void OpenGlSetup(int *argc, char** argv);

int main(int argc, char** argv){
    CONFIG = readConfig(".conf");
    
    world = new World(CONFIG["POPULATION_SIZE"], CONFIG["FOOD_AMOUNT"]);

    OpenGlSetup(&argc, argv);

    return 0;
}

void draw(){
    // Important: Only what is between glClear and glEnd will be drawn
    glClear(GL_COLOR_BUFFER_BIT);

    // The default OpenGL screen has its X and Y coordinates from -1 to 1
    // Coordinate (-1 -1) is the bottom left corner
    // Coordinate (-1 1) is the top left corner
    // Coordinate (0 0) is the center of the screen
    world->update();

    glutSwapBuffers();
}

void timer(int){
    // Execute the draw function to draw again
    glutPostRedisplay();


    // The first parameter defines how often in milliseconds the timer will be called
    // I put 1000/60 to define that it will update at 60hz
    glutTimerFunc(1000/60, timer, 0);// Guarantees that this function will be called again
}

void OpenGlSetup(int *argc, char** argv) {
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Testando OpenGL");
    glClearColor(1.0, 1.0, 1.0, 1.0);// Cleans the screen (red, green, blue, alpha)
    glutDisplayFunc(draw);// Defines which function will draw
    glutTimerFunc(0, timer, 0);// Define what the loop function will be
    glutMainLoop();
}