#pragma once
#include "elements\PhysicalElement.h"

class Bow : public PhysicalElement {
public:
	Bow();
	Bow(Graphic* _graphic, Camera* _camera, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr);
	~Bow();
};

