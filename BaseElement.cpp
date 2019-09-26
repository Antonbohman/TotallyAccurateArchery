#include "elements/BaseElement.h"



BaseElement::BaseElement() {
	Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	Size = XMFLOAT2(0.0f, 0.0f);
	anchor = TopLeft;

	texture2D = nullptr;
	ShaderResourceView = nullptr;

}

BaseElement::BaseElement(XMFLOAT3 PosToSet, XMFLOAT2 SizeToSet, Anchor Harbor, ID3D11Device* device, const wchar_t * textureName)
{
	Position = PosToSet;
	Size = SizeToSet;
	anchor = Harbor;

	CreateDDSTextureFromFile(device, textureName, &texture2D, &ShaderResourceView);
}


BaseElement::~BaseElement() {
}
