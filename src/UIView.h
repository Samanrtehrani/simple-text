#ifndef __twitterUI__UIView__
#define __twitterUI__UIView__

#include <stdio.h>
#include "myRect.h"
#include <vector>
#include <ofMain.h>
#include <string>


using namespace std;


class UIView {
    
public:
    string name;
    int _id;
    int childIDCount;
    
    UIView(myRect _bounds, int __id, string _name);
    UIView(myRect _bounds, ofColor _color, int __id, string _name);
    UIView(myRect _bounds, ofColor _color, int _z_index, int __id, string _name);
    
    /* every class inheriting from the base UIView class must implement their own drawing method */


    bool checkHovered(float mouseX, float mouseY);
    pair<bool,string> checkClicked(float mouseX, float mouseY);
    
    void setZIndex(int _z_index);
    void setBackgroundColor(ofColor _color);
    ofColor getBackgroundColor();
    myRect getBounds();
    int getzIndex();
    void addChildren( vector<UIView*> _children);
    void removeChild(int __id);
    void removeChild ( string _name );
    
    
    /* in order to draw the view, this function both draws it self and its children */
    void drawView();
    void setOpacity( float _opacity);
    float getOpacity( );
    void hide();
    void unhide();
    bool isHidden();
    myPoint getCenter(){
        return myPoint( (this->bounds.point.x + this->bounds.width/2) , (this->bounds.point.y + this->bounds.height/2)  );
    }


protected:
    virtual void clicked(){
        
    }
    virtual void draw(){
        if( hovered )
            ofSetColor(this->backgroundColor,this->opacity /2);
        else
            ofSetColor(this->backgroundColor,this->opacity);
        ofRect(bounds.point.x, bounds.point.y, bounds.width , bounds.height);
        
    };
    virtual bool checkInBounds( float mouseX, float mouseY){
        if (
            ( mouseX > this->bounds.point.x && mouseX < (this->bounds.point.x + this->bounds.width ) )
            &&
            ( mouseY > this->bounds.point.y && mouseY < (this->bounds.point.y + this->bounds.height ) )
            )
        {
            
            return true;
        }
        return false;
    };
    
    myRect bounds;
    vector< UIView* > children;
    ofColor backgroundColor;
    int zIndex;
    bool hidden;
    float opacity;

    bool hovered;
    
    
    
};

#endif /* defined(__twitterUI__UIView__) */
