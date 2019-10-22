#include "elements\Bow.h"

Bow::Bow() : PhysicalElement() {
	drawDistance = 0;
}

Bow::Bow(Graphic* _graphic, Camera* _camera, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr, Vector3 _direction) : PhysicalElement(_graphic, _camera, posToSet, sizeToSet, harbor, texturePtr) 
{
	direction = _direction;

	drawDistance = 0;
	drawTime = 0;
	maxDrawTime = 0;
	efficiencyFactor = 0;
	mass = 0;
	scalingFactor = 0;
}

Bow::~Bow() {

}

void Bow::setBowType(UINT bowType) {
	switch (bowType) {
	case BowType::LongBow:
		drawDistance = 0;
		drawTime = 0;
		maxDrawTime = 20;

		drawForce = 700;
		efficiencyFactor = 0.9f;
		mass = 1.0f;
		scalingFactor = 0.05f;
		break;
	/*case BowType::Type2:
		drawDistance = 0;
		maxDrawTime = 0;
		break;
	case BowType::Type3:
		drawDistance = 0;
		maxDrawTime = 0;
		break;
	case BowType::Type4:
		drawDistance = 0;
		maxDrawTime = 0;
		break;
	case BowType::Type5:
		drawDistance = 0;
		maxDrawTime = 0;
		break;*/
	default:
		drawDistance = 0;
		maxDrawTime = 0;
		drawForce = 700;
		break;
	}     

	constA = 1.0f / pow(maxDrawTime, 6);
	constB = 0.0f / maxDrawTime; 
}

void Bow::drawArrow(double delta) {
	float invTime = 0;

	drawTime += delta;

	if (drawTime > maxDrawTime) drawTime = maxDrawTime;

	invTime = maxDrawTime - drawTime;

 	drawDistance = 1 - ((constA * pow(invTime, 6)) + (constB * invTime));
	drawDistance = std::fmin(drawDistance, 0.762 );
}

bool Bow::arrowReady() {
	return drawDistance ? true : false;
}

Vector3 Bow::fireArrow(float arrowMass) {
	float velocitySize = pow(
		(efficiencyFactor * drawForce * drawDistance) /
		(arrowMass + scalingFactor * mass),
		0.5
	);

	direction.Normalize();

	//zero our force ahead for next arrow
	drawDistance = 0;
	drawTime = 0;

	return(direction * velocitySize);
}

float Bow::currentDrawForce() {
	return (float)(efficiencyFactor * drawForce * drawDistance);
}

void Bow::updateElement(MouseInfo mouse) {
	Vector3 bowPos(viewPosition.x, viewPosition.y, 0);
	Vector3 mousePos(mouse.X, W_HEIGHT - mouse.Y, 0);

	Vector3 bowAim = mousePos - bowPos;
	bowAim.Normalize();

	if (bowAim.x >= 0) {
		if (bowAim.y >= 0) {
			Vector3 bowNormal(1.0f, 0.0f, 0.0f);
			rotation = 1.5+(0.5*bowNormal.Dot(bowAim));
		} else {
			Vector3 bowNormal(0.0f, -1.0f, 0.0f);
			rotation = 0.5*bowNormal.Dot(bowAim);
		}
	} else {
		if (bowAim.y >= 0) {
			rotation = 1.5;
		} else {
			rotation = 0.5;
		}
	}

	rotation *= XM_PI;

	direction = Vector3
	(
		cos(-rotation),
		sin(-rotation),
		0
	);
}