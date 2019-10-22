#pragma once
#include "elements\AbstractElement.h"

#include <random>
#include <ctime>

#define FIRST_QUAD 1
#define SECOND_QUAD 2
#define THIRD_QUAD 3
#define FOURTH_QUAD 4

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
	XMFLOAT2 getWindRotation();

	void updateElement(double delta);
};

