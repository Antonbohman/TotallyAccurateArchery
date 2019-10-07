#pragma once
#include "elements/PhysicalElement.h"

class Arrow : public PhysicalElement
{
private:
	Vector3 dragForce;
	Vector3 velocity;
	Vector3 acceleration;
	float dragCoefficient;
	float mass;
	//const float fluidDensity = 1.225f; Dis air
	float fluidDensity;

public:

	Arrow();
	Arrow(Graphic* _graphic, Camera* _camera, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr, Vector3 dragForce, Vector3 velocity, Vector3 acceleration, float dragCoefficient, float mass,	float fluidDensity);
	~Arrow();

	void doPhysics(float deltaTime);
};