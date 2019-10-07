#pragma once
#include "elements\AbstractElement.h"
#include "Input.h"

class Button : public AbstractElement {
public:
	Button();
	Button(Graphic* _graphic, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr);
	~Button();

	bool isPressed(const MouseInfo* mouse);
};

