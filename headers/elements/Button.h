/*
* button.h/button.cpp
* An abstract element class for creating an element working as a button
* It can calculate if it has been pushed.
*
* Written and all rights reserved by: Filip Unger & Anton Bohman
*/

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

