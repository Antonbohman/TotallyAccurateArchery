#pragma once
#include "elements\PhysicalElement.h"

class Human : public PhysicalElement {
public:
	Human();
	Human(Graphic* _graphic, Camera* _camera, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr);
	~Human();
};

