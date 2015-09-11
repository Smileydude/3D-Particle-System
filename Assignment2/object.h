//
//  object.h
//  Assignment2
//
//  Created by Tom Woudenberg on 11/6/2013.
//  Copyright (c) 2013 Tom Woudenberg. All rights reserved.
//

#ifndef __Assignment2__object__
#define __Assignment2__object__

#include <iostream>


typedef struct
{
	int position[3];
    int scale[3];
    int shape;
    float bounce;
    float color[3];
    
    
}object;

//int fastDistance(int x1, int y1, int x2, int y2);

//float magDistance(int x, int y, int x2, int y2);

//int direction (int x1, int x2);

#endif /* defined(__Assignment2__object__) */
