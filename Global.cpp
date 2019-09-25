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

AmbientSpecular* gAmbientSpecularData = nullptr;
ID3D11Buffer* gAmbientSpecularBuffer = nullptr;

CameraMatrix* gCameraMatrix = nullptr;
ID3D11Buffer* gCameraMatrixBuffer = nullptr;

CameraWVP* gWorldMatrix = nullptr;
ID3D11Buffer* gWorldMatrixBuffer = nullptr;

ObjectW* gObjectMatrix = nullptr;
ID3D11Buffer* gObjectMatrixBuffer = nullptr;

LightVP* gLightMatrix = nullptr;
ID3D11Buffer* gLightMatrixBuffer = nullptr;

ID3D11Buffer* gLightDataBuffer = nullptr;


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

//clear pointers
ID3D11ShaderResourceView* nullSRV[1] = { nullptr };
ID3D11Buffer* nullCB = nullptr;

//Objects
ID3D11ShaderResourceView* gTextureSRV[OBJECTS] = { nullptr, nullptr, nullptr, nullptr, nullptr }; //SRVs for each object
ID3D11Resource* gTexture2D[OBJECTS] = { nullptr, nullptr, nullptr, nullptr, nullptr }; //Texture2Ds for each object

ReflectionAmount* gReflection = new ReflectionAmount[OBJECTS]; //How much each material reflects of each colour and light
ID3D11Buffer* reflectionBuffers[OBJECTS] = { nullptr, nullptr, nullptr, nullptr, nullptr };

//Blendmapping
ID3D11ShaderResourceView* gMapTexturesSRV[4] = { nullptr, nullptr, nullptr, nullptr }; //SRVs for blendmapping
ID3D11Resource* gMapTextureResource[4] = { nullptr, nullptr, nullptr, nullptr }; //Resources for each texture2Ds

ID3D11UnorderedAccessView* nullUAV = nullptr; //null UAV for clearing


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

