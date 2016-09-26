
#include "myRect.h"
myRect::myRect(myPoint _point, float _width, float _height){
    this->point = _point;
    this->width = _width;
    this->height = _height;
}
myRect::myRect( float x, float y, float _width, float _height){
    myPoint _point(x,y);
    this->point = _point;
    this->width = _width;
    this->height = _height;
}