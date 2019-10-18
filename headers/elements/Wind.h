#pragma once
#include "elements\AbstractElement.h"



class Wind : public AbstractElement {
protected:
	XMFLOAT2 direction;
	float speed;
	float currRotation;
	float targetRotation;

public:
	Wind();
	Wind(Graphic* graphic, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr);
	~Wind();

	void randomizeWind() {};
	XMFLOAT3 getWindDirectionAndSpeed() {};

	void updateElement() {};
};

