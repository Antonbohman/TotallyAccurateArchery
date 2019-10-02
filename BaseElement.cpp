#include "elements/BaseElement.h"

BaseElement::BaseElement() {
	colour = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	size = XMFLOAT2(0.0f, 0.0f);
	anchor = TopLeft;

	graphic = nullptr;

	quadBuffer = nullptr;
	
	shaderResourceView = nullptr;
}

BaseElement::BaseElement(Graphic* _graphic, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr)
{
	colour = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	position = posToSet;
	size = sizeToSet;
	anchor = Anchor(harbor);

	graphic = _graphic;

	quadBuffer = nullptr;

	shaderResourceView = texturePtr;

	createVertexBuffer();
}

BaseElement::~BaseElement() {
	if (quadBuffer) quadBuffer->Release();
}

XMFLOAT2 BaseElement::rotatePoint(float x, float y) {
	
	float zeroF = 0.0f;

	x -= position.x;
	y -= position.y;

	XMFLOAT2 newPoint(x, y);
	
	/*XMVECTOR rotatedPoint = XMVector3Transform(
		XMVectorSet(x, y, zeroF, zeroF),
		XMMatrixRotationY(rotation)
	);

	XMStoreFloat2(
		&newPoint,
		rotatedPoint
	);*/

	newPoint.x += position.x;
	newPoint.y += position.y;

	return newPoint;
}

void BaseElement::createVertexBuffer() {
	// Describe the Vertex Buffer
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.ByteWidth = sizeof(TriangleVertex) * 6;

	// create a Vertex Buffer
	graphic->device->CreateBuffer(&bufferDesc, nullptr, &quadBuffer);
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

	XMFLOAT2 NE = rotatePoint(pos_X0, pos_Y0);
	XMFLOAT2 NW = rotatePoint(pos_X1, pos_Y0);
	XMFLOAT2 SE = rotatePoint(pos_X0, pos_Y1);
	XMFLOAT2 SW = rotatePoint(pos_X1, pos_Y1);

	if (spriteInfo.spritesheet) {
		float xSplit = 1 / spriteInfo.columns;
		float ySplit = 1 / spriteInfo.rows;


	}

	TriangleVertex vertices[6] =
	{
		//v0
		NE.x, NE.y, position.z,						//pos
		colour.x, colour.y, colour.z, colour.w,		//colour
		uv.X0, uv.Y0,								//uv

		//v1
		NW.x, NW.y, position.z,						//pos
		colour.x, colour.y, colour.z, colour.w,		//colour
		uv.X1, uv.Y0,								//uv

		//v2
		SE.x, SE.y, position.z,						//pos
		colour.x, colour.y, colour.z, colour.w,		//colour
		uv.X0, -uv.Y1,								//uv

		//v3
		NW.x, NW.y, position.z,						//pos
		colour.x, colour.y, colour.z, colour.w,		//colour
		uv.X1, uv.Y0,								//uv

		//v4
		SW.x, SW.y, position.z,						//pos
		colour.x, colour.y, colour.z, colour.w,		//colour
		uv.X1, uv.Y1,								//uv

		//v5
		SE.x, SE.y, position.z,						//pos
		colour.x, colour.y, colour.z, colour.w,		//colour
		uv.X0, uv.Y1,								//uv
	};

	//create a subresource for our data
	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(data));
	data.pSysMem = vertices;

	//create a subresource to hold our data while we copy between cpu and gpu memory
	D3D11_MAPPED_SUBRESOURCE mappedMemory;

	//copy and map our cpu memory to our gpu buffert
	graphic->deviceContext->Map(quadBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedMemory);
	memcpy(mappedMemory.pData, &data, sizeof(TriangleVertex) * 6);
	graphic->deviceContext->Unmap(quadBuffer, 0);
}

void BaseElement::renderElement() {
	createQuad();

	graphic->setTextureResource(shaderResourceView);
	graphic->setVertexBuffer(quadBuffer, 6, sizeof(TriangleVertex), 0);

	graphic->Process();
}