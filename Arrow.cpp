#include "elements/Arrow.h"

Arrow::Arrow() : PhysicalElement()
{
}

Arrow::Arrow(Graphic * _graphic, Camera * _camera, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView * texturePtr, Vector3 dragForce, Vector3 velocity, Vector3 acceleration, float dragCoefficient, float mass, float fluidDensity) : PhysicalElement(_graphic, _camera, posToSet, sizeToSet, harbor, texturePtr)
{
	this->dragForce = dragForce;
	this->velocity = velocity;
	this->acceleration = acceleration;
	this->dragCoefficient = dragCoefficient;
	this->mass = mass;
	//this->fluidDensity = fluidDensity;
}

Arrow::~Arrow()
{
}

void Arrow::doPhysics(float deltaTime)
{
	//Beräkna DragForce

	Vector3 newVelocity = velocity;

	dragForce = dragCoefficient * velocity.LengthSquared() * -(velocity / velocity.Length());

	//Beräkna acceleration

	acceleration = dragForce / mass; //F = ma => F/m = a
	acceleration.y -= 9.82;

	//Beräkna velocity (Diffrential ekvation) FEL

	newVelocity.x += acceleration.x * deltaTime;
	newVelocity.y += acceleration.y * deltaTime;

	//Beräkna position FEL

	velocity =
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

	worldPosition += (velocity * deltaTime * 100);
}

void Arrow::updateElement(float deltaTime)
{
	doPhysics(deltaTime);
	if (worldPosition.y < 0) worldPosition.y = 1500;


}
