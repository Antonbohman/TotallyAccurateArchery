/*
* target.h/target.cpp
* A physical element class for drawing our target element
* that can be collided by our arrows.
*
* Written and all rights reserved by: Filip Unger & Anton Bohman
*/

#include "elements\Target.h"

Target::Target() : PhysicalElement() {
	hitbox = nullptr;
}

Target::Target(Graphic* _graphic, Camera* _camera, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr) : PhysicalElement(_graphic, _camera, posToSet, sizeToSet, harbor, texturePtr) {
	float xLeft = 0;
	float yTop = 0;

	switch (anchor) {
	case Middle:
		xLeft = posToSet.x - (sizeToSet.x / 2);
		yTop = posToSet.y + (sizeToSet.y / 2);
		break;
	case TopLeft:
		xLeft = posToSet.x;
		yTop = posToSet.y;
		break;
	case TopRight:
		xLeft = posToSet.x - sizeToSet.x;
		yTop = posToSet.y;
		break;
	case BottomLeft:
		xLeft = posToSet.x;
		yTop = posToSet.y + sizeToSet.y;
		break;
	case BottomRight:
		xLeft = posToSet.x - sizeToSet.x;
		yTop = posToSet.y + sizeToSet.y;
		break;
	}

	xLeft += (sizeToSet.x*0.20f);

	//creates an alternative hitbox in middle of target to make our shoot get stuck a bit into our targets
	hitbox = new PhysicalElement(_graphic, _camera, { xLeft, yTop, (posToSet.z+0.00001f) }, { (sizeToSet.x*0.2f), sizeToSet.y }, TopLeft, nullptr);
}

Target::~Target() {
	delete hitbox;
}

void Target::renderElement() {
	//alternative rendering to be able to move our child hitbox correctly as well
	PhysicalElement::renderElement();

	hitbox->moveWorldToView();
	hitbox->renderElement();
}
