/*
* button.h/button.cpp
* An abstract element class for creating an element working as a button
* It can calculate if it has been pushed.
*
* Written and all rights reserved by: Filip Unger & Anton Bohman
*/

#include "elements\Button.h"

Button::Button() : AbstractElement() {

}

Button::Button(Graphic* _graphic, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr) : AbstractElement(_graphic, posToSet, sizeToSet, harbor, texturePtr) {

}

Button::~Button() {

}

bool Button::isPressed(const MouseInfo* mouse) {
	//returns whether left mouse btn has been pushed when inside of button or not.
	float pos_X0 = 0, pos_X1 = 0, pos_Y0 = 0, pos_Y1 = 0;
	if (mouse->Left.Active) {
		getQuadBoundriesView(&pos_X0, &pos_X1, &pos_Y0, &pos_Y1);

		if (mouse->X > pos_X0 &&
			mouse->X < pos_X1 &&
			mouse->Y > pos_Y0 &&
			mouse->Y < pos_Y1
			) {
			return true;
		}
	}
	return false;
}
