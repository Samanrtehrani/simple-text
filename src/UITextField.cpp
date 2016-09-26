
#include "UITextField.h"

UITextField::UITextField(myRect _bounds, ofColor _color,ofColor _textColor, int _z_index, int __id, string _name): UIView(_bounds,_color,_z_index,__id,_name)
{
    cout<< font.loadFont("frabk.ttf", 16) << endl;
    this->textColor = _textColor;
    text = "";
    newText= "";

}
void UITextField::draw(){
    UIView::draw();
    ofSetColor(this->textColor);

    font.drawString(text + this->newText, this->bounds.point.x + 5, this->bounds.point.y+ 15);
    
    
}
void UITextField::parseString(string input){
	this->text = "";
	this->newText = "";

	for( int i=0 ; i< input.size() ; i++ ){
		this->keyPressed((int)input[i]);
	}
}
string UITextField::keyPressed(int key){
	
    if( key == 8){
	
        text = "";
        newText = "";
    }else{
    newText += (char)key;

    if(font.stringWidth(newText) > this->bounds.width - 15 ){
        text += newText;
        text+="\n";
        
        newText = "";
    }
    }
    
    
    return text + this->newText;
}