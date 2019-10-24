#include "elements\Wind.h"

Wind::Wind() {
	direction = { 0,1 };
	speed = 0;
	targetRotation = 0;
	rotationVelocity = 1.0f;
}

Wind::Wind(Graphic* graphic, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr) : AbstractElement(graphic, posToSet, sizeToSet, harbor, texturePtr) {
	direction = { 0,1 };
	speed = 0;
	targetRotation = 0;
	rotationVelocity = 2.0f;
}

Wind::~Wind() {
	
}

void Wind::randomizeWind() {
	std::mt19937 rng(std::time(NULL));
	std::uniform_int_distribution<int> gen_rotation(0, 10000000); // uniform, unbiased
	std::uniform_int_distribution<int> gen_speed(0, 150000000); // uniform, unbiased

	targetRotation = gen_rotation(rng)*0.0000001;
	targetRotation -= 0.5f;

	if (targetRotation > 0) {
		targetRotation += 0.25f;
	} else {
		targetRotation *= -1;
		targetRotation += 1.25f;
	}

	targetRotation *= XM_PI;
	
	XMStoreFloat2(
		&direction,
		XMVector3Rotate(
			XMVectorSet(0, 1, 0.0f, 0.0f),
			XMQuaternionRotationAxis(
				XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f),
				targetRotation
			)
		)
	);

	speed = gen_speed(rng)*0.0000001;
	////speed = 10;

	//speed = 0.0f;

	//targetRotation = 0;
	//direction = { 0, 1 };

	///*targetRotation = 0.5f*XM_PI;
	//direction = { 1, 0 };*/
}

XMFLOAT3 Wind::getWindDirectionAndSpeed() {
	return XMFLOAT3
	(
		direction.x, 
		direction.y, 
		speed
	);
}

void Wind::updateElement(double delta) {
	double rotationDistance = rotationVelocity * delta;

	if (rotation > targetRotation) {
		(rotation - targetRotation) < rotationDistance ? rotation = targetRotation : rotation -= rotationDistance;
	} else if (rotation < targetRotation) {
		(targetRotation - rotation) < rotationDistance ? rotation = targetRotation : rotation += rotationDistance;
	}
}
