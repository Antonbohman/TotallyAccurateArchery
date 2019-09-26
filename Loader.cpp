
#include "Loader.h"
#include "Global.h"


void createVertexBuffer(int nrOfVertices, TriangleVertex ArrOfVert[]) {
	gnrOfVert[nrOfVertexBuffers] = nrOfVertices;

	// Describe the Vertex Buffer
	D3D11_BUFFER_DESC bufferDesc;
	memset(&bufferDesc, 0, sizeof(bufferDesc));
	// what type of buffer will this be?
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	// what type of usage (press F1, read the docs)
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	// how big in bytes each element in the buffer is.
	bufferDesc.ByteWidth = sizeof(TriangleVertex) * nrOfVertices;

	//int size = sizeof(gMap);

	// this struct is created just to set a pointer to the
	// data containing the vertices.
	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = (void*)ArrOfVert;

	// create a Vertex Buffer
	HRESULT error;
	error = gDevice->CreateBuffer(&bufferDesc, &data, &ppVertexBuffers[nrOfVertexBuffers]);
	nrOfVertexBuffers++;

}

void loadTextures()
{
	CreateDDSTextureFromFile(gDevice, wideChar, &gTexture2D[nrOfVertexBuffers], &gTextureSRV[nrOfVertexBuffers]);
}