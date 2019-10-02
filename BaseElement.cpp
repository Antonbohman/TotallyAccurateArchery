#include "elements/BaseElement.h"

BaseElement::BaseElement() {
	position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	size = XMFLOAT2(0.0f, 0.0f);
	anchor = TopLeft;

	device = nullptr;

	quadBuffer = nullptr;
	
	shaderResourceView = nullptr;
}

BaseElement::BaseElement(XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, Anchor harbor, ID3D11Device* _device, ID3D11DeviceContext* _deviceContext, ID3D11ShaderResourceView* texturePtr)
{
	position = posToSet;
	size = sizeToSet;
	anchor = harbor;

	device = _device;
	deviceContext = _deviceContext;

	quadBuffer = nullptr;

	shaderResourceView = texturePtr;
}

BaseElement::BaseElement(XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, Anchor harbor, ID3D11Device* _device, ID3D11DeviceContext* _deviceContext, ID3D11ShaderResourceView* texturePtr, int columns, int rows) {
	position = posToSet;
	size = sizeToSet;
	anchor = harbor;

	device = _device;
	deviceContext = _deviceContext;

	quadBuffer = nullptr;

	shaderResourceView = texturePtr;

	spriteInfo.spritesheet = true;
	spriteInfo.columns = columns;
	spriteInfo.rows = rows;
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
	bufferDesc.ByteWidth = sizeof(vertices) * 6; //Inte säker på varför vi har 6st verts men lämnar det till dig.

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(data));
	data.pSysMem = vertices;

	// create a Vertex Buffer
	device->CreateBuffer(&bufferDesc, &data, &quadBuffer);
}
