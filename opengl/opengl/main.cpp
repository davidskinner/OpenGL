//
//  main.cpp
//  opengl
//
//  Created by David Skinner on 1/23/19.
//  Copyright © 2019 David Skinner. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <vector>
#include <cmath>

#include <OpenGL/gl.h>

#include <OpenGl/glu.h>

#include <GLUT/glut.h>

//gets a random floating point number in a range
float RandomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

int RandomInt(int min, int max){
    return rand() % max + min;

}

//more concise
void endFlush(){
    glEnd();
    glFlush();
}

void Firework(float centerX,float centerY, int sizeFactor, float red, float green, float blue){
    float outerX = RandomFloat(centerX-sizeFactor, centerX+sizeFactor);
    float outerY = RandomFloat(centerY-sizeFactor, centerY+sizeFactor);
    
    if(sqrt(abs(pow(centerX - (double)outerX, 2)) + abs(pow(centerY - (double)outerY,2) )) >= 2)
    {
        outerX = centerX + 1;
        outerY = centerY + 1;
    }
    
    glColor3f(red,green,blue);
    glBegin(GL_LINES);
    glVertex3f(centerX, centerY, 0.0);
    glVertex3f(outerX, outerY, 0.0);
    endFlush();
}

float** createArray(int r, int n)
{
    float** a = new float*[r]; // Rows
    
    for (int i = 0; i < r; i++)
    {
        a[i] = new float[n]; // Columns
    }
    return a;
}

float getColor()
{
    return RandomFloat(0.0, 1.0);
}

void display(){
    //generate a random number of fireworks
    int numberOfFireworks =RandomInt(2,7);
    int xY = 2;
    float ** fireworkCenters = createArray(numberOfFireworks, xY);
//
    //generate values for fireworkCenters
    for (int i = 0; i < numberOfFireworks; i++) {
        for (int j = 0; j < xY ; j++) {
            fireworkCenters[i][j] = RandomFloat(1.0, 10.0);
        }
    }
    
    for (int i = 0; i < numberOfFireworks; i++) {
        float X = fireworkCenters[i][0];
        float Y = fireworkCenters[i][1];
        float red = getColor();
        float green = getColor();
        float blue  = getColor();
        
    for (int j = 0; j < 100; j++) {
        Firework(X, Y, 2,red,green,blue);
    }
    }
}

int main(int argc, char** argv) {
    srand((unsigned int)time(NULL));
    printf("hello world\n");
    glutInit(&argc, argv);
    glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800); // set window size
    glutCreateWindow ("square");
    
    glClearColor(0.0, 0.0, 0.0, 0.0);         // black background
    glMatrixMode(GL_PROJECTION);              // setup viewing projection
    glLoadIdentity();                           // start with identity matrix
    glOrtho(0.0, 10.0, 0.0, 10.0, -1.0, 1.0);   // setup a 10x10x2 viewing world
    
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}
