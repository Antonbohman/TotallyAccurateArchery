#pragma once
#include "elements/BaseElement.h"

class PhysicalElement : public BaseElement {
	bool Moving;
	XMFLOAT3 Movement;
	
public:
	PhysicalElement();
	virtual ~PhysicalElement();
	//Calc movement();

};

