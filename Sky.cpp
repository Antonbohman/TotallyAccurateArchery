/*
* sky.h/sky.cpp
* A physical element class for drawing our sky background
* the sky consist of several layers that move in unison to
* create the feeling of continously movement
*
* Written and all rights reserved by: Filip Unger & Anton Bohman
*/

#include "elements\Sky.h"

Sky::Sky() : PhysicalElement() {
	side[0] = new Side();
	side[1] = new Side();
	side[2] = new Side();
}

Sky::Sky(Graphic* _graphic, Camera* _camera, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr) : PhysicalElement(_graphic, _camera, posToSet, sizeToSet, harbor, texturePtr) {
	posToSet.z += 0.0001;
	side[0] = new Side(_graphic, posToSet, sizeToSet, harbor, texturePtr);
	posToSet.z += 0.0001;
	side[1] = new Side(_graphic, posToSet, sizeToSet, harbor, texturePtr);
	posToSet.z += 0.0001;
	side[2] = new Side(_graphic, posToSet, sizeToSet, harbor, texturePtr);
}

Sky::~Sky() {
	delete side[0];
	delete side[1];
	delete side[2];
}

void Sky::setColour(XMFLOAT4 newColour)
{
	colour = newColour;
	side[0]->setColour(newColour);
	side[1]->setColour(newColour);
	side[2]->setColour(newColour);
}

void Sky::updateElement() {
	XMFLOAT2 camPos = camera->getOffset();

	float offsetX = -fmod(camPos.x, W_WIDTH);
	float offsetY = -fmod(camPos.y, W_HEIGHT);

	viewPosition.x = offsetX;
	viewPosition.y = offsetY;

	side[0]->updateElement(offsetX + W_WIDTH, offsetY);
	side[1]->updateElement(offsetX, offsetY + W_HEIGHT);
	side[2]->updateElement(offsetX + W_WIDTH, offsetY + W_HEIGHT);
}

void Sky::renderElement() {
	side[0]->renderElement();
	side[1]->renderElement();
	side[2]->renderElement();

	PhysicalElement::renderElement();
}