//
//  Background.h
//  Libcurl_Test
//
//  Created by Saman Rezazadeh Tehrani on 9/13/15.
//
//

#ifndef __Libcurl_Test__Background__
#define __Libcurl_Test__Background__

#include <stdio.h>
#include "ofMain.h"
#include "ImageLooper.h"



class Background{
public:
    Background(int s,int e, int w,int h);
    int totalNumber;
    vector<ofImage *> images;
    vector<ImageLooper> sliders;
    int startIndex;
    int endIndex;
    
    
};

#endif /* defined(__Libcurl_Test__Background__) */
