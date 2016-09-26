//
//  TextMessage.h
//  Libcurl_Test
//
//  Created by Saman Rezazadeh Tehrani on 8/26/15.
//
//

#ifndef __Libcurl_Test__TextMessage__
#define __Libcurl_Test__TextMessage__

#include <iostream>
using namespace std;


class TextMessage {
public:
    TextMessage();
    TextMessage(string term, string number,int id);
    string getContent();
    string getNumber();
    int getId();
private:
    int id;
    string content;
    string number;
};
#endif /* defined(__Libcurl_Test__TextMessage__) */
