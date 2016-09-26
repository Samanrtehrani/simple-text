//
//  MessaginThreadHandler.cpp
//  Libcurl_Test
//
//  Created by Saman Rezazadeh Tehrani on 8/21/15.
//
//

#include "MessaginThreadHandler.h"
MessaginThreadHandler::MessaginThreadHandler(string url) {
    modelURL =  url;
    messagesQueueSize = 0;
    
    // This Call Resets the model on the server on each run of the software.
    
    ofHttpResponse resetModel = ofLoadURL("http://samantehrani.com/quilt/ResetModel.php");
    if( resetModel.status != 200){
        cout << "Network Connection Down" <<endl;
    }

    
}

void MessaginThreadHandler::threadedFunction(){
  
    while(isThreadRunning()) {
        

        
        bool parsingSuccessful = json.open(modelURL);
        
        
        if (parsingSuccessful)
        {
            Json::ArrayIndex text = json["texts"].size();
            int newMessagesQueueSize = (int)text;
            if( newMessagesQueueSize > messagesQueueSize ){
                for( int i = messagesQueueSize ; i < newMessagesQueueSize ; i++){
                    const Json::Value& trends = json["texts"][i];
                    string cont = trends["C"].asString();
                    string num = trends["N"].asString();
                    int ID = trends["I"].asInt();
                    TextMessage* newMessage = new TextMessage(cont,num,ID);
                    messagesQueue.push_back(newMessage);
                }
                messagesQueueSize = newMessagesQueueSize;
            }

        } else {
            ofLogNotice("ofApp::setup") << "Failed to download model.";
        }
        
        // SLeep for avoiding IP to be banned
       sleep(500);
    }
}
    