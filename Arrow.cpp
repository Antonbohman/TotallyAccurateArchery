#include "elements/Arrow.h"

Arrow::Arrow() : PhysicalElement()
{
}

Arrow::Arrow(Graphic * _graphic, Camera * _camera, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView * texturePtr, /*Vector3 dragForce, */Vector3 velocity, /*Vector3 acceleration, */float dragCoefficient, float mass/*, float fluidDensity*/) : PhysicalElement(_graphic, _camera, posToSet, sizeToSet, harbor, texturePtr)
{
	//this->dragForce = dragForce;
	this->velocity = velocity;
	//this->acceleration = acceleration;
	this->dragCoefficient = dragCoefficient;
	this->mass = mass;
	//this->fluidDensity = fluidDensity;
}

Arrow::~Arrow()
{
}

void Arrow::doPhysics(float deltaTime)
{
	Vector3 newVelocity = velocity;

	//Ber�kna acceleration

	acceleration = Vector3
	(
		-(dragCoefficient / mass) * velocity.Length() * velocity.x,
		(-(dragCoefficient / mass) * velocity.Length() * velocity.y) - 9.82,
		0
	);

	//Ber�knar velocity a = v * dt

	newVelocity.x += acceleration.x * deltaTime;
	newVelocity.y += acceleration.y * deltaTime;

	//Ber�kna position, genomsnittsv�rde f�r hastighet

	Vector3 averageVelocity =
		Vector3(
		((velocity.x + newVelocity.x) / 2.0f),
			((velocity.y + newVelocity.y) / 2.0f),
			(0)
		);

	if (velocity.y > 0)
	{
		rotation = -acos(((velocity.Dot(Vector3(1, 0, 0)) / (velocity.Length()))));
	}
	else
	{
		rotation = acos(((velocity.Dot(Vector3(1, 0, 0)) / (velocity.Length()))));
	}

	worldPosition += (averageVelocity * deltaTime * 100);

	velocity = newVelocity;
}

void Arrow::updateElement(float deltaTime)
{
	doPhysics(deltaTime);

	if (worldPosition.x > 8000000) worldPosition.x = 8000000;
	if (worldPosition.x < (W_WIDTH/2)) worldPosition.x = (W_WIDTH / 2);
	if (worldPosition.y < 0) worldPosition.y = 590;
}

float Arrow::getVelocity() {
	return velocity.Length();
}