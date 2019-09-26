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

// CAMERAVIEW
Camera camera({ -40.0f,20.0f,-10.0f, 0.0f }, { 0.0f, 20.0f, 0.0f, 0.0f });
//+481.0f,20.0f,330.0f, 0.0f 

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
	
	*/
}

