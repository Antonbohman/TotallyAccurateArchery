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

