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
	XMFLOAT2 getPos();

	void setAnimation(float _acceleration, float _maxVelocity);
	void clearAnimation();

	void setDelay(double _delay);
};