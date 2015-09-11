//
//  ParticleStructure.cpp
//  Assignment2
//
//  Created by Tom Woudenberg on 10/24/2013.
//  Copyright (c) 2013 Tom Woudenberg. All rights reserved.
//

#include "ParticleStructure.h"
#include <stdlib.h>
#include <GLUT/glut.h>
#include <math.h>



float magDistance (int x, int y, int x2, int y2){
	float distance = sqrt((float)fastDistance(x ,y,x2,y2));
	if (distance == 0){
		return 0;
	}
	else{
        float magD = direction(x,x2)/distance;
        return (magD);
	}}

int direction(int x, int x2)
{
	int direction = x - x2;
	return (direction);
}




int fastDistance(int x1, int y1, int x2, int y2){
	int square1 = (x2 - x1)^2;
	int square2 = (y2 - y1)^2;
	int distance = (square1 + square2);
	return (abs(distance));
}