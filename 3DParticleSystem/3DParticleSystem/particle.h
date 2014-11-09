//
//  particle.h
//  3DParticleSystem
//
//  Created by Jake Harwood on 2014-11-04.
//  Copyright (c) 2014 Jake Harwood. All rights reserved.
//

#ifndef ___DParticleSystem__particle__
#define ___DParticleSystem__particle__

#include <stdio.h>


class particle {
    
public:
    particle(float px, float py, float pz, float rot ,float r, float g, float b, float dx, float dy, float dz, float age, float size, float speed, float bounceNum);
    
    void setpx(float px);
    void setpy(float py);
    void setpz(float pz);
    void setdx(float dx);
    void setdy(float dy);
    void setdz(float dz);
    void setrot(float rx);
    void setspeed(float speed);
    void setage(float set);

    void setr(float r);
    void setg(float g);
    void setb(float b);
    void setbounceNum(float bounceNum);
    
    
    
    float getpx();
    float getpy();
    float getpz();
    float getdx();
    float getdy();
    float getdz();
    float getrot();

    float getage();
    float getspeed();
    float getr();
    float getg();
    float getb();
    float getsize();
    float getbounceNum();

    
    
private:
    float px, py, pz; // particle position
    float dx, dy, dz; // movement direction
    float rot;
    float size; // particle size
    float r, g, b; // red green blue
    float age; // life
    float speed;
    float bounceNum;
};






#endif /* defined(___DParticleSystem__particle__) */
