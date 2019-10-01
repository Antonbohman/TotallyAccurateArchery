#include "elements/BaseElement.h"

BaseElement::BaseElement() {
	colour = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	size = XMFLOAT2(0.0f, 0.0f);
	anchor = TopLeft;

	device = nullptr;

	quadBuffer = nullptr;
	
	shaderResourceView = nullptr;
}

BaseElement::BaseElement(XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, Anchor harbor, ID3D11Device* _device, ID3D11ShaderResourceView* texturePtr)
{
	colour = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	position = posToSet;
	size = sizeToSet;
	anchor = harbor;

	device = _device;

	quadBuffer = nullptr;

	shaderResourceView = texturePtr;
}

BaseElement::BaseElement(XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, Anchor harbor, ID3D11Device* _device, ID3D11ShaderResourceView* texturePtr, int columns, int rows) {
	colour = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	position = posToSet;
	size = sizeToSet;
	anchor = harbor;

	device = _device;

	quadBuffer = nullptr;

	shaderResourceView = texturePtr;

	spriteInfo.spritesheet = true;
	spriteInfo.columns = columns;
	spriteInfo.rows = rows;
}


BaseElement::~BaseElement() {

}

void BaseElement::createQuad() {
	float pos_X0 = 0, pos_X1 = 0, pos_Y0 = 0, pos_Y1 = 0;

	switch (anchor) {
	case Middle:
		pos_X0 = position.x - (size.x / 2);
		pos_X1 = position.x + (size.x / 2);
		pos_Y0 = position.y - (size.y / 2);
		pos_Y1 = position.y + (size.y / 2);
		break;
	case TopLeft:
		pos_X0 = position.x;
		pos_X1 = position.x + size.x;
		pos_Y0 = position.y;
		pos_Y1 = position.y + size.y;
		break;
	case TopRight:
		pos_X0 = position.x - size.x;
		pos_X1 = position.x;
		pos_Y0 = position.y;
		pos_Y1 = position.y + size.y;
		break;
	case BottomLeft:
		pos_X0 = position.x;
		pos_X1 = position.x + size.x;
		pos_Y0 = position.y - size.y;
		pos_Y1 = position.y;
		break;
	case BottomRight:
		pos_X0 = position.x - size.x;
		pos_X1 = position.x;
		pos_Y0 = position.y - size.y;
		pos_Y1 = position.y;
		break;
	}

	TriangleVertex vertices[6] =
	{
		//v0
		pos_X0, pos_Y0, position.z,					//pos
		colour.x, colour.y, colour.z, colour.w,		//colour
		uv.X0, uv.Y0,								//uv

		//v1
		pos_X1, pos_Y0, position.z,					//pos
		colour.x, colour.y, colour.z, colour.w,		//colour
		uv.X1, uv.Y0,								//uv

		//v2
		pos_X0, pos_Y1, position.z,					//pos
		colour.x, colour.y, colour.z, colour.w,		//colour
		uv.X0, -uv.Y1,								//uv

		//v3
		pos_X1, pos_Y0, position.z,					//pos
		colour.x, colour.y, colour.z, colour.w,		//colour
		uv.X1, uv.Y0,								//uv

		//v4
		pos_X1, pos_Y1, position.z,					//pos
		colour.x, colour.y, colour.z, colour.w,		//colour
		uv.X1, uv.Y1,								//uv

		//v5
		pos_X0, pos_Y1, position.z,					//pos
		colour.x, colour.y, colour.z, colour.w,		//colour
		uv.X0, uv.Y1,								//uv
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

void BaseElement::renderElement(Graphic* graphic) {
	createQuad();

	graphic->setTextureResource(shaderResourceView);
	graphic->setVertexBuffer(quadBuffer, 6, sizeof(TriangleVertex), 0);
}