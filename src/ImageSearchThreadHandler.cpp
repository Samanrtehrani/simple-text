//
//  ImageSearchThreadHandler.cpp
//  Libcurl_Test
//
//  Created by Saman Rezazadeh Tehrani on 8/21/15.
//
//

#include "ImageSearchThreadHandler.h"


ImageSearchThreadHandler::ImageSearchThreadHandler( string filepath, string searchTerm,string baseURL){
    
    this->imageFetched = false;
    
    this->imageFormat = "jpg";
    this->baseURL = baseURL;
    this->filePath = filepath;
    this->timeout = 12000;
    this->requestURL =  this->createURL(searchTerm);
    
    this->startThread();
    
}

ImageSearchThreadHandler::~ImageSearchThreadHandler(){
    this->stopThread();
}

void ImageSearchThreadHandler::threadedFunction(){
    int searchIndex = 0;
    this->startTime = ofGetElapsedTimeMillis();
bool parsingSuccessful = jsonResponse.open(this->requestURL);
    cout << this->requestURL <<endl;
    while(isThreadRunning()) {
        if (parsingSuccessful)
        {

            const Json::Value& jsonVal = jsonResponse["responseData"]["results"];

            string imageURL = jsonVal[searchIndex++]["unescapedUrl"].asString();
            cout << imageURL << endl;
            ofHttpResponse resp = ofSaveURLTo(imageURL,this->filePath+"_main.jpg");
        
            if(resp.status==200){
                


                sleep(2000);
                
                this->imageFetched = true;
                this->stopThread();
                
            
            }else if( resp.status == 301 || resp.status == 302){
                //this->stopThread();
                cout << resp.status << " " << resp.error << endl;

            }else{
                
                //this->stopThread();
                cout << resp.status << " " << resp.error << endl;
            }
            
            
            if( searchIndex > 4 ){
                this->stopThread();
            }
            
        }else{
            
            ofLogNotice("ofApp::setup") << "No Json Response for Image";
            
            if( ofGetElapsedTimeMillis()  - this->startTime > this->timeout ){
                cout<< "TimeOUt Search " << endl;
                this->stopThread();
            }else{
                sleep(2000);
                parsingSuccessful = jsonResponse.open(this->requestURL);
            }
            
        }

    }
}


string ImageSearchThreadHandler::createURL(string term){
    LocalAddressGrabber :: availableList();
    string ip = LocalAddressGrabber :: getIpAddress("en0");
    string ip2 = LocalAddressGrabber :: getIpAddress("lo0");
    cout<< "IP : "<< ip <<endl;
        cout<< "IP2 : "<< ip2 <<endl;
    ofStringReplace(term, " ","%20");

    return this->baseURL + "&q=" + term ;
}

bool ImageSearchThreadHandler::isImageFetched(){
    

    return imageFetched;
}