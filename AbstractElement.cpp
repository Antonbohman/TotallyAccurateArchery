#include "elements/AbstractElement.h"


AbstractElement::AbstractElement() : BaseElement() {

}

AbstractElement::AbstractElement(Graphic* _graphic, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr) : BaseElement (_graphic, posToSet, sizeToSet, harbor, texturePtr) {

}

AbstractElement::~AbstractElement() {

}

void AbstractElement::updateElement() {

}
