#include "elements/BaseElement.h"

BaseElement::BaseElement() {
	colour = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	viewPosition = XMFLOAT3(0.0f, 0.0f, 0.0f);
	size = XMFLOAT2(0.0f, 0.0f);
	anchor = TopLeft;
	rotation = 0.0f;

	graphic = nullptr;
	shaderResourceView = nullptr;
	quadBuffer = nullptr;
	vertices = nullptr;
}

BaseElement::BaseElement(Graphic* _graphic, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr)
{
	colour = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	viewPosition = posToSet;
	size = sizeToSet;
	anchor = Anchor(harbor);
	rotation = 1;

	graphic = _graphic;
	shaderResourceView = texturePtr;

	createVertexBuffer();
}

BaseElement::~BaseElement() {
	if (quadBuffer) quadBuffer->Release();

	delete[] vertices;
}

XMFLOAT2 BaseElement::rotatePoint(float x, float y) {
	XMFLOAT2 newPoint(0, 0);
	
	XMStoreFloat2(
		&newPoint,
		XMVector3Rotate(
			XMVectorSet(x - viewPosition.x, y - viewPosition.y, 0.0f, 0.0f),
			XMQuaternionRotationAxis(
				XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f),
				rotation
			)
		)
	);

	newPoint.x += viewPosition.x;
	newPoint.y += viewPosition.y;

	return newPoint;
}

void BaseElement::createVertexBuffer() {
	vertices = new TriangleVertex[6];

	// Describe the Vertex Buffer
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.ByteWidth = sizeof(TriangleVertex) * 6;
	bufferDesc.StructureByteStride = sizeof(TriangleVertex);

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(data));
	data.pSysMem = vertices;

	// create a Vertex Buffer
	graphic->device->CreateBuffer(&bufferDesc, &data, &quadBuffer);
}

void BaseElement::createQuad() {
	float pos_X0 = 0, pos_X1 = 0, pos_Y0 = 0, pos_Y1 = 0;

	switch (anchor) {
	case Middle:
		pos_X0 = viewPosition.x - (size.x / 2);
		pos_X1 = viewPosition.x + (size.x / 2);
		pos_Y0 = viewPosition.y - (size.y / 2);
		pos_Y1 = viewPosition.y + (size.y / 2);
		break;
	case TopLeft:
		pos_X0 = viewPosition.x;
		pos_X1 = viewPosition.x + size.x;
		pos_Y0 = viewPosition.y - size.y;
		pos_Y1 = viewPosition.y;
		break;
	case TopRight:
		pos_X0 = viewPosition.x - size.x;
		pos_X1 = viewPosition.x;
		pos_Y0 = viewPosition.y - size.y;
		pos_Y1 = viewPosition.y;
		break;
	case BottomLeft:
		pos_X0 = viewPosition.x;
		pos_X1 = viewPosition.x + size.x;
		pos_Y0 = viewPosition.y;
		pos_Y1 = viewPosition.y + size.y;
		break;
	case BottomRight:
		pos_X0 = viewPosition.x - size.x;
		pos_X1 = viewPosition.x;
		pos_Y0 = viewPosition.y;
		pos_Y1 = viewPosition.y + size.y;
		break;
	}

	XMFLOAT2 NW = rotatePoint(pos_X0, pos_Y1);
	XMFLOAT2 NE = rotatePoint(pos_X1, pos_Y1);
	XMFLOAT2 SW = rotatePoint(pos_X0, pos_Y0);
	XMFLOAT2 SE = rotatePoint(pos_X1, pos_Y0);

	SW.x = (SW.x / (W_WIDTH / 2)) - 1;
	SW.y = (SW.y / (W_HEIGHT / 2)) - 1;

	SE.x = (SE.x / (W_WIDTH / 2)) - 1;
	SE.y = (SE.y / (W_HEIGHT / 2)) - 1;

	NW.x = (NW.x / (W_WIDTH / 2)) - 1;
	NW.y = (NW.y / (W_HEIGHT / 2)) - 1;

	NE.x = (NE.x / (W_WIDTH / 2)) - 1;
	NE.y = (NE.y / (W_HEIGHT / 2)) - 1;

	if (spriteInfo.spritesheet) {
		float xSplit = 1 / spriteInfo.columns;
		float ySplit = 1 / spriteInfo.rows;

		//fix sprite calc...
	}

	//v0
	vertices[0] = {
		NW.x, NW.y, viewPosition.z,						//pos
		colour.x, colour.y, colour.z, colour.w,		//colour
		uv.X0, uv.Y0,								//uv
	};

	//v1
	vertices[1] = {
		NE.x, NE.y, viewPosition.z,						//pos
		colour.x, colour.y, colour.z, colour.w,		//colour
		uv.X1, uv.Y0,								//uv
	};

	//v2
	vertices[2] = {		
		SW.x, SW.y, viewPosition.z,						//pos
		colour.x, colour.y, colour.z, colour.w,		//colour
		uv.X0, uv.Y1,								//uv
	};

	//v3
	vertices[3] = {
		NE.x, NE.y, viewPosition.z,						//pos
		colour.x, colour.y, colour.z, colour.w,		//colour
		uv.X1, uv.Y0,								//uv
	};

	//v4
	vertices[4] = {	
		SE.x, SE.y, viewPosition.z,						//pos
		colour.x, colour.y, colour.z, colour.w,		//colour
		uv.X1, uv.Y1,								//uv
	};

	//v5
	vertices[5] = {	
		SW.x, SW.y, viewPosition.z,						//pos
		colour.x, colour.y, colour.z, colour.w,		//colour
		uv.X0, uv.Y1,								//uv
	};

	//create a subresource to hold our data while we copy between cpu and gpu memory
	D3D11_MAPPED_SUBRESOURCE mappedMemory;
	ZeroMemory(&mappedMemory, sizeof(mappedMemory));

	//copy and map our cpu memory to our gpu buffert
	graphic->deviceContext->Map(quadBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedMemory);
	memcpy(mappedMemory.pData, vertices, sizeof(TriangleVertex) * 6);
	graphic->deviceContext->Unmap(quadBuffer, 0);
}

void BaseElement::renderElement() {
	createQuad();

	graphic->setTextureResource(shaderResourceView);
	graphic->setVertexBuffer(quadBuffer, 6, sizeof(TriangleVertex), 0);

	graphic->Process();
}