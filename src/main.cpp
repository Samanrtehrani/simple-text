#include "ofMain.h"
#include "SimpleText.h"

//========================================================================
int main( ){
    
    ofSetupOpenGL(2560,1600, OF_WINDOW);

    ofRunApp( new SimpleText(2560,1600) );
    
}
