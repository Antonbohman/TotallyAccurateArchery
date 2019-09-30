#include "elements/BaseElement.h"



void BaseElement::renderElement()
{
	
}

void BaseElement::createVertices()
{
}

BaseElement::BaseElement() {
	position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	size = XMFLOAT2(0.0f, 0.0f);
	anchor = TopLeft;

	texture2D = nullptr;
	shaderResourceView = nullptr;

}

BaseElement::BaseElement(XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, Anchor harbor, ID3D11Device* device, const wchar_t * textureName)
{
	position = posToSet;
	size = sizeToSet;
	anchor = harbor;

	CreateDDSTextureFromFile(device, textureName, &texture2D, &shaderResourceView);
}


BaseElement::~BaseElement() {
	texture2D = nullptr;
	shaderResourceView = nullptr;
}
