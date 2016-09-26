//
//  ImageLooper.h
//  Libcurl_Test
//
//  Created by Saman Rezazadeh Tehrani on 9/13/15.
//
//

#ifndef __Libcurl_Test__ImageLooper__
#define __Libcurl_Test__ImageLooper__

#include <stdio.h>
#include "ofMain.h"
#include "ofxThreadedImageLoader.h"

class ImageLooper{
public:
    ImageLooper(int x, int y,int n,int w,int h,int s, int e, int r){
        this->number = n;
        this->x = x;
        this->y = y;
        this->rate = r;
        this->width = w;
        this->height = h;
        this->startIndex = s;
        this->endIndex = e;
        this->time = ofGetElapsedTimeMillis();
      
    };
    void updateRate(int r){
        this->rate = r;
    };
    void updateIndexes(int s, int e){
        this->startIndex = s;
        this->endIndex = e;
    }
    
    void draw();
    void update();
    
private:
    int x;
    int y;
    double time;
    int rate;
    int number;
    int width;
    int height;
    int startIndex;
    int endIndex;
    ofImage image;
    ofxThreadedImageLoader loader;
};


#endif /* defined(__Libcurl_Test__ImageLooper__) */
