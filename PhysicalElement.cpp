#include "elements/PhysicalElement.h"

PhysicalElement::PhysicalElement() : BaseElement() {
	camera = nullptr;
	worldPosition = XMFLOAT3(0.0f, 0.0f, 0.0f);
}

PhysicalElement::PhysicalElement(Graphic* _graphic, Camera* _camera, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr) : BaseElement(_graphic, posToSet, sizeToSet, harbor, texturePtr) {
	camera = _camera;
	worldPosition = posToSet;
}

PhysicalElement::~PhysicalElement() {

}

void PhysicalElement::getQuadBoundriesWorld(float* pos_X0, float* pos_X1, float* pos_Y0, float* pos_Y1) {
	switch (anchor) {
	case Middle:
		*pos_X0 = worldPosition.x - (size.x / 2);
		*pos_X1 = worldPosition.x + (size.x / 2);
		*pos_Y0 = worldPosition.y - (size.y / 2);
		*pos_Y1 = worldPosition.y + (size.y / 2);
		break;
	case TopLeft:
		*pos_X0 = worldPosition.x;
		*pos_X1 = worldPosition.x + size.x;
		*pos_Y0 = worldPosition.y - size.y;
		*pos_Y1 = worldPosition.y;
		break;
	case TopRight:
		*pos_X0 = worldPosition.x - size.x;
		*pos_X1 = worldPosition.x;
		*pos_Y0 = worldPosition.y - size.y;
		*pos_Y1 = worldPosition.y;
		break;
	case BottomLeft:
		*pos_X0 = worldPosition.x;
		*pos_X1 = worldPosition.x + size.x;
		*pos_Y0 = worldPosition.y;
		*pos_Y1 = worldPosition.y + size.y;
		break;
	case BottomRight:
		*pos_X0 = worldPosition.x - size.x;
		*pos_X1 = worldPosition.x;
		*pos_Y0 = worldPosition.y;
		*pos_Y1 = worldPosition.y + size.y;
		break;
	}
}


void PhysicalElement::setAsCameraFocus() {
	camera->setFocus(this);
}

XMFLOAT2 PhysicalElement::getWorldPos() {
	return XMFLOAT2(worldPosition.x, worldPosition.y);
}

void PhysicalElement::moveWorldToView() {
	XMFLOAT2 offset = camera->getOffset();

	viewPosition.x = worldPosition.x - offset.x;
	viewPosition.y = worldPosition.y - offset.y;
}

bool PhysicalElement::isColliding(PhysicalElement* otherObject)
{
		float X0, X1, Y0, Y1;
		getQuadBoundriesWorld(&X0, &X1, &Y0, &Y1);

		float otherX0, otherX1, otherY0, otherY1;
		otherObject->getQuadBoundriesWorld(&otherX0, &otherX1, &otherY0, &otherY1);

		if ((X0 > otherX0 && X0 < otherX1) ||
			(X1 > otherX0 && X1 < otherX1))
		{
			if (Y0 < 10) { 
				int x = x; }
			if (Y0 < 0) { 
				int x = x; }

			if ((Y0 > otherY0 && Y0 < otherY1) ||
				(Y1 > otherY0 && Y1 < otherY1))
			{
				//this->moving = false;
				return true;
			}
		}

	return false;
}

void PhysicalElement::updateElement() 
{

}