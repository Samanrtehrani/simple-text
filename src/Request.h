//
//  Request.h
//  Libcurl_Test
//
//  Created by Saman Rezazadeh Tehrani on 8/24/15.
//
//

#pragma once

#include <ofMain.h>
#include <iostream>
#include <string>
#include "ImageSearchThreadHandler.h"
using namespace std;


class Request : public ofThread {
public:
    Request();
    Request(string term,int id, string baseURL);
    ~Request();
    string getRequestTerm();
    int getRequestId();
    void setStringTerm(string term);
    bool isImageLoaded();
    bool isImageFetched();

    void threadedFunction();
    ofImage *requestImage;
    bool loadImage();
    string imageFilePath;
    int startX;
    int startY;
private:
    
    int id;
    string requestTerm;
    string directory;
    ImageSearchThreadHandler* searchHandler;
    


    string createFilePath();
    
    bool imageIsLoaded;
    bool imageIsFetched;
    int timeout;
    int startTime;
    
    

    
};


