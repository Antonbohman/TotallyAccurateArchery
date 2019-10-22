#pragma once
#include "elements\AbstractElement.h"

#include <random>
#include <ctime>

class Wind : public AbstractElement {
protected:
	XMFLOAT2 direction;
	float speed;
	float targetRotation;
	float rotationVelocity;

public:
	Wind();
	Wind(Graphic* graphic, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr);
	~Wind();

	void randomizeWind();
	XMFLOAT3 getWindDirectionAndSpeed();

	void updateElement(double delta);
};

