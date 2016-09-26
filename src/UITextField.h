#pragma once
#include <stdio.h>
#include "UIView.h"


class UITextField: public UIView{
public:
    UITextField(myRect _bounds, ofColor _color,ofColor _textColor, int _z_index, int __id, string _name);
    
    string text;
    string newText;
    ofColor textColor;
    ofTrueTypeFont font;
    void draw();
    string keyPressed(int key);
	void parseString(string input);
	string getText(){
		
		return this->text;
	}

    
};

