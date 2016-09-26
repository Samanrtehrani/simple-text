

#include "UIUserView.h"



UIUserView::UIUserView(myPoint _center, float _radius, int __id, string _name, string _nickname ): UIView(myRect(_center,0,0),__id,_name )
{
    this->center = _center;
    this->radius = _radius;
    this->name = _name;
    this->nickname = _nickname;
    this->computeBounds();
    
}
UIUserView::UIUserView(myPoint _center, float _radius, int __id, string _name, string _nickname , ofColor _color): UIView(myRect(_center,0,0),__id,_name )
{
    this->center = _center;
    this->radius = _radius;
    this->name = _name;
    this->nickname = _nickname;
    this->backgroundColor = _color;
    
    this->computeBounds();
}
UIUserView::UIUserView(myPoint _center, float _radius, int __id, string _name, string _nickname , ofColor _color, int _z_index): UIView(myRect(_center,0,0),__id,_name )
{
    this->center = _center;
    this->radius = _radius;
    this->name = _name;
    this->nickname = _nickname;
    this->backgroundColor = _color;
    this->zIndex = _z_index;
    
    this->computeBounds();
}

void UIUserView::draw(){

    if( this->hovered )
        ofSetColor(this->backgroundColor,this->opacity /2);
    else
        ofSetColor(this->backgroundColor,this->opacity);

    ofCircle(center.x, center.y, radius);
	ofSetColor( ofColor(0,0,0));
	ofTrueTypeFont font;
	font.loadFont("frabk.ttf", 16) ;
	font.drawString(this->nickname, this->center.x -10, this->center.y+3);
    
    
}
bool UIUserView::checkInBounds( float mouseX, float mouseY){
    if(ofDist(mouseX,mouseY,this->center.x,this->center.y) < this->radius )
        return true;
    return false;
    
    
}

void UIUserView::computeBounds(){
    this->bounds.point.x = this->center.x - this->radius ;
    this->bounds.point.y = this->center.y - this->radius ;
    this->bounds.width = 2 * radius;
    this->bounds.height = 2 * radius;
}

