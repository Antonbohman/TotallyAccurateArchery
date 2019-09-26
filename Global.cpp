#include "Global.h"
// rendering options
ULONG renderOpt = RENDER_GAME;
UINT renderMode = 0;

/*
int gnrOfVert[OBJECTS];
ID3D11Buffer *ppVertexBuffers[OBJECTS];

ID3D11Buffer *heightmapBuffer;
int nrOfHMVert;
int nrOfVertexBuffers;
//int gTotalNrOfVert = 0;
char* textureName = nullptr;

ID3D11Buffer* gDeferredQuadBuffer = nullptr;

RenderOptions* gRenderingOptionsData = nullptr;
ID3D11Buffer* gRenderingOptionsBuffer = nullptr;


// CAMERAVIEW
Camera camera({ -40.0f,20.0f,-10.0f, 0.0f }, { 0.0f, 20.0f, 0.0f, 0.0f });
//+481.0f,20.0f,330.0f, 0.0f 


//int* elementsIndex = new int (1024);

int elementsAmount =2048;

Point* copies= new Point[elementsAmount];

int objectsFromFrustum = 0;

int objectsCulledFromQuad = 0;

int* elementsIndexQuadCulling = new int[elementsAmount];

int* elementsIndexFrustumCulling = new int [elementsAmount];


//Frustum frustumCamera(&camera);

WorldSpace worldObjects[5] = {
	{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
	{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 40.0f, 1.0f, 1.0f, 1.0f },
	{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -40.0f, 1.0f, 1.0f, 1.0f },
	{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
	{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f }
};

//World/View/Projection
XMMATRIX World;
XMMATRIX View;
XMMATRIX ViewRotated[5];
XMMATRIX Projection;


Heightmap g_heightmap;
TriangleVertex* g_map;



*/

// terminate function for globals
void DestroyGlobals() {
	/*

	//gVertexBuffer->Release();
	gDeferredQuadBuffer->Release();

	gLightDataBuffer->Release();

	_aligned_free(gRenderingOptionsData);
	gRenderingOptionsBuffer->Release();

	_aligned_free(gAmbientSpecularData);
	gAmbientSpecularBuffer->Release();

	_aligned_free(gCameraMatrix);
	gCameraMatrixBuffer->Release();

	_aligned_free(gWorldMatrix);
	gWorldMatrixBuffer->Release();

	_aligned_free(gObjectMatrix);
	gObjectMatrixBuffer->Release();

	for (int i = 0; i < G_BUFFER; i++) {
		if (gRenderTargetViewArray[i]) {
			gRenderTargetViewArray[i]->Release();
		}

		if (gShaderResourceViewArray[i]) {
			gShaderResourceViewArray[i]->Release();
		}

		if (gRenderTargetTextureArray[i]) {
			gRenderTargetTextureArray[i]->Release();
		}
	}
	
	*/
}

