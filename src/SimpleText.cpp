#include "SimpleText.h"



SimpleText:: SimpleText(int w, int h ): standardURL("http://ajax.googleapis.com/ajax/services/search/images?v=1.0&safe=active&as_filetype=jpg&rsz=7&imgsz=large|xlarge"), staticAPIEndpoint("http://APIURL.com") {
    
    retrieveEndpoints();
    
    
    this->modelHandler = new MessaginThreadHandler("http://ec2-54-152-67-38.compute-1.amazonaws.com/simpletext/api/model.json");
    
    SYSTEM_STATE = 0;
    this->width  = w;
    this->height = h;
    cout<<ofGetHeight()<<endl;
    counterFade = 0;
    
    sessionCreated = false;

    license = new License("http://ec2-54-152-67-38.compute-1.amazonaws.com/simpletext/check-license-validation/","license/license.json");

    if( license->localLicenseAvailable ){
           guiController = new GUIHandler(license->getLicenseKey(),license);
    }else{
           guiController = new GUIHandler("",license);
    }
    
    SYSTEM_STATE = 1;
};
void SimpleText::setup()
{
    ofShowCursor();
    ofSetBackgroundAuto(false);

    ofBackground(0);

    this->startThread();
    
    scene.allocate(ofGetWidth(), ofGetHeight());
    
    scene.begin();
    ofClear(0,0,0,255);
    scene.end();
    

}
void SimpleText::threadedFunction(){
    
    while( this->isThreadRunning() ){
        sleep(500);
        switch (SYSTEM_STATE) {
            case 0:
            {
                setupSystem();
                break;
            }
            case 1:
            {
                if( guiController->guiState == 1){ // validate the license
                    license->key = guiController->licenseInputField.text;
                    
                    if( license->validateLicense()  ){
                        guiController->guiState = 2;
                        
                    }else{
                        guiController->guiState = 4;// enter again
                    }
                }else if ( guiController->guiState == 2 ){ // pull the content, license is valid.
                    if( !this->sessionCreated ){
                    this->session = new Session(license,"http://ec2-54-152-67-38.compute-1.amazonaws.com/simpletext/get-content-information/");
                        this->sessionCreated = true;
                    }
                    if( !session->contentInformationLoaded ){
                        session->loadContentInformation();
                    }else{
                        
                        if( !session->backgroundMusicFetched && session->hasMusic)
                            session->downloadMusic();
                        
                        if( !session->backgroundVideoFetched && session->hasVideo)
                            session->downloadVideo();
                        if( !session->backgroundImageFetched && session->hasImage)
                            session->downloadImage();
                        if( !session->headerFontFetched || !session->messagesFontFetched)//check font lading process!!!!
                            session->downloadFontFaces();
                        cout<< session->backgroundMusicFetched << session->backgroundVideoFetched << session->backgroundImageFetched << session->headerFontFetched<<session->messagesFontFetched << endl;
                        if( session->backgroundMusicFetched && session->backgroundVideoFetched && session->backgroundImageFetched && session->headerFontFetched && session->messagesFontFetched){
                            guiController->guiState = 3;
                        }else{
                            delete session;
                            this->sessionCreated = false;
                            guiController->guiState = 5;// Try Again
                        }
                    }
                }else if( guiController->guiState == 3){// content is load to local disk, ready to start the session
                    cout<< "READY TO START!"<< endl;
                }else if( guiController->guiState == 6){// terminate GUI and start session
                    SYSTEM_STATE = 2;
                }
                break;
            }
            case 2: // LOADING CONTENT AND SETTING UP THE VISUAL CONTROLLER
            {
                if( !modelHandler->isThreadRunning() ){
                    modelHandler->startThread();
                }
                break;
            }
            case 3:// APPLICATION RUNNING
            {
                int index = this->requestQueue.size();
                if ( index < modelHandler->messagesQueueSize ){
                    
                    Request* newRequest = new Request(modelHandler->messagesQueue[index]->getContent(),modelHandler->messagesQueue[index]->getId(),this->standardURL);
                    this->requestQueue.push_back(newRequest);
                    cout<< modelHandler->messagesQueue[index]->getContent() <<endl;
                }
                break;
            }
            default:
                break;
        }

    }
}


//--------------------------------------------------------------
void SimpleText::update(){
    
    scene.begin();
    
    switch (SYSTEM_STATE) {
        case 0:
            setupSystem();
            break;
        case 1:
            guiController->draw();
            break;
        case 2:
        {
            if( !modelHandler->isThreadRunning() ){
                modelHandler->startThread();
            }
            if( session->hasMusic ){
                session->backgroundMusic = new ofSoundPlayer();
                session->backgroundMusic->loadSound(session->backgroundMusicPath);
                session->backgroundMusic->setLoop(true);
                session->backgroundMusic->setVolume(0.5);
                session->backgroundMusic->play();
            }
            if( session->hasImage ){
                session->backgroundImage = new ofImage();
                session->backgroundImage->loadImage(session->backgroundImagePath);
            }
            if ( session->hasVideo ){

                session->backgroundVideoPlayer = new ofVideoPlayer();
                session->backgroundVideoPlayer->loadMovie(session->backgroundVideoPath);
                session->backgroundVideoPlayer->setVolume(0);
                session->backgroundVideoPlayer->setLoopState(OF_LOOP_NORMAL);
                session->backgroundVideoPlayer->setSpeed(1);
                session->backgroundVideoPlayer->play();
            }
            /*track = new ofSoundPlayer();
             track->loadSound("loops/track1.mp3");
             track->setLoop(true);
             track->setVolume(0.5);
             track->play();*/
            synthesizer.initSynthesizer();
            
            int wDisp = 370;
            int hDisp = 200;
            vector< pair<float,float> > placeholders;
            placeholders.push_back(pair<float,float>(ofGetWidth()/2,ofGetHeight()/2) );
            placeholders.push_back(pair<float,float>(wDisp,hDisp) );
            placeholders.push_back(pair<float,float>(ofGetWidth()- wDisp,hDisp) );
            placeholders.push_back(pair<float,float>(wDisp,ofGetHeight()/2 + hDisp*1.2) );
            placeholders.push_back(pair<float,float>(ofGetWidth() - wDisp,ofGetHeight()/2 + hDisp) );
            pair<float,float> tTimeRange;
            tTimeRange.first = 4;
            tTimeRange.second = 7;
            pair<float,float> mTimeRange;
            mTimeRange.first = 6;
            mTimeRange.second = 10;
            pair<float,float> sTimeRange;
            sTimeRange.first = 5;
            sTimeRange.second = 8;
            vController = new VisualController(placeholders, tTimeRange , mTimeRange , sTimeRange ,ofGetWidth(),ofGetHeight(),&this->synthesizer,session);
            questionsText.loadFont("ZeroThr.ttf", 24);
            currentImage = 0;
            for( int i=0 ; i< session->questions.size() ; i++){
                pair< pair<string,int> , float > tempQ;
                tempQ.first = session->questions[i];
                tempQ.second = ofGetElapsedTimef();
                this->qQueue.push_back(tempQ);
            }
            if( session->questions.size() > 0 )
                qQueueHead = 0;
            
            SYSTEM_STATE = 3;
            break;
        }
        case 3:
        {
            
            ofSoundUpdate();// update sound if any sound is being played.
            
            
            int size= requestQueue.size();
            
            
            if( size > currentImage ){
                
/*                if( !requestQueue[currentImage]->isImageLoaded() ){
                    requestQueue[currentImage]->loadImage();
                }else{*/
                   // if( requestQueue[currentImage]->requestImage->width > 0 ){
                        if( vController->insertNewImage(requestQueue[currentImage]->requestImage,requestQueue[currentImage]->getRequestTerm() ) ){
                            currentImage++;
                            
                        }
//                    }
                //}
            }
            counterFade++;
            if( counterFade > 100000){
                counterFade =0;
            }
            if( (int)counterFade % 10 == 0){
                ofSetColor(1, 1, 1, 15);
                
                ofRect(0, 0, ofGetWidth(), ofGetHeight());
            }
            
            
            ofSetColor(255, 255, 255);
            vController->draw();
          
            break;
        }
        default:
            break;
    }

    
    scene.end();
    if( SYSTEM_STATE == 3){
    if( session->hasVideo ){
     session->backgroundVideoPlayer->update();
    }
    }
    ofSetWindowTitle( ofToString( ofGetFrameRate()) );
    
}

void SimpleText::draw()
{
    currentTime = ofGetElapsedTimef();
    
    
    
    if( SYSTEM_STATE == 3){
    if( session->hasImage ){
        session->backgroundImage->draw(0, 0, ofGetWidth(),ofGetHeight());
    }
    if( session->hasVideo ){

     
        
        session->backgroundVideoPlayer->draw(0,0,ofGetWidth(),ofGetHeight());
    }
                ofSetColor(0);
        questionsText.drawCenteredBoundingBox(qQueue[qQueueHead].first.first,ofGetWidth()/2,30, 10);
                ofSetColor(255);
        questionsText.drawStringCentered(qQueue[qQueueHead].first.first, ofGetWidth()/2,30);
        
        if( (currentTime - qQueue[qQueueHead].second) > qQueue[qQueueHead].first.second*60 ){// time is up
            if ( qQueueHead +1 < qQueue.size()  ){
                
                qQueueHead++;
                qQueue[qQueueHead].second = currentTime;
            }
        }
        
    }
    
    
    
    ofSetColor(255);
    scene.draw(0,0);
    
    //draw qQueue[qhead]
   
    
    
    
}

void SimpleText::exit(){
    if( session->hasMusic)
        session->backgroundMusic->stop();
    modelHandler->stopThread();
    this->stopThread();
}








//--------------------------------------------------------------
void SimpleText::keyPressed  (int key){
    
   	
}
void SimpleText::mousePressed(int x, int y, int button){
    guiController->checkPressed(x,y,button);
}

/*
This function attempts to make a request from the static API endpoint in order to retrieve the all required endpoints from the server. Within this design it's only critical to keep on of endpoint statically always fixed and other endpoints can vary if needed.
 
 
*/
void SimpleText::retrieveEndpoints(){
    
}

