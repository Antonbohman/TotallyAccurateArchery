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
	XMFLOAT3 windDirSpeed = wind->getWindDirectionAndSpeed();
	
	float pos_X0 = 0, pos_X1 = 0, pos_Y0 = 0, pos_Y1 = 0;
	getQuadBoundriesWorld(&pos_X0, &pos_X1, &pos_Y0, &pos_Y1);
		
	float value = pos_X1 - pos_X0;

	double base = convertPixelToMeter(&value);

	value = windDirSpeed.y*windDirSpeed.z;

	double height = convertPixelToMeter(&value);

	float areaA = base * height;

	value = windDirSpeed.x*windDirSpeed.z;

	base = convertPixelToMeter(&value);
	
	value = pos_Y1 - pos_Y0;

	height = convertPixelToMeter(&value);

	float areaB = base * height;

	return areaA + areaB;
}

void Arrow::doPhysics(float deltaTime, Wind* wind)
{
	Vector3 newVelocity = velocity;

	//Calculate dragCoefficient
	XMFLOAT3 windDirSpeed = wind->getWindDirectionAndSpeed();

	Vector3 windVelocity = Vector3
	(
		windDirSpeed.x,
		windDirSpeed.y,
		0
	) * windDirSpeed.z;

	Vector3 relativeVelocity = velocity - windVelocity;

	//Create vector with an 90 angle to the wind relative to the object. (A)

	Vector3 angledVector = -relativeVelocity;
	angledVector = Vector3
	(
		-angledVector.y,
		angledVector.x,
		0
	);

	//Create two vectors: V:X0->Y1, U:X1->Y0
	float pos_X0 = 0, pos_X1 = 0, pos_Y0 = 0, pos_Y1 = 0;
	getQuadBoundriesWorld(&pos_X0, &pos_X1, &pos_Y0, &pos_Y1);

	Vector3 vectorV = Vector3(pos_X1, pos_Y1, 0) - Vector3(pos_X0, pos_Y0, 0);
	Vector3 vectorU = Vector3(pos_X1, pos_Y0, 0) - Vector3(pos_X0, pos_Y1, 0);

	//Do the dot-products between V and A, and U and A. The larger value times 1cm is the area.

	float area = fmax(angledVector.Dot(vectorV), angledVector.Dot(vectorU));

	//dragCoefficient = (0.5f) * fluidDensity * calcArea(wind) * 1.63265306123f;
	dragCoefficient = (0.5f) * fluidDensity * area * 1.63265306123f;

	//float dragForce = calcArea(wind) * fluidDensity * 1.63265306123f / 2;

	//Ber�kna acceleration

	acceleration = Vector3
	(
		(dragCoefficient / mass) * velocity.Length() * velocity.x,
		((dragCoefficient / mass) * velocity.Length() * velocity.y) - gravity,
		0
	);

	//acceleration = -relativeVelocity * dragForce / mass;

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