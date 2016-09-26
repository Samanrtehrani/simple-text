
#ifndef __twitterUI__UIUserView__
#define __twitterUI__UIUserView__

#include <stdio.h>
#include "UIView.h"

class UIUserView: public UIView{
public:
    UIUserView(myPoint _center, float _radius, int __id, string _name, string nickname );
    UIUserView(myPoint _center, float _radius, int __id, string _name, string nickname , ofColor _color);
    UIUserView(myPoint _center, float _radius, int __id, string _name, string nickname , ofColor _color, int _z_index);
    
    myPoint center;
    float radius;
    string nickname;
    
    bool checkInBounds( float mouseX, float mouseY);
    void draw();
    
    void computeBounds();
    bool selected;
};
#endif /* defined(__twitterUI__UIUserView__) */
