#pragma once
#include "elements/PhysicalElement.h"
#include "elements/Bow.h"
#include "elements/Wind.h"

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

	PhysicalElement* hitbox;

public:

	Arrow();
	Arrow(Graphic* _graphic, Camera* _camera, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr, Vector3 velocity, float dragCoefficient, float mass, float fluidDensity, float gravity);
	~Arrow();

	float calcArea(Wind* wind);
	float getDragCoefficient();

	void doPhysics(float deltaTime, Wind* wind);
	void updateElement(float deltaTime, Wind* wind);

	void arrowSnap(TextureObj* texture);

	float getVelocity();

	void renderElement();
};