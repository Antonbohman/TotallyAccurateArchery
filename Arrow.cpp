#include "elements/Arrow.h"

Arrow::Arrow() : PhysicalElement()
{
}

Arrow::Arrow(Graphic * _graphic, Camera * _camera, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView * texturePtr, Vector3 dragForce, Vector3 velocity, Vector3 acceleration, float dragCoefficient, float mass, float fluidDensity)
{
}

Arrow::~Arrow()
{
}

void Arrow::doPhysics(float deltaTime)
{
	//Beräkna DragForce

	dragForce.x = 0.5 * fluidDensity * pow(velocity.x, 2)
		* size.y * dragCoefficient; //Delar upp dem för att få alla olika dimensioner

	dragForce.y = 0.5 * fluidDensity * pow(velocity.y, 2)
		* size.x * dragCoefficient; //Funkar det?

	//Beräkna acceleration

	acceleration.x = -(dragForce.x * velocity.x) / (mass * velocity.Length());
	acceleration.y = 9.82 + (dragForce.y * velocity.y) / (mass * velocity.Length());

	//Beräkna velocity (Diffrential)

	velocity.x = acceleration.x * deltaTime;
	velocity.y = acceleration.y * deltaTime;

	//Beräkna position

	worldPosition.x = (acceleration.x * pow(deltaTime, 2)) / 2;
	worldPosition.y = (acceleration.y * pow(deltaTime, 2)) / 2; //Känns för lätt
}
