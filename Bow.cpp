#include "elements\Bow.h"

Bow::Bow() : PhysicalElement() {
}

Bow::Bow(Graphic* _graphic, Camera* _camera, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr,
	Vector3 _direction, float _efficiencyFactor, float _mass, float _scalingFactor) : PhysicalElement(_graphic, _camera, posToSet, sizeToSet, harbor, texturePtr) 
{
	direction = _direction;
	efficiencyFactor = _efficiencyFactor;
	mass = _mass;
	scalingFactor = _scalingFactor;
}

Bow::~Bow() {

}

Vector3 Bow::fireArrow(float arrowMass)
{
	float velocitySize = pow(
		(efficiencyFactor * drawForce * drawDistance) /
		(arrowMass + scalingFactor * mass),
		0.5
	);

	direction.Normalize();

	return(direction * velocitySize);
}

void Bow::updateElement(MouseInfo mouse) {
	Vector3 bowPos(viewPosition.x, viewPosition.y, 0);
	Vector3 mousePos(mouse.X, mouse.Y, 0);

	mousePos = mousePos - bowPos;

	bowPos.Normalize();
	mousePos.Normalize();

	

	if (rotation < -0.6 || rotation > 0.6)
		rotationDirection *= -1;
	rotation += 0.00001* rotationDirection;
	direction = Vector3
	(
		cos(-rotation),
		sin(-rotation),
		0
	);
}