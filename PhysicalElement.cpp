#include "elements/PhysicalElement.h"

PhysicalElement::PhysicalElement() : BaseElement() {

}

PhysicalElement::PhysicalElement(Graphic* _graphic, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr) : BaseElement(_graphic, posToSet, sizeToSet, harbor, texturePtr) {

}

PhysicalElement::~PhysicalElement() {

}

void PhysicalElement::moveWorldToView() {

}