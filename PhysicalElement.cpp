#include "elements/PhysicalElement.h"

PhysicalElement::PhysicalElement() : BaseElement() {
	camera = nullptr;
	worldPosition = XMFLOAT3(0.0f, 0.0f, 0.0f);
}

PhysicalElement::PhysicalElement(Graphic* _graphic, Camera* _camera, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr) : BaseElement(_graphic, posToSet, sizeToSet, harbor, texturePtr) {
	camera = _camera;
	worldPosition = posToSet;
}

PhysicalElement::~PhysicalElement() {

}

void PhysicalElement::setAsCameraFocus() {
	camera->setFocus(this);
}

XMFLOAT2 PhysicalElement::getWorldPos() {
	return XMFLOAT2(worldPosition.x, worldPosition.y);
}

void PhysicalElement::moveWorldToView() {
	XMFLOAT2 offset = camera->getPos();

	viewPosition.x = worldPosition.x - offset.x;
	viewPosition.y = worldPosition.y - offset.y;
}

void PhysicalElement::updateElement() {
}