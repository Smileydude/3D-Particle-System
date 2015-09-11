//
//  ParticleStructure.h
//  Assignment2
//
//  Created by Tom Woudenberg on 10/24/2013.
//  Copyright (c) 2013 Tom Woudenberg. All rights reserved.
//

#ifndef __Assignment2__ParticleStructure__
#define __Assignment2__ParticleStructure__

#include <iostream>

typedef struct
{
	float position[3];
    float direction[3];
    int speed;
    int rotation[3];
    int size;
    float color[3];
    int age;
    
    
}particle;

int fastDistance(int x1, int y1, int x2, int y2);

float magDistance(int x, int y, int x2, int y2);

int direction (int x1, int x2);




#endif /* defined(__Assignment2__ParticleStructure__) */
