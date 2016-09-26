//
//  License.hpp
//  SimpleTextMaster
//
//  Created by Saman Rezazadeh Tehrani on 12/12/15.
//
//

#ifndef License_h
#define License_h

#include <iostream>
#include <string>
#include <ofMain.h>
#include "ofxJSON.h"
using namespace std;


class License {
public:
    License();
    License(string,string);
    
    ~License();
    
    
    string getLicenseKey();
    string getLicenseName();
    string getExpirationDate();
    string loadLicenseFromFile();
    bool localLicenseAvailable;
    
    bool validateLicense();
    
    void putLicenseInFile();
    ofxJSONElement json;

    string key;
    string fname;
    string lname;
    bool isValid;
    bool isLoaded;


    string expirationDay;
    string expirationMonth;
    string expirationYear;
    
    string filePath;
             
    string serverURL;
    
    
    
    
};
#endif /* License_h */
