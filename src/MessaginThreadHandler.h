/*http://samantehrani.com/quilt/notifier-gateway.php?text=AaaaaaaaaaaAaaaaaaaaaaaAaaaaaaaaaaaAaaaaaaaaaaaAaaaaaaaaaaaAaaaaaaaaaaaAaaaaaaaaaaaAaaaaaaaaaaaAaaaaaaaaaaaAaaaaaaaaaaaAaaaaaaaaaaaAaaaaaaaaaaaAaaaaaaaaaaaAaaaaaaaaaaaAaaaaaaaaaaaAaaaaaaaaaaaAaaaaaaaaaaaAaaaaaaaaaaaAaaaaaaaaaaaAaaaaaaaaaaaAaaaaaaaaaaaAaaaaaaaaaaaAaaaaaaaaaaaAaaaaaaaaaaaAaaaaaaaaaaaAaaaaaaaaaaaAaaaaaaaaaaaAaaaaaaaaaaaAaaaaaaaaaaaAaaaaaaaaaaaAaaaaaaaaaaaAaaaaaaaaaaaAaaaaaaaaaaaAaaaaaaaaaaaAaaaaaaaaaaaAaaaaaaaaaaaa&phone=1234
 */

//
//  MessaginThreadHandler.h
//  Libcurl_Test
//
//  Created by Saman Rezazadeh Tehrani on 8/21/15.
//
//

#ifndef __Libcurl_Test__MessaginThreadHandler__
#define __Libcurl_Test__MessaginThreadHandler__
#include <ofMain.h>
#include "ofxJSON.h"
#include "TextMessage.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;
class MessaginThreadHandler : public ofThread {
public:
    MessaginThreadHandler(string url);
    void threadedFunction();
    string modelURL;
    ofxJSONElement json;
    
  //  ofURLFileLoader *loader ;
    vector<TextMessage*> messagesQueue;
    int messagesQueueSize;
    
};

#endif /* defined(__Libcurl_Test__MessaginThreadHandler__) */
