//
//  VisualController.cpp
//  SimpleTextMaster
//
//  Created by Saman Rezazadeh Tehrani on 9/24/15.
//
//

#include "VisualController.h"


VisualController::VisualController(vector< pair<float,float> > pholders , pair<float,float> tRange , pair<float,float> mRange , pair<float,float> sRange ,float w,float h,ofxSpeechSynthesizer* synth, Session * session){

    //set curren session
    this->currentSession = session;
    
    
    //set the placeholders
    this->placeholders = pholders;
    this->transitionTimeRange = tRange;
    this->mainWaitTimeRange = mRange;
    this->sidesWaitTimeRange = sRange;
    this->screenWidth = w;
    this->screenHeight = h;
    for( int i = 1 ; i <pholders.size()  ; i++ )
        this->availableHolders.push_back(i);
    
    //set up the fonts
    font.loadFont("ZeroThr.ttf", 54);
    
    headerFont.loadFont(this->currentSession->headerFontFacePath, this->currentSession->headerFontSize);
    
    messagesFont.loadFont(this->currentSession->messagesFontFacePath, this->currentSession->messagesFontSize);
    
 //   this->synthesizer = synth;
}



void VisualController::draw(){
    
    update();
    
    for(int i = 0 ; i < imageBuffer.size() ; i++ ){

        imageBuffer[i]->image->draw(imageBuffer[i]->currentPosX - imageBuffer[i]->currentWidth/2, imageBuffer[i]->currentPosY- imageBuffer[i]->currentHeight/2,imageBuffer[i]->currentWidth,imageBuffer[i]->currentHeight);

        string requestTerm =  imageBuffer[i]->term;
        if( this->currentSession->useBackgroundBoxForMessages ){
            ofSetColor(this->currentSession->backgroundBoxColor);
            messagesFont.drawCenteredBoundingBox(requestTerm, imageBuffer[i]->currentPosX  ,imageBuffer[i]->currentPosY + 72 + imageBuffer[i]->currentHeight/2 , 10);
        }
        
        ofSetColor(this->currentSession->messagesFontColor);
        
        messagesFont.drawStringCentered(requestTerm,imageBuffer[i]->currentPosX  ,imageBuffer[i]->currentPosY + 72 + imageBuffer[i]->currentHeight/2  );
    }
    
}


void VisualController::update(){
    for(int i = 0 ; i < imageBuffer.size() ; i++ ){
        
        imageBuffer[i]->updateCoordinates();
        
    }
}


bool VisualController::insertNewImage(ofImage* newImage,string text){
    
    if ( isMainAvailable() ){
        float startX;
        float startY;
        int t = ofRandom(newImage->width );
        int z = ofRandom( newImage->height);
        
        float luck = ofRandom(0,4);
        if ( luck <1 ){
            startX = 0 - t;
            startY = ofRandom(ofGetHeight());
            
        }else if(luck < 2){
            startX =  ofRandom(ofGetWidth());
            startY =  0- z;
            
        }else if( luck <3){
           startX = ofGetWidth()+  t;
           startY =  ofRandom(ofGetHeight());
            
        }else if(luck < 4){
            startX = ofRandom(ofGetWidth());
            startY = ofGetHeight() + z;
        }
        
        float tTime = ofRandom(this->transitionTimeRange.first,transitionTimeRange.second);
        float wTime = ofRandom(this->mainWaitTimeRange.first,this->mainWaitTimeRange.second);
        float sTime = ofRandom(this->sidesWaitTimeRange.first,this->sidesWaitTimeRange.second);

        ImageHolder* newHolder = new ImageHolder(newImage, text,startX,startY,tTime,wTime,sTime,this->synthesizer);
        
        this->imageBuffer.push_back(newHolder);
        this->imageBuffer[imageBuffer.size()-1]->moveTo(0,placeholders[0]);
        
        return true;
    }else{
        
        
        return false;
    }
    
}


void VisualController::drawHeader(){
    
}
void VisualController::drawLegalDisclamair(){
    
}
void VisualController::drawMessages(){
    
}


void VisualController::insertionRequested(){
    
}
void VisualController::insertImage(){
    
}