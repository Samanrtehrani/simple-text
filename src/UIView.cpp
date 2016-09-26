#include "UIView.h"

UIView::UIView(myRect _bounds, int __id, string _name): bounds(_bounds)
{
    this->backgroundColor = ofColor(0,0,0);
    this->zIndex = 0;
    this->_id = __id;
    this->name = _name;
    this->childIDCount = 0;
    this->hidden = false;
    this->opacity  =255;
    this->hovered = false;

}
UIView::UIView(myRect _bounds, ofColor _color, int __id, string _name): bounds(_bounds){
    this->backgroundColor = _color;
    this->zIndex = 0;
    this->_id = __id;
    this->name = _name;
        this->opacity  =255;
    this->childIDCount = 0;
    this->hidden = false;
    this->hovered = false;

}
UIView::UIView(myRect _bounds, ofColor _color, int _z_index, int __id, string _name):bounds(_bounds){
    this->backgroundColor = _color;
    this->zIndex = _z_index;
    this->_id = __id;
    this->name = _name;
    this->childIDCount = 0;
    this->hidden = false;
        this->opacity  =255;
    this->hovered = false;

}


void UIView::setZIndex(int _z_index){
    this->zIndex = _z_index;
    
}
void UIView::setBackgroundColor(ofColor _color){
    this->backgroundColor = _color;
}
ofColor UIView::getBackgroundColor(){
    return this->backgroundColor;
}
myRect UIView::getBounds(){
    return this->bounds;
}
int UIView::getzIndex(){
    return this->zIndex;
}
void UIView::addChildren( vector<UIView*> _children){
    for( vector<UIView*>::iterator it = _children.begin() ; it != _children.end() ; it++)
        this->children.push_back(*it);
}

void UIView::removeChild( int __id){
    for( vector<UIView*>::iterator it = children.begin() ; it != children.end() ; it++){
        if( (*it)->_id == __id){
            this->children.erase(it);
        }
    }
    
}


void UIView::removeChild( string _name){
    for( vector<UIView*>::iterator it = children.begin() ; it != children.end() ; it++){
        if( (*it)->name == _name){
            this->children.erase(it);
        }
    }
    
}

void UIView::drawView(){
    if( !this->hidden)
        draw();
    
    for( vector<UIView*>::iterator it = children.begin() ; it != children.end() ; it++){
        (*it)->drawView();
    }
    
}

bool UIView::checkHovered(float mouseX, float mouseY){
    bool childrenHovered = false;
    for( vector<UIView*>::iterator it = children.begin() ; it != children.end() ; it++){
        if( (*it)->checkHovered(mouseX, mouseY) )
            childrenHovered = true;
    }
    if( childrenHovered)
        return false;
    bool isInBound = checkInBounds(mouseX, mouseY);
    
    if( isInBound)
        hovered = true;
    else
        hovered = false;
    return isInBound;
}
pair<bool,string> UIView::checkClicked(float mouseX, float mouseY){
    bool childrenClicked= false;
    
    for( vector<UIView*>::iterator it = children.begin() ; it != children.end() ; it++){
        if( ((*it)->checkClicked(mouseX, mouseY)).first ){
            return (*it)->checkClicked(mouseX, mouseY);
        }
    }

    bool isInBound = this->checkInBounds(mouseX, mouseY);
    if(isInBound)
        return make_pair(true, this->name);
    else
        return make_pair(false,"");
    
}


void UIView::setOpacity( float _opacity){
    this->opacity  = _opacity;
}
float UIView::getOpacity( ){
    return this->opacity;
}
void UIView::hide(){
    this->hidden = true;
}
void UIView::unhide(){
    this->hidden = false;
}
bool UIView::isHidden(){
    return this->hidden;
}