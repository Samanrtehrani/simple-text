//
//  GUIHandler.cpp
//  SimpleTextMaster
//
//  Created by Saman Rezazadeh Tehrani on 12/13/15.
//
//

#include "GUIHandler.h"


GUIHandler::GUIHandler(string input,License* l){
    
    this->insertedLicense = input;
    licenseInputField.setup();
    licenseInputField.text = input;

    

    font.loadFont(OF_TTF_SERIF, 18);
    licenseInputField.setFont(font);
    
    this->guiState = 0;
    
}
GUIHandler::~GUIHandler(){
    
}



void GUIHandler::draw(){
    ofBackground(0);
    switch (guiState) {
        case 0:
            ofSetColor(255);
            licenseInputField.bounds.height = 36;
            licenseInputField.bounds.width = 380;
            licenseInputField.bounds.x = ofGetWidth()/2 - licenseInputField.bounds.width/2;
            licenseInputField.bounds.y = ofGetHeight()/2 - licenseInputField.bounds.height/2;
            ofNoFill();
            ofRect(licenseInputField.bounds);
            licenseInputField.draw();
            ofFill();
            ofRect(ofGetWidth()/2 - 150,ofGetHeight()/2 + 200,300,font.stringHeight("Check License:")+10);
            ofSetColor(125);
            font.drawString("Check License", ofGetWidth()/2  - font.stringWidth("Check License:")/2,ofGetHeight()/2+ 200+font.stringHeight("Check License:")+5);
            break;
        case 1:
            ofSetColor(255);
    
            ofFill();

            ofSetColor(125);
            font.drawString("Validating License Key, Please Wait!", ofGetWidth()/2  - font.stringWidth("Validating License Key, Please Wait!")/2,ofGetHeight()/2+font.stringHeight("Validating License Key, Please Wait!")+5);
            break;
        case 2:
            ofSetColor(255);
            
            ofFill();
            
            ofSetColor(125);
            font.drawString("Your license is valid!", ofGetWidth()/2  - font.stringWidth("Your license is valid!")/2,ofGetHeight()/2+font.stringHeight("Your license is valid!")+5);
            font.drawString("Please wait until we download your session content...", ofGetWidth()/2  - font.stringWidth("Please wait until we download your session content...")/2,ofGetHeight()/2+ 40+font.stringHeight("Please wait until we download your session content...")+5);
            break;
        case 3:
            ofSetColor(255);
            
            ofFill();
            
            ofRect(ofGetWidth()/2 - 150,ofGetHeight()/2 + 200,300,font.stringHeight("Start Session!")+10);
            ofSetColor(125);
            font.drawString("Start Session!", ofGetWidth()/2  - font.stringWidth("Start Session!")/2,ofGetHeight()/2+ 200+font.stringHeight("Start Session!")+5);

            
            break;
        case 4:
            ofSetColor(255);
            
            ofFill();
            
            ofSetColor(125);
            font.drawString("License is not valid!", ofGetWidth()/2  - font.stringWidth("License is not valid!")/2,ofGetHeight()/2+font.stringHeight("License is not valid!")+5);
            ofSetColor(255);
            ofRect(ofGetWidth()/2 - 150,ofGetHeight()/2 + 200,300,font.stringHeight("Enter Again")+10);
            ofSetColor(125);
            font.drawString("Enter Again", ofGetWidth()/2  - font.stringWidth("Enter Again")/2,ofGetHeight()/2+ 200+font.stringHeight("Enter Again")+5);
            break;
        case 5:
            ofSetColor(255);
            
            ofFill();
            
            ofSetColor(125);
            font.drawString("Error loading the content from server!", ofGetWidth()/2  - font.stringWidth("Error loading the content from server!")/2,ofGetHeight()/2+font.stringHeight("Error loading the content from server!")+5);
            ofSetColor(255);
            ofRect(ofGetWidth()/2 - 150,ofGetHeight()/2 + 200,300,font.stringHeight("Try Again")+10);
            ofSetColor(125);
            font.drawString("Try Again", ofGetWidth()/2  - font.stringWidth("Try Again")/2,ofGetHeight()/2+ 200+font.stringHeight("Try Again")+5);
            break;
        default:
            break;
    }
    

    
}

void GUIHandler::checkPressed(int mouseX,int mouseY, int button){
    if( guiState == 0 ){
        if( mouseX >  ofGetWidth()/2 - 150,ofGetHeight()/2 + 200 && mouseX < ofGetWidth()/2 - 150,ofGetHeight()/2 + 200 + 300 && mouseY > ofGetHeight()/2 + 200 && mouseY < ofGetHeight()/2 + 200 + font.stringHeight("Check License:")+10){
            guiState = 1;
        }
    }else if( guiState == 3 ){
        if( mouseX >  ofGetWidth()/2 - 150,ofGetHeight()/2 + 200 && mouseX < ofGetWidth()/2 - 150,ofGetHeight()/2 + 200 + 300 && mouseY > ofGetHeight()/2 + 200 && mouseY < ofGetHeight()/2 + 200 + font.stringHeight("Start Session!")+10){
            guiState = 6;
        }
        
    }else if ( guiState == 4){
        if( mouseX >  ofGetWidth()/2 - 150,ofGetHeight()/2 + 200 && mouseX < ofGetWidth()/2 - 150,ofGetHeight()/2 + 200 + 300 && mouseY > ofGetHeight()/2 + 200 && mouseY < ofGetHeight()/2 + 200 + font.stringHeight("Enter Again")+10){
            guiState = 0;
        }
        
    }else if (guiState == 5){
        if( mouseX >  ofGetWidth()/2 - 150,ofGetHeight()/2 + 200 && mouseX < ofGetWidth()/2 - 150,ofGetHeight()/2 + 200 + 300 && mouseY > ofGetHeight()/2 + 200 && mouseY < ofGetHeight()/2 + 200 + font.stringHeight("Try Again")+10){
            guiState = 2;
        }
        
    }
    
}

