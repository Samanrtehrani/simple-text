//
//  ImageLooper.cpp
//  Libcurl_Test
//
//  Created by Saman Rezazadeh Tehrani on 9/13/15.
//
//

#include "ImageLooper.h"

void ImageLooper::update(){
    double currentTime = ofGetElapsedTimeMillis();
    if ( currentTime - this->time   > this->rate){
        int newIndex = (int)ofRandom(startIndex,endIndex);
        loader.loadFromDisk(image, "images/num_"+ ofToString(newIndex)+".jpg");
        
        this->time = currentTime;
    }
}
void ImageLooper::draw(){
    this->image.resize(this->width,this->height);
    this->image.draw(this->x, this->y);
}