#pragma once

#include "UIView.h"

class UIButton :  public UIView{
public:
     UIButton(myRect _bounds, ofColor _color,ofColor _labelColor, int _z_index, int __id, string _name);
    string label;
    ofColor labelColor;
    void draw(){
        UIView::draw();
        
        ofSetColor(labelColor);
        ofTrueTypeFont font;
        font.loadFont("frabk.ttf", 16) ;
        float w = font.stringWidth(label);
        float h = font.stringHeight(label);
        myPoint point( (this->bounds.point.x + this->bounds.width/2) - w/2 , (this->bounds.point.y + this->bounds.height/2) - h/2 );
        font.drawString(label, point.x, point.y);
        
    }
};

