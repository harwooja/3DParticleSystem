//
//  Initilization.cpp
//  3DParticleSystem
//
//  Created by Jake Harwood on 2014-11-06.
//  Copyright (c) 2014 Jake Harwood. All rights reserved.
//

#include "Initilization.h"
#include <time.h>
#include <math.h>


// Initialization speed for each particle
void randomSpin(){
    float spins[] = {0, 0, 0};
    srand(time(NULL));
    spins[0] =  rand() % 361;
    ry =  rand() % 361;
    rz =  rand() % 361;
    
}

// Initialization colour for each particle
void randomColour(){
    srand(time(NULL));
    r =  (float)rand()/RAND_MAX;
    g =  (float)rand()/RAND_MAX;
    b =  (float)rand()/RAND_MAX;
}

void randomDirections(){
    srand(time(NULL));
    
    dy =  -1;
    
}