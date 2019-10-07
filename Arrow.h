#pragma once
#include "elements/PhysicalElement.h"

class Arrow : public PhysicalElement
{
private:
	bool moving;
	Vector3 dragForce;
	Vector3 velocity;
	Vector3 acceleration;
	float dragCoefficient;
	float mass;
	//const float fluidDensity = 1.225f; Dis air
	float fluidDensity;

public:
	void doPhysics(float deltaTime);
};