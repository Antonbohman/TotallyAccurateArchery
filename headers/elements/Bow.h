#pragma once
#include "elements\PhysicalElement.h"

class Bow : public PhysicalElement {
private:
	int direction = -1;

public:
	Bow();
	Bow(Graphic* _graphic, Camera* _camera, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr);
	~Bow();

	void Bow::updateElement();

};

