//
//  Session.h
//  SimpleTextMaster
//
//  Created by Saman Rezazadeh Tehrani on 12/12/15.
//
//

#ifndef Session_h
#define Session_h



#include <iostream>
#include <string>
#include <vector>
#include "License.h"
#include "FileHandler.h"

using namespace std;


class Session {
public:
    Session();
    Session(License*, string );
    ~Session();
    
    void loadContentInformation();
    void downloadImage();
    void downloadVideo();
    void downloadMusic();
    void downloadFontFaces();
    
    
    int sessionDuration; // minutes
    License *sessionLicense;
    FileHandler *fileHandler;
    
    ofxJSONElement contentInformation;
    string contentinformationURL;
    bool contentInformationLoaded;
    bool backgroundImageFetched;
    bool backgroundVideoFetched;
    bool backgroundMusicFetched;
    bool messagesFontFetched;
    bool headerFontFetched;
    bool hasMusic;
    bool hasVideo;
    bool hasImage;
    //content
    string sessionPhoneNumber;
    string backgroundType; //0->solid, 1->image , 2->video
    
    ofColor backgroundColor;
    
    ofImage* backgroundImage;
    string backgroundImageURL;
    string backgroundImagePath;
    
    ofVideoPlayer* backgroundVideoPlayer;
    string backgroundVideoURL;
    string backgroundVideoPath;
    
    ofSoundPlayer* backgroundMusic;
    string backgroundMusicURL;
    string backgroundMusicPath;
    
    vector< pair<string,int> > questions;
    ofColor messagesFontColor;
    ofTrueTypeFont* messagesFontFace;
    string messagesFontFacePath;
        string messagesFontFaceURL;
    int messagesFontSize;
    
    ofColor headerFontColor;
    ofTrueTypeFont* headerFontFace;
    int headerFontSize;
    string headerFontFacePath;
    string headerFontFaceURL;
    
    ofColor sessionNumberFontColor;
    
    bool useGoogleImages;
    bool useBackgroundBoxForMessages;
    ofColor backgroundBoxColor;
    

    
    
 
};

#endif /* Session_h */
