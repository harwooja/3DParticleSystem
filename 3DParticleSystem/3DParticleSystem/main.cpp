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


/**
 
 --LEGEND--
 
 Key "q": Exits program
 Key "r": Clears vector (and particles from screen)
 Key "f": Enables/Disables friction mode
 Key "w": Enables/Disables wind mode
 Key SPACE: Pauses/Unpauses scene
 Key "c": Changes direction of particles if in "WIND" mode
 Key "s": Enables/Disables rain mode
 
 
 
 **/




// Identify all of our variables
vector <particle *> pvector;
float camPos[] = {5, 6, 10};
float origin[] = {-4, 7, -4};
float cols[6][3] = { {1,0,0},
                     {0,1,1},
                     {1,1,0},
                     {0,1,0},
                     {0,0,1},
                     {1,0,1} };
float gravity;
float speed;
bool friction;
bool wind;
float windspeed = 1.7;
float direction = 0;
bool pause;
bool rain = false;



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

// Draws the base rectangular prism
void cube(float v[8][3])
{
    glColor3fv(cols[1]);
    drawPolygon(0, 3, 2, 1, v); // front face
   
    glColor3fv(cols[2]);
        drawPolygon(5, 4, 0, 1, v); // left face
   
    glColor3fv(cols[3]);
        drawPolygon(5, 1, 2, 6, v); // top face
    
    glColor3fv(cols[4]);
        drawPolygon(2, 3, 7, 6, v); // right face
    
    
    glColor3fv(cols[5]);
        drawPolygon(7, 4, 5, 6, v);//back face
    
    glColor3fv(cols[0]); // bottom face
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







        /** --------- START OF RAIN MODE FUNCTIONS---------  **/

// Creates a rain particle by pushing our data to a class
void createRainParticle(){
    float rot = 0;
    float r = 0;
    float g = 0;
    float b = 1;
    speed = 1.35;
    float px = -5 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(5 - (-5))));
    float pz = -5 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(5 - (-5))));
    float dx = 0;
    float dy = -0.35;
    float dz = 0;
    float bounceNum = 0;
    float age = 0;
    float size = 0.1;
    
    // Create a new instance of our particle class and store it's object in our vector
    particle * pt = new particle(px, origin[1], pz, rot, r, g, b, dx, dy, dz, age, size, speed, bounceNum);
    pvector.push_back(pt); // Push to vector
    
}

// Method (collision on base) if we do our rain graphic
void rainCollision(){
    for (int x = 0; x < pvector.size(); x++) {
       if (pvector[x]->getpy() < 1.1){  // If particle collides with base, then stop moving
            pvector[x]->setdy(0);
        }
    }
}

// Method (remove particle from vector)
void removeRainParticle(){
    for (int x =0; x < pvector.size(); x++) {
        // Removes particle if its age is old
        if (pvector[x]->getage() == 20){
            pvector.erase(pvector.begin()+x);
        }
    }
}

// Method (update particle information)
void updateRainParticle(){
    
    // Updates age componenet and the y-value of every particle
    for (int x =0; x < pvector.size(); x++){
        pvector[x]->setage(pvector[x]->getage()+1);
        pvector[x]->setpy(pvector[x]->getpy() + pvector[x]->getdy() );
    }
     removeRainParticle();
}

// Method (renders our rain particle on screen)
void renderRainParticle(){
    
    
    // Matrix hiearchy. Push matrix, translate to our origin (spot we want to spit out particles). Then, for every particle, get the colour and location then put it into our scene.
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0, 7, 0); // set up origin
    
    for (int x = 0; x < pvector.size(); x++) {
        glPushMatrix();
        glColor3f(pvector[x]->getr(), pvector[x]->getg(), pvector[x]->getb());
        
        glRotatef(pvector[x]->getrot(), pvector[x]->getpx(), pvector[x]->getpy(), pvector[x]->getpz()); // Rotate particle
        glTranslatef(pvector[x]->getpx() + pvector[x]->getdx(), pvector[x]->getpy() + pvector[x]->getdy(), pvector[x]->getpz() + pvector[x]->getdz()); // Get location values
        
        glutSolidSphere(pvector[x]->getsize(), 60, 60); // Create actual particle
        glPopMatrix();
        glPopMatrix();
        
    }
    updateRainParticle();
    
}



        /** --------- END RAIN MODE FUNCTIONS---------  **/











        /** --------- START OF NON RAID MODE FUNCTIONS --------- **/

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
    speed = 1.35;
    float dx = (((rand() % 20)) * 0.008);
    float dy = -0.35;
    float dz = (((rand() % 20)) * 0.01);
    float bounceNum = 1;
    float age = 0;
    float size = 0.1;

    // Create a new instance of our particle class and store it's object in our vector
    particle * pt = new particle(origin[0], origin[1], origin[2], rot, r, g, b, dx, dy, dz, age, size, speed, bounceNum);
    pvector.push_back(pt); // Push to vector
    
}




// Detects any particle collision with our base
void collision(){
    
    for (int x = 0; x < pvector.size(); x++) {
        
        // if y-value intersects with plane then switch direction and increase # of bounces
        if (pvector[x]->getpy() < 0.800) {
            if (pvector[x]->getpx() < 5 && pvector[x]->getpx() > -5){
                if (pvector[x]->getpz() < 5 && pvector[x]->getpz() > -5){
                     pvector[x]->setdy(pvector[x]->getdy() * -1);
                    pvector[x]->setbounceNum(pvector[x]->getbounceNum()+1);
                }
            }
           
            // if friction is activated, slow down particles on bounce
            if (friction){
                pvector[x]->setdx(pvector[x]->getdx()/pvector[x]->getspeed());
                pvector[x]->setdy(pvector[x]->getdy()/pvector[x]->getspeed());
                pvector[x]->setdz(pvector[x]->getdz()/pvector[x]->getspeed());
            }
        
        }
        
        // if our particles are travelling upwards, then switch direction again (back downwards) at a certain height.
        if (pvector[x]->getdy() > 0) {
            if (pvector[x]->getpy() > (7/pvector[x]->getbounceNum())){
                pvector[x]->setdy(pvector[x]->getdy() * -1);
            }
        }
        
  }
}

// Method to remove particles from our vector
void removeParticle(){
    for (int x =0; x < pvector.size(); x++) {
        // Removes particle if its age is old
        if (pvector[x]->getage() == 100){
            pvector.erase(pvector.begin()+x);
        }

        // Removes particle if it exits the platform
        if (pvector[x]->getpy() < -2) {
            pvector.erase(pvector.begin()+x);
        }
        
        if (pvector[x]->getpx() > 5 || pvector[x]->getpx() < -5){
            pvector.erase(pvector.begin()+x);
        }
        
 
    }
}

// Update every particles details
void updateParticle(){
    
    // For every particle in the vector, update the age and location values (x, y, z)
    for (int x = 0; x < pvector.size(); x++) {
        pvector[x]->setage(pvector[x]->getage()+1);
        pvector[x]->setpx(pvector[x]->getpx() + pvector[x]->getdx() );
        pvector[x]->setpy(pvector[x]->getpy() + pvector[x]->getdy() );
        pvector[x]->setpz(pvector[x]->getpz() + pvector[x]->getdz()  );
       
        
    // If wind is true, then manipulate the direction information depending on the value of "direction"
        if (wind){
            if (direction == 1){
                pvector[x]->setdx(pvector[x]->getdx()*windspeed);
            } else if (direction == 2){
                pvector[x]->setdx(pvector[x]->getdx()/windspeed);
                pvector[x]->setdz(pvector[x]->getdz()*windspeed);
            } else if (direction == 3){
                pvector[x]->setdz(pvector[x]->getdz()/windspeed);
                direction = 1;
            }
           
            }
        }
        
    removeParticle();
}




// Logic: Push matrix (local coordinate system) on to stack -> Translate the original origin to the spot we want particles to come out of -> Rotate each theoretical particle (from our record) and then translate them the amount calculated in our record. Update the Particles so we continue moving them (the spheres) a certain direction

void renderParticle(){
    
    
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(-4, 7, -4); // set up origin
    
    for (int x = 0; x < pvector.size(); x++) {
        
        glPushMatrix();
        glColor3f(pvector[x]->getr(), pvector[x]->getg(), pvector[x]->getb());
        
        glRotatef(pvector[x]->getrot(), pvector[x]->getpx(), pvector[x]->getpy(), pvector[x]->getpz());
        
        glTranslatef(pvector[x]->getpx() + pvector[x]->getdx(), pvector[x]->getpy() + pvector[x]->getdy(), pvector[x]->getpz() + pvector[x]->getdz());
        
        
        glutSolidSphere(pvector[x]->getsize(), 60, 60);
        glPopMatrix();
        glPopMatrix();
        
    }
     updateParticle();
}


        /** --------- END OF NON RAID MODE FUNCTIONS --------- **/


// Display function
void display(void){
    
    float origin[3] = {0,0,0};
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(camPos[0], camPos[1], camPos[2], 0,0,0, 0,1,0); // Sets up what camera is looking at in our scene
   
    drawBox(origin, 10, 1, 10); // Draws our rectangular base
    
    // If rain mode is false, then run th default mode. If rain mode is true, run rain mode.
    if (rain == false){
        drawOrigin();
        renderParticle();
    } else if (rain == true){
        renderRainParticle();
    }

    glutSwapBuffers(); // Swap buffers -- Double buffering.
    
}



// Keyboard method
void keyboard(unsigned char key, int x, int y){
    
    switch(key){
        case 'q':
        case 'Q':
            exit(0);
            break;
            
        case 'r':
        case 'R':
            pvector.clear();
            break;
    
        case 'f':
        case 'F':
            if(friction == true){
                friction=false;
            }
            else{
                friction=true;
            }
            break;
        
        case 'w':
        case 'W':
            if(wind == true){
                wind=false;
            }
            else{
                wind=true;
            }
            break;
        
        case ' ':
            if (pause == true){
                pause = false;
            } else {
                pause = true;
            }
            break;
        
        case 'c':
        case 'C':
            direction++;
            break;
            
        case 's':
        case 'S':
            if (rain == true){
                rain = false;
                pvector.clear();
            } else if (rain == false){
                rain = true;
                pvector.clear();
            }
            break;
            
            
    }
    
}

void special(int key, int x, int y){
    
    switch(key){
        case GLUT_KEY_LEFT: // Camera position change on left arrow
            camPos[0]-=0.5;
            break;
            
        case GLUT_KEY_RIGHT: // Camera position change on right arrow
            camPos[0]+=0.5;
            break;
            
        case GLUT_KEY_UP: // Camera position change on up arrow
            camPos[2] -= 0.5;
            break;
                
        case GLUT_KEY_DOWN: // Camera position change on down arrow
            camPos[2] += 0.5;
            break;
    }
}

// Initialization method (sets up things on first run time)
void init(void)
{
    
    glClearColor(0, 0, 0, 0); // red, green, blue, alpha
    glColor3f(1, 1, 1); // red, green, blue.   0 - 1 (floats)
    
    glMatrixMode(GL_PROJECTION); // load for camera angle
    glLoadIdentity();
    
    gluPerspective(70, 1, 5, 50); // field of view
}



// Timer Method. Refreshes display periodically and runs certain functions depending on what mode we are in!
void timer(int value)
{
    
    // If rain mode is false, run characteristics for normal mode
    if (rain == false){
        if (pause == false){
            createParticle();
        }
        collision();
    }
    
    // If rain mode is true, run characteristics for rain mode
    else if (rain == true){
        if (pause == false){
            createRainParticle();
        }
        rainCollision();
    }
    
    glutPostRedisplay(); // Display callback (constant refreshing)
    glutTimerFunc(50, timer, 0); // Recursion
    
    
}


// Main function
int main(int argc, char * argv[]) {
    
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    
    glutCreateWindow("3D Particle System");	//creates the window
    
    glEnable(GL_CULL_FACE); // Enables backface culling
    glEnable(GL_DEPTH_TEST); // Enables depth test for 3-D objects
    
    glutDisplayFunc(display);	//registers "display" as the display callback function
    glutKeyboardFunc(keyboard); // registers "keyboard" as the keyboard callback function
    glutSpecialFunc(special); // registers "special" as the special keyboard callback function
    glutTimerFunc(0.01, timer, 0);
    
    init();
    glutMainLoop(); // Event loop starts
    
    return (0);
}
