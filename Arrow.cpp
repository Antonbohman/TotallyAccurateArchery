/*
* arrow.h/arrow.cpp
* A physical element class for drawing an arrow element
* that can be collided with targets and ground. The arrow is also
* interacted with our current wind, ground gravity and air density.
*
* Written and all rights reserved by: Filip Unger & Anton Bohman
*/

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

	//creates a child hitbox for only the tip of arrow
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
	delete hitbox;
}

bool Arrow::isColliding(PhysicalElement* otherObject) {
	return hitbox->isColliding(otherObject);
}

float Arrow::calcArea(Vector3 windDirection) {
	//rotates arrow and relative wind so that the relative wind is perpendicular towards one axis, this case X-axis
	Vector3 arrowDirection(0.0f, -1.0f, 0.0f);

	windDirection.Normalize();
	
	float angle = 0;
	if (windDirection.x > 0 || (windDirection.x == 0 && windDirection.y > 0)) {
		angle = XM_PI+acos(windDirection.Dot(-arrowDirection));
	} else {
		angle = acos(windDirection.Dot(arrowDirection));
	}

	angle = rotation - angle;
	
	//the second rotation here is not really needed here since we have already aligned it along one axis(X-axis) and the x-cordinates
	//for the vectors will still be the same even if rotate it around its own axis, but since this was as showned on the presentation it will remain here
	//rotateX(arrow width as vector); rotateY(arrow height as vector)
	XMFLOAT3 rotateX;
	XMStoreFloat3(
		&rotateX,
		XMVector3Rotate(
			XMVector3Rotate(
				XMVectorSet(size.x, 0.0f, 0.0f, 0.0f),
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
				XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f),
				XMQuaternionRotationAxis(
					XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f),
					angle
				)
			),
			XMQuaternionRotationAxis(
				XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f),
				0.5*XM_PI
			)
		)
	);

	//take out only the maximum distance in x-axis since that will be our new length
	Vector3 diagonal(rotateX.x - rotateY.x, 0.0f, 0.0f);
	//make sure the length is always positive
	float length = diagonal.Length();

	//return the length as of the arrow where the wind is hitting multiplied with the depth of the arrow (in meters)
	//the depth will always be constant on our arrow
	return (convertPixelToMeter(&length) * 0.01);
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

	float area = calcArea(relativeVelocity);

	dragConstant = (0.5f) * fluidDensity * area * dragCoefficient; //Aim for 0.0001

	//Highest velocity 76.8 / 8.06

	//Beräkna acceleration

	acceleration = Vector3
	(
		-(dragConstant / mass) * relativeVelocity.Length() * relativeVelocity.x,
		(-(dragConstant / mass) * relativeVelocity.Length() * relativeVelocity.y) - gravity,
		0
	);

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
	//does main physics on arrow and it's flightpath
	doPhysics(deltaTime, wind);

	//make sure it stays inside considerable boundries where it can not move outside ground hitboxes and fall for eternity beneth ground
	//also stops it to go behind archer where there is no hitboxes as well
	if (worldPosition.x > 8000000) worldPosition.x = 8000000;
	if (worldPosition.x < (W_WIDTH/2)) worldPosition.x = (W_WIDTH / 2);
	if (worldPosition.y < 0) worldPosition.y = 590;

	//updates positions for arrow's child hitbox
	XMFLOAT2 dir;
	XMStoreFloat2(
		&dir,
		XMVector3Rotate(
			XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f),
			XMQuaternionRotationAxis(
				XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f),
				rotation
			)
		)
	);

	dir.x = worldPosition.x + (dir.x*42.0f);
	dir.y = worldPosition.y + (dir.y*42.0f);

	hitbox->setWorldPos(dir.x, dir.y);
}

void Arrow::arrowSnap(TextureObj* texture)
{
	//changes texture and size of arrow to a shorter version for when hitting targets
	setTexture(texture->ShaderResourceView);
	setSize(XMFLOAT2(75, 15));
}

float Arrow::getVelocity() {
	return velocity.Length();
}

void Arrow::renderElement() {
	//alternative rendering function to also update arrow's child hitbox
	PhysicalElement::renderElement();

	hitbox->setRotation(rotation);

	hitbox->moveWorldToView();
	hitbox->renderElement();
}