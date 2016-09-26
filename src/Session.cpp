//
//  Session.cpp
//  SimpleTextMaster
//
//  Created by Saman Rezazadeh Tehrani on 12/12/15.
//
//

#include "Session.h"


Session::Session(){
    
}


Session::~Session(){
    
}
Session::Session(License* l,string url){
    this->sessionLicense = l;
    this->contentinformationURL = url;
    
    this->backgroundImagePath = "content/bgi.png";
    this->backgroundVideoPath = "content/bgv.mp4";
    this->backgroundMusicPath = "content/bgm.mp3";
    this->messagesFontFacePath = "content/mf.ttf";
    this->headerFontFacePath = "content/hf.ttf";
    
    backgroundImageFetched = false;
    backgroundVideoFetched = false;
    messagesFontFetched = false;
    backgroundMusicFetched = false;
    headerFontFetched = false;
    
}
void Session::downloadImage(){
    if( backgroundImageURL != ""){
        ofHttpResponse response = ofSaveURLTo(backgroundImageURL, backgroundImagePath);
        if(response.status==200){
        
            this->backgroundImageFetched = true;
        
        }else{
        

            cout << response.status << " " << response.error << endl;
            this->backgroundImageFetched = false;
        }
    }else{
               this->backgroundImageFetched = false;
    }
}
void Session::downloadVideo(){
    cout<<backgroundVideoURL <<endl;
        if( backgroundVideoURL != ""){
    ofHttpResponse response = ofSaveURLTo(backgroundVideoURL, backgroundVideoPath);
    if(response.status==200){
        
        this->backgroundVideoFetched = true;
        
    }else{
        
        
        cout << response.status << " " << response.error << endl;
        this->backgroundVideoFetched = false;
    }
        }else{
        this->backgroundVideoFetched = false;
        }
}
void Session::downloadMusic(){
            if( backgroundMusicURL != ""){
    ofHttpResponse response = ofSaveURLTo(backgroundMusicURL, backgroundMusicPath);
    if(response.status==200){
        
        this->backgroundMusicFetched = true;
        
    }else{
        

        cout << response.status << " " << response.error << endl;
        this->backgroundMusicFetched = false;
    }
            }else{
        this->backgroundMusicFetched = false;
            }
}
void Session::downloadFontFaces(){
    ofHttpResponse response;
    if( messagesFontFaceURL != ""){
     response = ofSaveURLTo(messagesFontFaceURL, messagesFontFacePath);
    if(response.status==200){
        
        this->messagesFontFetched = true;
        
    }else{
        
        
        cout << response.status << " " << response.error << endl;
        this->messagesFontFetched = false;
    }
    }else{
         this->messagesFontFetched = false;
    }
    
        if( headerFontFaceURL != ""){
    response = ofSaveURLTo(headerFontFaceURL, headerFontFacePath);
    if(response.status==200){
        
        this->headerFontFetched = true;
        
    }else{
        

        cout << response.status << " " << response.error << endl;
        this->headerFontFetched = false;
    }
        }else{
             this->headerFontFetched = false;   
    }
    
    
}

void Session::loadContentInformation(){
    
    bool parsingSuccessful = contentInformation.open(this->contentinformationURL+"?key="+sessionLicense->key);
    
    if (parsingSuccessful)
    {
        
        Json::Value& t  = contentInformation["PN"];
        cout<<"PN: " <<t.asString() <<endl;
        sessionPhoneNumber = t.asString();
        
        t  = contentInformation["BT"];
        cout<<"BT: " <<t.asString() <<endl;
        backgroundType = t.asString();

        
        t  = contentInformation["BC"];
        cout<<"BC: " <<t.asString() <<endl;
        
        t  = contentInformation["BI"];
        cout<<"BI: " <<t.asString() <<endl;
        backgroundImageURL = t.asString();
        
        t  = contentInformation["BV"];
        cout<<"BV: " <<t.asString() <<endl;
        backgroundVideoURL = t.asString();

        t  = contentInformation["HM"];
        cout<<"HM: " <<t.asString() <<endl;
        if( t.asString() == "true" ){
            t  = contentInformation["BM"];
            cout<<"BM: " <<t.asString() <<endl;
            backgroundMusicURL = t.asString();
            hasMusic = true;
        }else{
            hasMusic = false;
        }
        
        if( backgroundType == "solid"){
            hasVideo = false;
            hasImage = false;
            
            backgroundImageFetched = true;
            backgroundVideoFetched = true;
        }else if( backgroundType == "video"){
            hasVideo = true;
            hasImage = false;
            
            backgroundImageFetched = true;
        }else if( backgroundType == "image"){
            hasVideo = false;
            hasImage = true;
            
            backgroundVideoFetched = true;
        }
        
               Json::ArrayIndex text = contentInformation["Q"].size();
        int questionQueueSize = (int)text;
      
            for( int i = 0 ; i < questionQueueSize ; i++){
                const Json::Value& q = contentInformation["Q"][i];
                string term = q["term"].asString();
                int time = q["time"].asInt();
                pair<string, int> temp ;
                temp.first = term;
                temp.second = time;
                questions.push_back(temp);
                
            }
        cout<< "SIZE " << questions.size() <<endl;
      
      
        
        t  = contentInformation["MFC"];
        cout<<"MFC: " <<t.asString() <<endl;
        
        t  = contentInformation["MFF"];
        cout<<"MFF: " <<t.asString() <<endl;
        messagesFontFaceURL = t.asString();
        
        t  = contentInformation["MFS"];
        cout<<"MFS: " <<t.asInt() <<endl;
        messagesFontSize = t.asInt();
        
        t  = contentInformation["HFC"];
        cout<<"HFC: " <<t.asString() <<endl;
        
        t  = contentInformation["HFF"];
        cout<<"HFF: " <<t.asString() <<endl;
        headerFontFaceURL = t.asString();
        
        t  = contentInformation["HFS"];
        cout<<"HFS: " <<t.asInt() <<endl;
        headerFontSize = t.asInt();
        
        t  = contentInformation["PNC"];
        cout<<"PNC: " <<t.asString() <<endl;

        t  = contentInformation["GI"];
        cout<<"GI: " <<t.asString() <<endl;

        t  = contentInformation["BB"];
        cout<<"BB: " <<t.asString() <<endl;
        
        
        t  = contentInformation["BBC"];
        cout<<"BBC: " <<t.asString() <<endl;
        
        contentInformationLoaded = true;
        
       
        
    } else {
        ofLogNotice("ofApp::setup") << "Failed to download model.";
                contentInformationLoaded = false;
    }
}