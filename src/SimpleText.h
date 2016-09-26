#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
#include "Request.h"
#include <iostream>
#include <string>
#include <vector>
#include "MessaginThreadHandler.h"
#include "ImageSearchThreadHandler.h"
#include "IPAddressGrabber.h"
#include "ImageLooper.h"
#include "ofxTween.h"
#include <cmath>
#include "ofxSpeech.h"
#include "VisualController.h"
#include "GUIHandler.h"
#include "License.h"
#include "Session.h"
#include "ofxCenteredTrueTypeFont.h"

using namespace std;

class SimpleText : public ofBaseApp, public ofThread{

	public:

    SimpleText(int w, int h);
    
    
    
    string staticAPIEndpoint;
    int width;
    int height;
    void setup();
    void update();
    void draw();
    void exit();
    int oldLength;
    int newLength;
    void threadedFunction();
    MessaginThreadHandler* modelHandler;
    vector<Request*> requestQueue;
    vector< pair< pair<string,int> , float > > qQueue;
    int qQueueHead;
    ofShader shader;
    bool doShader;
    string standardURL;
    
    void keyPressed  (int key);
    bool start;
    vector<ImageLooper *> sliders;
    bool sessionCreated;
    int currentImage;
    double currentimageTime;
    bool currentImageStarted;
    int currentImageX;
    int currentImageY;
    ofxCenteredTrueTypeFont questionsText;
    float currentTime;
    void mousePressed(int x, int y, int button);
private:
    void retrieveEndpoints();
    int SYSTEM_STATE ; // 0 -> startState , 1-> License Validation , 2-> Session Content Management , 3-> Session Start? , 4-> Session Running
    
    
    void setupSystem(){};
    float zoomInTime;
    float waitTime;
    bool currentImageRead;
    ofxEasingBounce easeBounce;
    ofxEasingCubic easeCubic;
    ofxEasingElastic easeElastic;
    ofxEasingLinear easeLinear;
    ofxEasingQuart easeQuart;
    ofxEasingBack easeBack;
    ofxEasingCirc easeCirc;
    ofxEasingExpo easeExpo;
    ofxEasingQuad easeQuad;
    ofxEasingQuint easeQuint;
    ofxEasingSine easeSine;	
    ofxTween::ofxEasingType easingType;
    double counterFade;
    License *license;
    Session *session;
    ofSoundPlayer* track;
    vector<ofSoundPlayer*>  loops;
    ofxSpeechSynthesizer    synthesizer;
    int isMusicPlaying;
    ofFbo scene;
    ofImage* numberImage;
    
    VisualController* vController;
    GUIHandler *guiController;
};
