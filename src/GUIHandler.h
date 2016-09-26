//
//  GUIHandler.h
//  SimpleTextMaster
//
//  Created by Saman Rezazadeh Tehrani on 12/13/15.
//
//

#ifndef GUIHandler_h
#define GUIHandler_h

#include <iostream>
#include <ofMain.h>
#include "ofxTextInputField.h"
#include "License.h"
#include "Session.h"

using namespace std;
class GUIHandler{
public:
    GUIHandler(string,License*);
    ~GUIHandler();
    ofxTextInputField licenseInputField;
    void draw();
    ofTrueTypeFont font;
    void checkPressed(int,int,int );
    string insertedLicense;
    int guiState ; // 0-> license insertion , 1-> license validation , 2-> license valid!, waiting for content loading | 3-> content loaded, waiting to start session | 4-> License Not Valid | 5-> Content Loading Issue , ASK TO TRY AGAIN, SHOW THE ERROR | 6-> GUI is OVER, start Session
    License *currentLicese;
    Session * currentSession;
};
#endif /* GUIHandler_h */
