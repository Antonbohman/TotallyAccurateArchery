#include "elements/Arrow.h"

Arrow::Arrow() : PhysicalElement()
{
	hitbox = nullptr;
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

	float pos_X0 = 0, pos_X1 = 0, pos_Y0 = 0, pos_Y1 = 0;
	getQuadBoundriesWorld(&pos_X0, &pos_X1, &pos_Y0, &pos_Y1);

	hitbox = new PhysicalElement(
		_graphic,
		_camera,
		{ pos_X1 - ((sizeToSet.x * 0.05f)/2), pos_Y0 + ((pos_Y1 - pos_Y0) / 2), posToSet.z + 0.000001f },
		{ sizeToSet.x * 0.05f, sizeToSet.y },
		Middle,
		nullptr
	);
}

Arrow::~Arrow()
{
}

float Arrow::calcArea(Vector3 windDirection) {
	Vector3 arrowDirection(1.0f, 0.0f, 0.0f);

	windDirection.Normalize();
	float angle = windDirection.Dot(arrowDirection);


	float pos_X0 = 0, pos_X1 = 0, pos_Y0 = 0, pos_Y1 = 0;
	getQuadBoundriesWorld(&pos_X0, &pos_X1, &pos_Y0, &pos_Y1);

	XMFLOAT3 rotateX;
	XMStoreFloat3(
		&rotateX,
		XMVector3Rotate(
			XMVector3Rotate(
				XMVectorSet(pos_X1 - pos_X0, 0.0f, 0.0f, 0.0f),
				XMQuaternionRotationAxis(
					XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f),
					angle
				)
			),
			XMQuaternionRotationAxis(
				XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f),
				0.5*XM_PI
			)
		)	
	);

	XMFLOAT3 rotateY;
	XMStoreFloat3(
		&rotateY,
		XMVector3Rotate(
			XMVector3Rotate(
				XMVectorSet(0.0f, pos_Y1 - pos_Y0, 0.0f, 0.0f),
				XMQuaternionRotationAxis(
					XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f),
					angle
				)
			),
			XMQuaternionRotationAxis(
				XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f),
				0.5*XM_PI
			)
		)
	);

	Vector3 diagonal(rotateX.x - rotateY.x, rotateX.y - rotateY.y, rotateX.z - rotateY.z);
	float length = diagonal.Length();

	return length;
}

float Arrow::getDragCoefficient()
{
	return dragCoefficient;
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

	float a = calcArea(angledVector);

	angledVector = Vector3
	(
		-angledVector.y,
		angledVector.x,
		0
	);

	angledVector.Normalize();
	angledVector *= 0.7f;

	//Create two vectors: V:X0->Y1, U:X1->Y0
	float pos_X0 = 0, pos_X1 = 0, pos_Y0 = 0, pos_Y1 = 0;
	getQuadBoundriesWorld(&pos_X0, &pos_X1, &pos_Y0, &pos_Y1);

	Vector3 vectorV = Vector3(0.7f, 0.01f, 0);
	Vector3 vectorU = Vector3(0.7f, -0.01f, 0);

	vectorV = Vector3
	(
		vectorV.x * cos(rotation) - vectorV.y * sin(rotation),
		vectorV.x * sin(rotation) - vectorV.y * cos(rotation),
		0
	);

	vectorU = Vector3
	(
		vectorU.x * cos(rotation) - vectorU.y * sin(rotation),
		vectorU.x * sin(rotation) - vectorU.y * cos(rotation),
		0
	);

	/*vectorV = Vector3
	(
		convertPixelToMeter(&vectorV.x),
		convertPixelToMeter(&vectorV.y),
		0
	);
	vectorU = Vector3
	(
		convertPixelToMeter(&vectorU.x),
		convertPixelToMeter(&vectorU.y),
		0
	);*/


	////Do the dot-products between V and A, and U and A. The larger value times 1cm is the area.

	float area = fmax(angledVector.Dot(vectorV), angledVector.Dot(vectorU));
	if (area < 0) area *= -1;
	area = area * 0.01f;
	

	dragCoefficient = (0.5f) * fluidDensity * area * 1.63265306123f; //Aim for 0.0001

	//float dragForce = calcArea(wind) * fluidDensity * 1.63265306123f / 2;

	//Beräkna acceleration

	acceleration = Vector3
	(
		-(dragCoefficient / mass) * velocity.Length() * velocity.x,
		(-(dragCoefficient / mass) * velocity.Length() * velocity.y) - gravity,
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

void Arrow::renderElement() {
	PhysicalElement::renderElement();

	float pos_X0 = 0, pos_X1 = 0, pos_Y0 = 0, pos_Y1 = 0;
	getQuadBoundriesWorld(&pos_X0, &pos_X1, &pos_Y0, &pos_Y1);

	XMFLOAT2 rotateCord(pos_X1, pos_Y1);

	/*XMStoreFloat2(
		&rotateCord,
		XMVector3Rotate(
			XMVectorSet(pos_X1 - ((size.x * 0.05f) / 2), pos_Y0 + ((pos_Y1 - pos_Y0) / 2), 0.0f, 0.0f),
			XMQuaternionRotationAxis(
				XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f),
				rotation
			)
		)
	);*/

	hitbox->setRotation(rotation);
	hitbox->setWorldPos(rotateCord.x, rotateCord.y);

	hitbox->moveWorldToView();
	hitbox->renderElement();
}