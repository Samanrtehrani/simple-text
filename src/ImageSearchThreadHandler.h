//
//  ImageSearchThreadHandler.h
//  Libcurl_Test
//
//  Created by Saman Rezazadeh Tehrani on 8/21/15.
//
//

#ifndef __Libcurl_Test__ImageSearchThreadHandler__
#define __Libcurl_Test__ImageSearchThreadHandler__

#include <ofMain.h>
#include "ofxJSON.h"
#include <iostream>
#include <string>
#include "IPAddressGrabber.h"
using namespace std;


class ImageSearchThreadHandler : public ofThread {
public:
    ImageSearchThreadHandler(string filepath ,string searchTerm, string baseURL);
    ~ImageSearchThreadHandler();
    void threadedFunction();
    ofxJSONElement jsonResponse;
    bool isImageFetched();
private:
    ImageSearchThreadHandler* searchHandlers;
    string baseURL;
    string requestURL;
    string createURL(string term);

    string filePath;
    string imageFormat;
    float startTime;
    float timeout;
    bool imageFetched;
};

#endif /* defined(__Libcurl_Test__ImageSearchThreadHandler__) */
