
#include "UIButton.h"
UIButton::UIButton(myRect _bounds, ofColor _color,ofColor _labelColor, int _z_index, int __id, string _name): UIView(_bounds,_color,_z_index,__id,_name)
{
    this->label = _name;
    this->labelColor = _labelColor;
}
