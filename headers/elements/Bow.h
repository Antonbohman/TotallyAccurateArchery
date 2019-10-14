#pragma once
#include "elements\PhysicalElement.h"

class Bow : public PhysicalElement {
private:
	int rotationDirection = -1;

	Vector3 direction;
	float efficiencyFactor; //"e"
	float mass;
	float drawDistance = 0.5; //"x"
	float drawForce = 700; //"F"
	float scalingFactor; //"k"
	

public:
	Bow();
	Bow(Graphic* _graphic, Camera* _camera, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr,
		Vector3 _direction, float _efficiencyFactor, float _mass, float _scalingFactor);
	~Bow();

	Vector3 fireArrow(float arrowMass);

	void Bow::updateElement(XMFLOAT2 camera, MouseInfo mouse);

};

