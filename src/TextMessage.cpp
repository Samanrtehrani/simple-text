//
//  TextMessage.cpp
//  Libcurl_Test
//
//  Created by Saman Rezazadeh Tehrani on 8/26/15.
//
//

#include "TextMessage.h"
TextMessage::TextMessage(){
    this->content = "EMPTY MESSAGE";
    this->number = "000000000000";
    this->id = -1;
}
TextMessage::TextMessage(string term, string number,int id){
    this->content = term;
    this->number = number;
    this->id = id;
}
string TextMessage::getContent(){
    return this->content;
}
string TextMessage::getNumber(){
    return this->number;
}
int TextMessage::getId(){
    return this->id;
}