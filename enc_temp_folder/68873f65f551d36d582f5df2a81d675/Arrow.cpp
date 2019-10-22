#include "elements/Arrow.h"

Arrow::Arrow() : PhysicalElement()
{
}

Arrow::Arrow(Graphic * _graphic, Camera * _camera, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView * texturePtr, /*Vector3 dragForce, */Vector3 velocity, /*Vector3 acceleration, */float dragCoefficient, float mass, float fluidDensity, float gravity) : PhysicalElement(_graphic, _camera, posToSet, sizeToSet, harbor, texturePtr)
{
	//this->dragForce = dragForce;
	this->velocity = velocity;
	//this->acceleration = acceleration;
	this->dragCoefficient = dragCoefficient;
	this->mass = mass;
	this->fluidDensity = fluidDensity;
	this->gravity = gravity;
}

Arrow::~Arrow()
{
}

float Arrow::calcArea(Wind* wind) {
	float value;
	double base, height;
	float areaA, areaB;

	XMFLOAT3 windDirSpeed = wind->getWindDirectionAndSpeed();
	
	float pos_X0 = 0, pos_X1 = 0, pos_Y0 = 0, pos_Y1 = 0;
	getQuadBoundriesWorld(&pos_X0, &pos_X1, &pos_Y0, &pos_Y1);
		
	value = pos_X1 - pos_X0;
	base = convertPixelToMeter(&value);
	height = windDirSpeed.y*windDirSpeed.z;
	if (height < 0) height *= -1;

	areaA = base * height;

	value = pos_Y1 - pos_Y0;
	base = windDirSpeed.x*windDirSpeed.z;
	height = convertPixelToMeter(&value);
	if (base < 0) base *= -1;

	areaB = base * height;

	return areaA + areaB;
}

void Arrow::doPhysics(float deltaTime, Wind* wind)
{
	Vector3 newVelocity = velocity;

	//Calculate dragCoefficient
	/*XMFLOAT3 windDirSpeed = wind->getWindDirectionAndSpeed();

	Vector3 windVelocity = Vector3
	(
		windDirSpeed.x,
		windDirSpeed.y,
		0
	) * windDirSpeed.z;

	Vector3 relativeVelocity = velocity - windVelocity;*/

	//dragCoefficient = (0.5f) * fluidDensity * calcArea(wind) * 1.63265306123f;
	dragCoefficient = (0.5f) * fluidDensity * 0.0001 * 1.63265306123f;

	float dragForce = calcArea(wind) * fluidDensity * 1.63265306123f / 2;

	//Beräkna acceleration

	acceleration = Vector3
	(
		(dragCoefficient / mass) * velocity.Length() * velocity.x,
		((dragCoefficient / mass) * velocity.Length() * velocity.y) - gravity,
		0
	);

	//acceleration = -relativeVelocity * dragForce / mass;

	//Beräknar velocity a = v * dt

	newVelocity.x += acceleration.x * deltaTime;
	newVelocity.y += acceleration.y * deltaTime;

	//Beräkna position, genomsnittsvärde för hastighet

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

void Arrow::updateElement(float deltaTime, Wind* wind)
{
	doPhysics(deltaTime, wind);

	if (worldPosition.x > 8000000) worldPosition.x = 8000000;
	if (worldPosition.x < (W_WIDTH/2)) worldPosition.x = (W_WIDTH / 2);
	if (worldPosition.y < 0) worldPosition.y = 590;
}

void Arrow::arrowSnap(TextureObj* texture)
{
	setTexture(texture->ShaderResourceView);
	setSize(XMFLOAT2(75, 15));
}

float Arrow::getVelocity() {
	return velocity.Length();
}