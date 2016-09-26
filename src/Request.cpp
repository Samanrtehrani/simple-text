//
//  Request.cpp
//  Libcurl_Test
//
//  Created by Saman Rezazadeh Tehrani on 8/24/15.
//
//

#include "Request.h"
Request::Request(){
    
}
Request::Request(string term,int id, string baseURL){
    this->id = id;
    this->directory = "images";
    this->imageIsFetched = false;
    this->imageIsLoaded = false;
    this->timeout = 16000;
    this->requestTerm = term;
    
    this->imageFilePath = this->createFilePath();
    
    this->searchHandler= new ImageSearchThreadHandler(this->imageFilePath,this->requestTerm,baseURL);

    requestImage = new ofImage();
    
    this->startThread();
    
    
}


Request::~Request(){
    
    delete searchHandler;
    this->stopThread();
}
void Request::threadedFunction(){
    this->startTime = ofGetElapsedTimeMillis();
    while( this->isThreadRunning() ){
        if ( this->searchHandler->isImageFetched() ){
            this->imageIsFetched = true;
            cout<< "IMAGE IN THE FILE" << endl;
            delete this->searchHandler;
            this->stopThread();
        }else{
            if( ofGetElapsedTimeMillis()  - this->startTime > this->timeout ){
                cout<< "TimeOUt Request################# " << endl;
                
                this->imageFilePath = "Unknown";
                this->imageIsFetched = true;
                
                delete this->searchHandler;
                
                this->stopThread();
            }else{
                sleep(2000);
            }
        }
        
    }
}


bool Request::isImageLoaded(){
    return this->imageIsLoaded;
}
bool Request::isImageFetched(){
    return this->imageIsFetched;
}

int Request::getRequestId(){
    return this->id;
}
string Request::createFilePath(){
    return this->directory +"/"+ofToString(id)+"_"+this->requestTerm;
}
string Request::getRequestTerm(){
    return this->requestTerm;
}

bool Request::loadImage(){
    if( imageIsFetched && !imageIsLoaded ){

        if(  this->requestImage->loadImage(this->imageFilePath + "_main.jpg")  ){
            this->imageIsLoaded = true;
        }
    }
    return imageIsLoaded;
    
}