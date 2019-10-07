#include "elements\Button.h"

Button::Button() : AbstractElement() {

}

Button::Button(Graphic* _graphic, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr) : AbstractElement(_graphic, posToSet, sizeToSet, harbor, texturePtr) {

}

Button::~Button() {

}

bool Button::isPressed(const MouseInfo* mouse) {
	float pos_X0 = 0, pos_X1 = 0, pos_Y0 = 0, pos_Y1 = 0;
	if (mouse->Left.Active) {
		getQuadBoundries(&pos_X0, &pos_X1, &pos_Y0, &pos_Y1);

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
