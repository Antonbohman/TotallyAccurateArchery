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