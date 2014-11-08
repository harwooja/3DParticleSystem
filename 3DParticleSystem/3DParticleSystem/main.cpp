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
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <math.h>
#include "particle.h"

using namespace std;

vector <particle *> pvector;
float camPos[] = {5, 6, 10};
float origin[] = {-4, 6, -4};
float cols[6][3] = { {1,0,0}, {0,1,1}, {1,1,0}, {0,1,0}, {0,0,1}, {1,0,1} };
float gravity;
float speed;



/** ----- START OF CREATING BASE ----- **/

// Draws our base (rectangular prism)
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
    glColor3fv(cols[1]);
        drawPolygon(0, 3, 2, 1, v);
    
    glColor3fv(cols[2]);
        drawPolygon(5, 4, 0, 1, v);
   
    glColor3fv(cols[3]); // top
        drawPolygon(5, 1, 2, 6, v);
    
    glColor3fv(cols[4]);
        drawPolygon(2, 3, 7, 6, v);
    
    
    glColor3fv(cols[5]);
        drawPolygon(6, 5, 4, 7, v);
    
    glColor3fv(cols[0]); // bottom
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

/** ---- END OF CREATING BASE ---- **/








// Draws origin point in window
void drawOrigin(){
    glPointSize(5);
        glColor3f(1, 0, 0);
        glEnable(GL_POINT_SMOOTH);
        glBegin(GL_POINTS);
        glVertex3f(origin[0], origin[1], origin[2]);
    glEnd();
}



// Creates a new particle per display refresh
void createParticle(){
    float rot =  rand() % 360 + 1;
    float r =  (float)rand()/RAND_MAX;
    float g =  (float)rand()/RAND_MAX;
    float b =  (float)rand()/RAND_MAX;
    speed = 0.005;
    gravity = 0;
    float dx = ((rand() % 20)) * speed;
    float dy = -0.35;
    float dz = ((rand() % 20)) * 0.00;
    float age = 0;
    float size = 2;

    // Create a new instance of our particle class and store it's object in our vector
    particle * pt = new particle(origin[0], origin[1], origin[2], rot, r, g, b, dx, dy, dz, age, size, gravity);
    pvector.push_back(pt); // Push to vector
    
}

// Detects any particle collision with our base
void collision(){
    
    for (int x = 0; x < pvector.size(); x++) {
        if (pvector[x]->getpy() < 0.500) {
            pvector[x]->setdy(pvector[x]->getdy() * -1);
        }
        
        if (pvector[x]->getdy() > 0) {
            pvector[x]->setgrav(pvector[x]->getgrav() + 0.5);
        }
        

    }
}

void removeParticle(){
    for (int x =0; x < pvector.size(); x++) {
        if (pvector[x]->getage() == 100){
        //    pvector.erase(x);
        }
        
    }
}

// Update every particles details
void updateParticle(){
    
    for (int x = 0; x < pvector.size(); x++) {
        pvector[x]->setage(pvector[x]->getage()+1);
        pvector[x]->setdy(pvector[x]->getdy() - pvector[x]->getgrav());
        pvector[x]->setpx(pvector[x]->getpx() + pvector[x]->getdx() );
        pvector[x]->setpy(pvector[x]->getpy() + pvector[x]->getdy() );
        pvector[x]->setpz(pvector[x]->getpz() + pvector[x]->getdz()  );
    }
    removeParticle();
}


// Logic: Push matrix (local coordinate system) on to stack -> Translate the original origin to the spot we want particles to come out of -> Rotate each theoretical particle (from our record) and then translate them the amount calculated in our record. Update the Particles so we continue moving them (the spheres) a certain direction

void renderParticle(){
    
    glPushMatrix();
    glTranslatef(-5, 5, -5); // set up origin
    
    for (int x = 0; x < pvector.size(); x++) {
        
        glPushMatrix();
        glColor3f(pvector[x]->getr(), pvector[x]->getg(), pvector[x]->getb());
        
        glRotatef(pvector[x]->getrot(), pvector[x]->getpx(), pvector[x]->getpy(), pvector[x]->getpz());
        
        glTranslatef(pvector[x]->getpx() + pvector[x]->getdx(), pvector[x]->getpy() + pvector[x]->getdy(), pvector[x]->getpz() + pvector[x]->getdz());
        
        
        glutSolidCube(0.3);
        glPopMatrix();
        glPopMatrix();
        
    }
     updateParticle();
}





void display(void){
    
    float origin[3] = {0,0,0};
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camPos[0], camPos[1], camPos[2], 0,0,0, 0,1,0);
    glColor3f(1,1,1);
    
    drawBox(origin, 10, 1, 10);
    drawOrigin();
    renderParticle();

    glutSwapBuffers();
    
  
    
}




void keyboard(unsigned char key, int x, int y){
    
    switch(key){
            
        case 'q':
            exit(0);
            break;
            
        case 'r':
            pvector.clear();
            break;
    }
    
}

void special(int key, int x, int y){
    
    switch(key){
            
        case GLUT_KEY_LEFT:
            camPos[0]-=0.5;
            break;
            
        case GLUT_KEY_RIGHT:
            camPos[0]+=0.5;
            if (camPos[0] < 0)
                camPos[0] = 5;
            
            break;
    }
}

void init(void)
{
    
    glClearColor(0, 0, 0, 0); // red, green, blue, alpha
    glColor3f(1, 1, 1); // red, green, blue.   0 - 1 (floats)
    
    glMatrixMode(GL_PROJECTION); // load for camera angle
    glLoadIdentity();
    
    gluPerspective(70, 1, 5, 40); // field of view
}

void idle(void){
    createParticle();
    collision();
 
    glutPostRedisplay();
    
    
}

void timer(int value)
{
    createParticle();
    collision();
    glutPostRedisplay();
    glutTimerFunc(50, timer, 0);
    
    
}



int main(int argc, char * argv[]) {
    
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    
    
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    
    glutCreateWindow("3D Particle System");	//creates the window
    
    glutDisplayFunc(display);	//registers "display" as the display callback function
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutTimerFunc(0.01, timer, 0);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    
    init();
    
    glutMainLoop();
    
    return (0);
}
