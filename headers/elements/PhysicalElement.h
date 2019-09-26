#pragma once
#include "elements/BaseElement.h"

class PhysicalElement :
	protected BaseElement {
	bool Moving;
	XMFLOAT3 Movement;

public:
	PhysicalElement();
	virtual ~PhysicalElement();
	//Calc movement();

};

