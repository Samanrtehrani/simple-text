//
//  ImageHolder.h
//  SimpleTextMaster
//
//  Created by Saman Rezazadeh Tehrani on 9/24/15.
//
//

#ifndef __SimpleTextMaster__ImageHolder__
#define __SimpleTextMaster__ImageHolder__

#include <stdio.h>
#include <ofMain.h>
#include "ofxTween.h"
#include "ofxSpeech.h"
#include <cmath>
class ImageHolder {
    
public:
    ImageHolder(ofImage* im, string t,float sx,float sy,float tTime,float wTime, float sTime, ofxSpeechSynthesizer* synth){
        
        this->image = im;
        this->term = t;
        this->currentPosX = sx;
        this->currentPosY = sy;
       
        this->transitionTime = tTime;
        this->waitTime = wTime;
        this->sideWaitTime = sTime;
        if( im->height > 600 ){
            float ratio = 600.0/im->height;
            this->currentWidth = im->width*ratio;
            this->currentHeight = im->height*ratio;
        }else{
            this->currentWidth = im->width;
            this->currentHeight = im->height;
        }
        
        this->termRead = false;

        this->synthesizer = synth;
        this->dynamicMotionTime = ofRandom(1,4);
        this->dynamicMotionRadius = 50;
        
    };
    
    
    void updateCoordinates(){
        float currentTime = ofGetElapsedTimef();
        if( currentTime - currentStartTime < transitionTime){
            currentPosX = ofxTween::map(currentTime, currentStartTime,currentStartTime + transitionTime , currentStartX, destinationPosX,false, easeQuad, easingType);
            currentPosY = ofxTween::map(currentTime, currentStartTime,currentStartTime + transitionTime , currentStartY, destinationPosY,false, easeExpo, easingType);
            
        }else{
            if( !settleTimeSet){
                this->dynamicMotionTime = ofRandom(1,4);
                settleTime = currentTime;
                settleTimeSet = true;
                temporalSettlementTime = currentTime;
                
                int randDegree  = ofRandom(0,360);
                
                temporalDestX = dynamicMotionRadius * cos(pi/180*randDegree) + placeholder.first;
                temporalDestY = dynamicMotionRadius * sin(pi/180*randDegree) +  placeholder.second;
                

                temporalX = currentPosX;
                temporalY = currentPosY;
                
                if ( !termRead ){
                    synthesizer->speakPhrase(this->term);
                    termRead  = true;
                }
            }else{
              
                if( currentTime - temporalSettlementTime < dynamicMotionTime ) {

                    currentPosX = ofxTween::map(currentTime, temporalSettlementTime,temporalSettlementTime + dynamicMotionTime , temporalX, temporalDestX,false, easeQuad, easingType);
                    currentPosY = ofxTween::map(currentTime, temporalSettlementTime,temporalSettlementTime + dynamicMotionTime , temporalY , temporalDestY,false, easeExpo, easingType);
                    
                }else{
                    
                    temporalSettlementTime = currentTime;
                    
                    int randDegree  = ofRandom(0,360);
                    
                    temporalDestX = dynamicMotionRadius * cos(pi/180*randDegree)+ placeholder.first;
                    temporalDestY = dynamicMotionRadius * sin(pi/180*randDegree)+  placeholder.second;
                    temporalX = currentPosX;
                    temporalY = currentPosY;
                }
            }
            
            
            
        }
        
    };
    
    void moveTo(int holderID,pair<float,float> dest){
        this->placeHolderId = holderID;
        this->placeholder = dest;
        this->currentStartTime = ofGetElapsedTimef();
        this->currentStartX = this->currentPosX;
        this->currentStartY = this->currentPosY;
        this->destinationPosX = dest.first;
        this->destinationPosY = dest.second;
        this->placeHolderId = holderID;
        this->settleTimeSet = false;
        
    };
    
    bool mainTimeIsOver(){

        if( settleTimeSet ){
            float currentTime = ofGetElapsedTimef();
            if (currentTime - settleTime  > waitTime)
                return true;
        }
        return false;
    };
    bool sideTimeIsOver(){
        if( settleTimeSet ){
            float currentTime = ofGetElapsedTimef();
            if (currentTime - settleTime  > sideWaitTime)
                return true;
        }
        return false;
    };
    
    ofImage* image;
    string term;
    ofxSpeechSynthesizer* synthesizer;
    float currentStartTime;
    float currentStartX;
    float currentStartY;
    float transitionTime;
    float waitTime;
    float sideWaitTime;
    
    float currentPosX;
    float currentPosY;
    
    float currentWidth;
    float currentHeight;
    
    float destinationPosX;
    float destinationPosY;
    bool settleTimeSet;
    
    float settleTime;
    float temporalSettlementTime;
    float temporalX;
    float temporalY;
    float temporalDestX;
    float temporalDestY;
    float dynamicMotionTime;
    float dynamicMotionRadius;
    bool termRead;
    //////////
    
    int placeHolderId;
    pair<float,float> placeholder;

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

    
};
#endif /* defined(__SimpleTextMaster__ImageHolder__) */
