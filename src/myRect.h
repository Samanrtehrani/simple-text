

#ifndef __twitterUI__myRect__
#define __twitterUI__myRect__

#include <stdio.h>
#include "myPoint.h"

class myRect {
public:
    myRect(myPoint _point, float _width, float _height);
    myRect( float x, float y, float _width, float _height);

    
    myPoint point;
    
    float width;
    float height;
    
    
    
};
#endif /* defined(__twitterUI__myRect__) */
