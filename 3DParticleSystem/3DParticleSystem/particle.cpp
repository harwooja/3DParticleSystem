//
//  particle.cpp
//  3DParticleSystem
//
//  Created by Jake Harwood on 2014-11-04.
//  Copyright (c) 2014 Jake Harwood. All rights reserved.
//

#include "particle.h"


particle::particle(float px, float py, float pz, float rx, float ry, float rz, float r, float g, float b, float dx, float dy, float dz, float age, float size, float speed){
    this->px = px;
    this->py = py;
    this->pz = pz;
    this->rx = rx;
    this->ry = ry;
    this->rz = rz;
    this->r = r;
    this->g = g;
    this->b = b;
    this->dx = dx;
    this->dy = dy;
    this->dz = dz;
    this->age = age;
    this->size = size;
    this->speed = speed;
}

// SETS -- 

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
    this->rz = rz;
}
void particle::setr(float r){
    this->r = r;
}
void particle::setg(float g){
    this->g = g;
}
void particle::setb(float b){
    this->b = b;
}



// -- GETS --

float particle::getpx(){
    return(this->px);
}
float particle::getpy(){
    return(this->py);
}
float particle::getpz(){
    return(this->pz);
}
float particle::getdx(){
    return(this->dx);
}
float particle::getdy(){
    return(this->dy);
}
float particle::getdz(){
    return(this->dz);
}
float particle::getrx(){
    return(this->rx);
}
float particle::getry(){
    return(this->ry);
}
float particle::getrz(){
    return(this->rz);
}
float particle::getr(){
    return(this->r);
}
float particle::getg(){
    return(this->g);
}
float particle::getb(){
    return(this->b);
}
