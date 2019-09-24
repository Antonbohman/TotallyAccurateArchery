#include "Global.h"
// rendering options
ULONG renderOpt = RENDER_GAME;
UINT renderMode = 0;

/*
// viewport
D3D11_VIEWPORT* vp = nullptr;
D3D11_VIEWPORT svp[4];

// Most directX Objects are COM Interfaces
// https://es.wikipedia.org/wiki/Component_Object_Model
IDXGISwapChain* gSwapChain = nullptr;

// Device and DeviceContext are the most common objects to
// instruct the API what to do. It is handy to have a reference
// to them available for simple applications.
ID3D11Device* gDevice = nullptr;
ID3D11DeviceContext* gDeviceContext = nullptr;

// sampling resource
ID3D11SamplerState* gSampling = nullptr;

//blend resource
ID3D11BlendState* gBlendStateLight = nullptr;

int gnrOfVert[OBJECTS];
ID3D11Buffer *ppVertexBuffers[OBJECTS];

ID3D11Buffer *heightmapBuffer;
int nrOfHMVert;
int nrOfVertexBuffers;
//int gTotalNrOfVert = 0;
char* textureName = nullptr;

ID3D11Buffer* gDeferredQuadBuffer = nullptr;

// input layouts
ID3D11InputLayout* gShadowVertexLayout = nullptr;
ID3D11InputLayout* gVertexLayout = nullptr;
ID3D11InputLayout* gLightVertexLayout = nullptr;

// render targets
ID3D11RenderTargetView* gBackbufferRTV = nullptr;
ID3D11Texture2D* gRenderTargetTextureArray[G_BUFFER];
ID3D11RenderTargetView* gRenderTargetViewArray[G_BUFFER];
ID3D11ShaderResourceView* gShaderResourceViewArray[G_BUFFER];

// resources for depth buffer image
ID3D11ShaderResourceView* gDepthShaderResourceView = nullptr;
ID3D11DepthStencilView* gDepth = nullptr;

// resources that represent shaders
ID3D11PixelShader* gWirePixelShader = nullptr;
ID3D11VertexShader* gShadowVertexShader = nullptr;
ID3D11GeometryShader* gShadowGeometryShader = nullptr;
ID3D11PixelShader* gShadowPixelShader = nullptr;
ID3D11VertexShader* gVertexShader = nullptr;
ID3D11GeometryShader* gGeometryShader = nullptr;
ID3D11PixelShader* gPixelShader = nullptr;
ID3D11PixelShader* gBlendShader = nullptr;
ID3D11ComputeShader* gComputeShader = nullptr;
ID3D11VertexShader* gLightVertexShader = nullptr;
ID3D11PixelShader* gLightPixelShader = nullptr;

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

int currentLight = 0;
LightSource* SpotLights = nullptr;
LightSource* PointLights = nullptr;
LightSource* DirectionalLights = nullptr;
int nrOfLights[3] = { 0 };

// CAMERAVIEW
Camera camera({ -40.0f,20.0f,-10.0f, 0.0f }, { 0.0f, 20.0f, 0.0f, 0.0f });
//+481.0f,20.0f,330.0f, 0.0f 

Quadtree theObjectTree(1100, 1100, 0.0f, 0.0f);
//Quadtree theObjectTree(float(g_heightmap.imageWidth), float(g_heightmap.imageHeight), 0.0f, 0.0f);

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

//lock button presses
bool key_down = false;
bool key_cd = false;

// keeping track of current rotation
float rotation = 1.5f*XM_PI;

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


//Blur
ID3D11Texture2D* gBlurTextureDraw = nullptr;
ID3D11Texture2D* gBlurTextureRead = nullptr;
ID3D11ShaderResourceView* gBlurShaderResource = nullptr;
bool blurFilter = false;
ID3D11Texture2D* gBlurTextureEmpty;

ID3D11UnorderedAccessView* blurUAV = nullptr;
*/

// terminate function for globals
void DestroyGlobals() {
	/*delete vp;

	delete[] SpotLights;
	delete[] PointLights;
	delete[] DirectionalLights;

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

	gDepth->Release();
	gDepthShaderResourceView->Release();

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

	gSwapChain->Release();
	gDevice->Release();
	gDeviceContext->Release();*/
}

