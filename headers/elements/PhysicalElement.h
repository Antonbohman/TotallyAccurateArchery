#pragma once
#include "elements/BaseElement.h"
#include "elements/Camera.h"

class PhysicalElement : public BaseElement {
	bool Moving;
	XMFLOAT3 Movement;
	
	XMFLOAT3 worldPosition;

	void moveWorldToView();

public:
	PhysicalElement();
	PhysicalElement(Graphic* _graphic = nullptr, XMFLOAT3 posToSet = XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2 sizeToSet = XMFLOAT2(0.0f, 0.0f), UINT harbor = 0, ID3D11ShaderResourceView* texturePtr = nullptr);
	virtual ~PhysicalElement();

	//Calc movement();

};

