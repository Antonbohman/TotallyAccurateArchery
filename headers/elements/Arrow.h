#pragma once
#include "elements/PhysicalElement.h"
#include "elements/Bow.h"

class Arrow : public PhysicalElement
{
private:
	//Vector3 dragForce;
	Vector3 velocity;
	Vector3 acceleration;
	float dragCoefficient;
	float mass;
	float fluidDensity;
	float gravity;

public:

	Arrow();
	Arrow(Graphic* _graphic, Camera* _camera, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr, Vector3 velocity, float dragCoefficient, float mass, float fluidDensity, float gravity);
	~Arrow();

	void doPhysics(float deltaTime);
	void updateElement(float deltaTime);

	void arrowSnap(TextureObj* texture);

	float getVelocity();
};