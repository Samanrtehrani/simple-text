//
//  VisualController.h
//  SimpleTextMaster
//
//  Created by Saman Rezazadeh Tehrani on 9/24/15.
//
//

#ifndef __SimpleTextMaster__VisualController__
#define __SimpleTextMaster__VisualController__

#include <iostream>

#include <ofMain.h>
#include <vector>
#include "ImageHolder.h"
#include "ofxCenteredTrueTypeFont.h"
#include "ofxSpeech.h"
#include "Session.h"


using namespace std;

class VisualController {
    
public:
    VisualController(vector< pair<float,float> > placeholders , pair<float,float> transitionTimeRange , pair<float,float> mainWaitTimeRange , pair<float,float> sidesWaitTimeRange ,float screenWidth,float screenHeight,ofxSpeechSynthesizer* synthesizer, Session* );
    
    
    
    void draw();
   

    bool insertNewImage(ofImage*,string);// return true if inserted, else false if full
    

    Session* currentSession;
    vector<ImageHolder* > imageBuffer;
    vector< pair<float,float> > placeholders ;
    vector< int > availableHolders;
    pair<float,float> transitionTimeRange ;
    pair<float,float> mainWaitTimeRange ;
    pair<float,float> sidesWaitTimeRange ;
    float screenWidth;
    float screenHeight;
    
    ofxCenteredTrueTypeFont font;
    ofxCenteredTrueTypeFont headerFont;
    ofxCenteredTrueTypeFont messagesFont;
    
    ofxSpeechSynthesizer* synthesizer;
    
private:
    
    void drawHeader();
    void drawLegalDisclamair();
    void drawMessages();

    bool isMainAvailable(){
        if( imageBuffer.size() == 0 ){
            return true;
        }else if ( imageBuffer[imageBuffer.size() -1]->mainTimeIsOver() ){
           
            if( availableHolders.size() > 0 ){
                int rIndex = (int)ofRandom(0,availableHolders.size() );
                int rHolder = availableHolders[rIndex];
                
                imageBuffer[imageBuffer.size() - 1]->moveTo(rHolder,placeholders[rHolder]);
                availableHolders.erase(availableHolders.begin()+rIndex);
 
                return true;
                
            }else{
                for( int i =0 ; i< imageBuffer.size() - 1 ; i++ ){
                    if( imageBuffer[i]->sideTimeIsOver() ){
                        int holderID = imageBuffer[i]->placeHolderId;
                        imageBuffer.erase(imageBuffer.begin()+i);
                        availableHolders.push_back(holderID);
                    }
                }
                return false;
            }

        }else{
           
            return false;
        }
    };
    void insertionRequested();
    void insertImage();// check times, among thosse over time chooses the min , if no chooses the min.
    void update();
    
};

#endif /* defined(__SimpleTextMaster__VisualController__) */
