//
//  main.cpp
//  3DParticleSystem
//
//  Created by Jake Harwood on 2014-10-30.
//  Copyright (c) 2014 Jake Harwood. All rights reserved.
//

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include <iostream>
#include <stdio.h>
#include <vector>
#include "particle.h"

using namespace std;


vector <particle *> pvector;
float camPos[] = {5, 6, 10};
float origin[] = {0,5,0};





void renderParticle(){
    
    particle * pt = new particle();
    pvector.push_back(pt);
    
  
    glPointSize(5);
    glColor3f(1, 0, 0);
    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);
        glVertex3f(origin[0], origin[1], origin[2]);
    
    glEnd();
    
    
    
    
}



void drawPolygon(int a, int b, int c, int d, float v[8][3]){
    glBegin(GL_POLYGON);
        glVertex3fv(v[a]);
        glVertex3fv(v[b]);
        glVertex3fv(v[c]);
        glVertex3fv(v[d]);
    glEnd();
    

}

void cube(float v[8][3])
{
    glColor3f(0, 1, 1);
    drawPolygon(0, 3, 2, 1, v);
    
    glColor3f(0,0,1);
    drawPolygon(1, 0, 4, 5, v);
    
    glColor3f(0,0,1);
    drawPolygon(5, 1, 2, 6, v);
    
    glColor3f(0,0,1);
    drawPolygon(2, 3, 7, 6, v);
    
    glColor3f(0,1,1);
    drawPolygon(6, 5, 4, 7, v);
    
    glColor3f(0,1,1);
    drawPolygon(4, 0, 3, 7, v);
}

/* drawBox - takes centre point, width, height and depth of a box,
 *  calculates its corner vertices, and draws it with the cube function
 */
void drawBox(float* c, float w, float h, float d)
{
    float vertices[8][3] = { {c[0]-w/2, c[1]-h/2, c[2]+d/2},
							 {c[0]-w/2, c[1]+h/2, c[2]+d/2},
							 {c[0]+w/2, c[1]+h/2, c[2]+d/2},
							 {c[0]+w/2, c[1]-h/2, c[2]+d/2},
							 {c[0]-w/2, c[1]-h/2, c[2]-d/2},
							 {c[0]-w/2, c[1]+h/2, c[2]-d/2},
							 {c[0]+w/2, c[1]+h/2, c[2]-d/2},
							 {c[0]+w/2, c[1]-h/2, c[2]-d/2} };
    cube(vertices);
}





void keyboard(unsigned char key, int x, int y){
    
    switch(key){
            
        case 'q':
            exit(0);
            break;
    
            
    }
    
    
    
}

void special(int key, int x, int y){
    
    switch(key){
            
            
    }
    
    
}

void timer(int value)
{
    ;
    glutPostRedisplay();
    glutTimerFunc(0.01, timer, 0);
    
    
}



void display(void){
    
    
    float origin[3] = {0,0,0};
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    
    
    gluLookAt(camPos[0], camPos[1], camPos[2], 0,0,0, 0,1,0);
    glColor3f(1,1,1);
    
    
    drawBox(origin, 10, 1, 10);
    renderParticle();
    
    glutSwapBuffers();
    
    
}

void init(void)
{
    glClearColor(0, 0, 0, 0); // red, green, blue, alpha
    glColor3f(1, 1, 1); // red, green, blue.   0 - 1 (floats)
    
    glMatrixMode(GL_PROJECTION); // load for camera angle
    glLoadIdentity();
    
    gluPerspective(80, 1, 5, 40); // field of view
}

int main(int argc, char * argv[]) {

    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    
    glutCreateWindow("3D Particle System");	//creates the window
    
    glutDisplayFunc(display);	//registers "display" as the display callback function
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    
    glEnable(GL_DEPTH_TEST);
    glutTimerFunc(0.2, timer, 0);
    
    init();
    
    glutMainLoop();
    
    return (0);
}
