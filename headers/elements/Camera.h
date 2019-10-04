#pragma once
#include "elements/AbstractElement.h"

#include "Graphic.h"

class Camera : public AbstractElement {
	bool Moving;
	XMFLOAT3 Movement;

public:
	Camera();
	~Camera();
	
	void setFocus();
	XMFLOAT2 getFocus();
	
};