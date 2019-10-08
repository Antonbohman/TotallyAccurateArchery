#include "Arrow.h"



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
	this->fluidDensity = fluidDensity;
}

Arrow::~Arrow()
{
}

void Arrow::doPhysics(float deltaTime)
{
	//Beräkna position

	deltaTime = 0.01;

	worldPosition.x += (velocity.x * deltaTime);
	worldPosition.y += (velocity.y * deltaTime); //Känns för lätt

	//Beräkna DragForce

	Vector2 realSize;
	realSize.x = float(0.3); 
	realSize.y = float(0.04);

	dragForce.x = 0.5 * fluidDensity * pow(velocity.x, 2)
		* realSize.y * dragCoefficient; //Delar upp dem för att få alla olika dimensioner

	dragForce.y = 0.5 * fluidDensity * pow(velocity.y, 2)
		* realSize.x * dragCoefficient; //Funkar det?

	//Beräkna acceleration

	acceleration.x = -(dragForce.x * velocity.x) / (mass * velocity.Length());
	acceleration.y = -9.82 /*- (dragForce.y * velocity.y) / (mass * velocity.Length())*/;

	//Beräkna velocity (Diffrential)

	velocity.x += acceleration.x * deltaTime;
	velocity.y += acceleration.y * deltaTime;
}

void Arrow::updateElement(float deltaTime)
{
	doPhysics(deltaTime);
	if (worldPosition.y < 0) worldPosition.y = 1500;


}
