//
//  License.cpp
//  SimpleTextMaster
//
//  Created by Saman Rezazadeh Tehrani on 12/12/15.
//
//

#include "License.h"


License::License(){
    
    
}

License::License(string licenseServerURl,string filePath){
    this->filePath = filePath;
    this->serverURL = licenseServerURl;
    this->localLicenseAvailable = false;
    
    bool parsingSuccessful = json.open(filePath);
    if (parsingSuccessful)
    {
        localLicenseAvailable = true;
        Json::Value& term  = json["key"];
        this->key =   term.asString();
        term = json["fname"];
        this->fname = term.asString();
        term = json["lname"];
        this->lname = term.asString();
        term = json["day"];
        this->expirationDay = term.asString();
        term = json["month"];
        this->expirationMonth = term.asString();
        term = json["year"];
        this->expirationYear = term.asString();
        
    } else {
        ofLogNotice("ofApp::setup") << "Failed to download model.";
    }
    
  
    
    
}
License::~License(){
    
}



string License::loadLicenseFromFile(){
   
}


bool License::validateLicense(){
    bool parsingSuccessful = json.open(this->serverURL+"?key="+this->key);
    if (parsingSuccessful)
    {
        cout<<"here"<<endl;
        Json::Value& t  = json["valid"];
        
        cout<<t.asString() <<endl;
        if( t.asString() == "yes" ){
            return true;
        }else{
            return false;
        }
        
    } else {
        ofLogNotice("ofApp::setup") << "Failed to download model.";
    }
    return false;
}

void License::putLicenseInFile(){
    
}
string License::getLicenseKey(){
    return this->key;
    
}
string License::getLicenseName(){
    return this->fname+" "+this->lname;
    
}
string License::getExpirationDate(){
    return this->expirationMonth+"/"+this->expirationDay+"/"+this->expirationYear;
    
}