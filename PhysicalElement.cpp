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

double PhysicalElement::convertPixelToMeter(const float* pixels) {
	return (double)*pixels / (double)100;
}

float PhysicalElement::convertMeterToPixel(const double* meters) {
	return (float)round(*meters * 100);
}

void PhysicalElement::setAsCameraFocus() {
	camera->setFocus(this);
}

XMFLOAT2 PhysicalElement::getWorldPos() {
	return XMFLOAT2(worldPosition.x, worldPosition.y);
}

void PhysicalElement::moveWorldToView() {
	XMFLOAT2 offset = camera->getPos();

	viewPosition.x = worldPosition.x - offset.x;
	viewPosition.y = worldPosition.y - offset.y;
}

bool PhysicalElement::isColliding(PhysicalElement otherObject)
{
	//This might be stupid

	Vector2 distanceBetweenObjects;
	distanceBetweenObjects.x = (worldPosition.x - otherObject.worldPosition.x);
	distanceBetweenObjects.y = (worldPosition.y - otherObject.worldPosition.y);

	float maxSize = pow(pow(size.x, 2) + pow(size.y, 2), 0.5);

	if (distanceBetweenObjects.Length() <= maxSize)
	{
		float X0, X1, Y0, Y1;
		getQuadBoundries(&X0, &X1, &Y0, &Y1);

		float otherX0, otherX1, otherY0, otherY1;
		getQuadBoundries(&otherX0, &otherX1, &otherY0, &otherY1);

		if (X1 < otherX1 && X1 > otherX0)
		{
			if ((Y0 > otherY0 && Y0 < otherY1) ||
				(Y1 > otherY0 && Y1 < otherY1))
			{
				//this->moving = false;
				return true;
			}
		}
	}

	return false;
}

void PhysicalElement::updateElement() 
{

}