/*
* camera.h/camera.cpp
* An abstract element class for creating an element working as a camera view
* It moves around and returns offsets for other elements so they can align 
* themself according to our currnet view. Camera movement can be set to be
* animated and delayed to smoothen the movement of the camera instead of
* instant adjustment.
*
* Written and all rights reserved by: Filip Unger & Anton Bohman
*/

#pragma once
#include "elements/AbstractElement.h"
#include "elements/PhysicalElement.h"

class PhysicalElement;

class Camera : public AbstractElement {
private:
	PhysicalElement* focus;
	XMFLOAT2 focusPos;
	float acceleration;
	float maxVelocity;
	float velocity;
	float delay;

public:
	Camera();
	Camera(Graphic* _graphic, XMFLOAT3 posToSet);
	~Camera();
	
	void setFocus(PhysicalElement* target);
	void setFocus(XMFLOAT2 newPos);
	void clearFocus();
	void updateFocus(double delta);

	XMFLOAT2 getOffset();
	XMFLOAT2 getOffsetMeter();
	XMFLOAT2 getPos();

	void setAnimation(float _acceleration, float _maxVelocity);
	void clearAnimation();

	void setDelay(double _delay);
};