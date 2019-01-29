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

////////////////////////////Globals////////////////////////////
static const int windowWidth = 800;
static const int windowHeight = 800;
 float aspectRatio = (float)windowWidth/(float)windowHeight;
static const int sizeFactor = 2 * aspectRatio;
////////////////////////////Globals////////////////////////////

////////////////////////////Helpers////////////////////////////
//gets a random floating point number in a range
float RandomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

//gets a random integer in a range
int RandomInt(int min, int max){
    return rand() % max + min;
}

//more concise
void endFlush(){
    glEnd();
    glFlush();
}

//creates/allocates a 2D array
float** createArray(int r, int c){
    
    float** array = new float*[r]; // Rows
    for (int i = 0; i < r; i++){
        array[i] = new float[c]; // Columns
    }
    return array;
}

float getColor()
{
    return RandomFloat(0.0, 1.0);
}
////////////////////////////Helpers////////////////////////////

void Firework(float centerX,float centerY, int sizeFactor, float red, float green, float blue){
    float outerX = RandomFloat(centerX-sizeFactor, centerX+sizeFactor);
    float outerY = RandomFloat(centerY-sizeFactor, centerY+sizeFactor);
    
    if(sqrt(abs(pow(centerX - (double)outerX, 2)) + abs(pow(centerY - (double)outerY,2) )) >= 2){
        outerX = centerX + 1;
        outerY = centerY + 1;
    }
    glColor3f(red,green,blue);
//    glColor3f(RandomFloat(0.0,1.0), RandomFloat(0.0,1.0), RandomFloat(0.0,1.0));
    glBegin(GL_LINES);
    glVertex3f(centerX, centerY, 0.0);
    glVertex3f(outerX, outerY, 0.0);
    endFlush();
}

void display(){
    //choose a random number of fireworks to display
    int numberOfFireworks =RandomInt(2,10);
    
    //length of array that hold the X and Y Positions
    int xY = 2;
    
    //dynamic 2D array that hold variable amounts of
    float ** fireworkCenters = createArray(numberOfFireworks, xY);
    
    //generate values for fireworkCenters
    for (int i = 0; i < numberOfFireworks; i++) {
        for (int j = 0; j < xY ; j++) {
            fireworkCenters[i][j] = RandomFloat(1.0, 9.0);
        }
    }
    
    for (int i = 0; i < numberOfFireworks; i++) {
        
        //center X and Y to get passed to Firework()
        float X = fireworkCenters[i][0];
        float Y = fireworkCenters[i][1];
        
        //random  colors of fireworks
        float red = getColor();
        float green = getColor();
        float blue  = getColor();
        
    //the number of lines in the firework
    for (int j = 0; j < 100; j++) {
        Firework(X, Y, sizeFactor,red,green,blue);
    }
    }
}

int main(int argc, char** argv) {
    
    srand((unsigned int)time(NULL));
    printf("hello world\n");
    glutInit(&argc, argv);
    glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(windowWidth,windowHeight); // set window size
    glutCreateWindow ("square");
    glClearColor(0.0, 0.0, 0.0, 0.0);         // black background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 10.0, 0.0, 10.0, -1.0, 1.0);
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}
