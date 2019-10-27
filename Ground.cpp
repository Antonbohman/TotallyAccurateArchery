/*
* ground.h/ground.cpp
* A physical element class for drawing our ground element
* the ground consist of several layers that move in unison to
* create the feeling of continously movement, it also has a seperate hitbox
* and two layer arrows can fall between to simulate arrows getting stuck in ground
* it also stores different key values for different kinds of planets and ground types
*
* Written and all rights reserved by: Filip Unger & Anton Bohman
*/

#include "elements/Ground.h"

Ground::Ground() : PhysicalElement() {
	back[0] = nullptr;
	back[1] = nullptr;
	back[2] = nullptr;
	front[0] = nullptr;
	front[1] = nullptr;
	front[2] = nullptr;
}

Ground::Ground(Graphic* _graphic, Camera* _camera, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr) : PhysicalElement(_graphic, _camera, { posToSet.x, posToSet.y-14.0f, posToSet.z }, sizeToSet, harbor, nullptr) {
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

	float newSizeY = (sizeToSet.y / 0.9f);
	float newTopY = yTop + (newSizeY - sizeToSet.y);

	//create our shifted ground texture to create a gap and be able to move it continously
	back[0] = new Layer(_graphic, { xLeft, newTopY, 0.80f }, { W_WIDTH, newSizeY }, texturePtr, 0.0f);
	back[1] = new Layer(_graphic, { xLeft - W_WIDTH, newTopY, 0.80f }, { W_WIDTH, newSizeY }, texturePtr, 0.0f);
	back[2] = new Layer(_graphic, { xLeft + W_WIDTH, newTopY, 0.80f }, { W_WIDTH, newSizeY }, texturePtr, 0.0f);

	front[0] = new Layer(_graphic, { xLeft, yTop, 0.50f }, { W_WIDTH, sizeToSet.y }, texturePtr, 0.1f);
	front[1] = new Layer(_graphic, { xLeft - W_WIDTH, yTop, 0.50f }, { W_WIDTH, sizeToSet.y }, texturePtr, 0.1f);
	front[2] = new Layer(_graphic, { xLeft + W_WIDTH, yTop, 0.50f }, { W_WIDTH, sizeToSet.y }, texturePtr, 0.1f);
}

Ground::~Ground() {
	delete back[0];
	delete back[1];
	delete back[2];
	delete front[0];
	delete front[1];
	delete front[2];
}

void Ground::moveWorldToView() {
	XMFLOAT2 camPos = camera->getOffset();

	float offsetY = camPos.y;
	float offsetX = -fmod(camPos.x, W_WIDTH);

	back[0]->updateElement(offsetX, offsetY);
	back[1]->updateElement(offsetX - W_WIDTH, offsetY);
	back[2]->updateElement(offsetX + W_WIDTH, offsetY);

	front[0]->updateElement(offsetX, offsetY);
	front[1]->updateElement(offsetX - W_WIDTH, offsetY);
	front[2]->updateElement(offsetX + W_WIDTH, offsetY);
}

void Ground::renderElement() {
	back[0]->renderElement();
	back[1]->renderElement();
	back[2]->renderElement();
	front[0]->renderElement();
	front[1]->renderElement();
	front[2]->renderElement();
}

void Ground::setColour(XMFLOAT4 newColour)
{
	colour = newColour;
	front[0]->setColour(newColour);
	front[1]->setColour(newColour);
	front[2]->setColour(newColour);
	back[0]->setColour(newColour);
	back[1]->setColour(newColour);
	back[2]->setColour(newColour);
}

void Ground::setGravity(UINT gravityType) {
	//return the correct values depending on what planet we are shooting from
	switch (gravityType) {
	case GravityType::Earth:
		gravity = 9.82f;
		fluidDensity = 1.225f;
		break;
	case GravityType::Lunar:
		gravity = 1.62f;
		fluidDensity = 0.0f;
		break;
	case GravityType::Mars:
		gravity = 3.711f;
		fluidDensity = 0.02f;
		break;
	case GravityType::Sun:
		gravity = 274.0f;
		fluidDensity = 0.0002f;
		break;
	case GravityType::NoGravity:
		gravity = 0.0f;
		fluidDensity = 0.0f;
		break;
	default:
		gravity = 9.82f;
		fluidDensity = 1.225f;
		break;
	}
}

//deprecated function....
void Ground::setDensity(float newDensity)
{
	fluidDensity = newDensity;
}

float Ground::getGravity() {
	return gravity;
}

float Ground::getDensity()
{
	return fluidDensity;
}
