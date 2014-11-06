//
//  particle.cpp
//  3DParticleSystem
//
//  Created by Jake Harwood on 2014-11-04.
//  Copyright (c) 2014 Jake Harwood. All rights reserved.
//

#include "particle.h"


particle::particle(){
    px = 1;
    py = 1;
    pz = 1;
    
}

// SETS

void particle::setpx(float px){
    this->px = px;
}
void particle::setpy(float py){
    this->py = py;
}
void particle::setpz(float pz){
    this->pz = pz;
}
void particle::setdx(float dx){
    this->dx = dx;
}
void particle::setdy(float dy){
    this->dy = dy;
}
void particle::setdz(float dz){
    this->dz = dz;
}
void particle::setrx(float rx){
    this->rx = rx;
}
void particle::setry(float ry){
    this->ry = ry;
}
void particle::setrz(float rz){

}
void particle::setr(float r){
    
}
void particle::setg(float g){
    
}
void particle::setb(float b){
    
}

