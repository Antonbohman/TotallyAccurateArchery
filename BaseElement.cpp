#include "elements/BaseElement.h"



BaseElement::BaseElement() {
	Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	Size = XMFLOAT2(0.0f, 0.0f);
	anchor = TopLeft;

	device = nullptr;

	quadBuffer = nullptr;
	
	texture2D = nullptr;
	ShaderResourceView = nullptr;
}

BaseElement::BaseElement(XMFLOAT3 PosToSet, XMFLOAT2 SizeToSet, Anchor Harbor, ID3D11Device* _device, const wchar_t * textureName)
{
	Position = PosToSet;
	Size = SizeToSet;
	anchor = Harbor;

	device = _device;

	quadBuffer = nullptr;

	CreateDDSTextureFromFile(device, textureName, &texture2D, &ShaderResourceView);
}


BaseElement::~BaseElement() {

}

void BaseElement::createQuad() {
	TriangleVertex vertices[6] =
	{
		//v0
		-1, -1, 1,	//pos
		-1, -1, 1,	//colour
		-1, -1,		//uv

		//v1
		-1, -1, 1,	//pos
		-1, -1, 1,	//colour
		-1, -1,		//uv

		//v2
		-1, -1, 1,	//pos
		-1, -1, 1,	//colour
		-1, -1,		//uv

		//v3
		-1, -1, 1,	//pos
		-1, -1, 1,	//colour
		-1, -1,		//uv

		//v4
		-1, -1, 1,	//pos
		-1, -1, 1,	//colour
		-1, -1,		//uv

		//v5
		-1, -1, 1,	//pos
		-1, -1, 1,	//colour
		-1, -1,		//uv
	};

	// Describe the Vertex Buffer
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(vertices) * 6;

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(data));
	data.pSysMem = vertices;

	// create a Vertex Buffer
	device->CreateBuffer(&bufferDesc, &data, &quadBuffer);
}