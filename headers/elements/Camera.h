#pragma once
#include "elements/AbstractElement.h"
#include "elements/PhysicalElement.h"

class PhysicalElement;

class Camera : public AbstractElement {
private:
	PhysicalElement* focus;
		
public:
	Camera();
	Camera(Graphic* _graphic, XMFLOAT3 posToSet);
	~Camera();
	
	void setFocus(PhysicalElement* target);
	void clearFocus();
	void updateFocus();
	void setPos(XMFLOAT2 newPos);
	XMFLOAT2 getPos();	
};