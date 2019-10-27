/*
* target.h/target.cpp
* A physical element class for drawing our target element
* that can be collided by our arrows.
*
* Written and all rights reserved by: Filip Unger & Anton Bohman
*/

#pragma once
#include "elements\PhysicalElement.h"

class Target : public PhysicalElement {
public:
	PhysicalElement * hitbox;

	Target();
	Target(Graphic* _graphic, Camera* _camera, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr);
	~Target();

	void renderElement(); 
};

