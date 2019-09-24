#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")

using namespace DirectX;


///////////////////
// Defines       //
///////////////////

// version
#define VERSION_MAJOR 0
#define VERSION_MINOR 1
#define VERSION_PATCH 0

// window size
#define W_WIDTH 1280.0f
#define W_HEIGHT 720.0f

//Fov (radians)
#define FOV 0.45f//0.45f

// PROJECTION RANGE
#define PROJECTION_NEAR_Z 1.0f
#define PROJECTION_FAR_Z 800.0f

// define number of vertices used in rendering
#define VERTICES 6


///////////////////
// Enums         //
///////////////////

// render types
enum RenderFlags {
	RENDER_DEFAULT = 0x00000000UL,
	RENDER_MULTI_VIEWPORT = 0x00000001UL,
	RENDER_WIREFRAME = 0x00000010UL,
	RENDER_FREE_FLIGHT = 0x00000100UL,
	RENDER_CULLING = 0x00001000UL,
	RENDER_BLOOM = 0x00010000UL,
};

// render types
enum KeyValues {
	RENDER_DEFAULT = 0x00000000UL,
	RENDER_MULTI_VIEWPORT = 0x00000001UL,
	RENDER_WIREFRAME = 0x00000010UL,
	RENDER_FREE_FLIGHT = 0x00000100UL,
	RENDER_CULLING = 0x00001000UL,
	RENDER_BLOOM = 0x00010000UL,
};


///////////////////
// Structs       //
///////////////////

// resource storing camera source
struct RenderOptions {
	bool splitView;
	UINT renderMode;
	float padding1, padding2;
};

// heightmap
struct Heightmap {
	int imageWidth;			//Width of image file
	int imageHeight;		//Height of image file
	XMFLOAT3 *verticesPos;  //Array of vertex positions
};

// resource storing ambient and specular
struct AmbientSpecular {
	XMVECTOR Ambient;
	XMVECTOR Diffuse;
	XMVECTOR Specular;
};

// resource storing camera source
struct CameraMatrix {
	XMVECTOR Origin;
	XMVECTOR Focus;
};

// a resource to store world matrix for objects in the GPU
struct ObjectW {
	XMMATRIX World;
};

// a resource to store type, origin and view,porojection matrix for lights in the GPU
struct LightVP {
	UINT LightType;
	XMFLOAT3 Origin;
	XMMATRIX ViewProjection;
	XMMATRIX RotatedViewProjection[5];
};

// a resource to store world,view,porojection matrix for object in the GPU
struct CameraWVP {
	XMMATRIX World;
	XMMATRIX ViewProjection;
	XMMATRIX RotatedViewProjection[3];
};

// basic vertex struct �
struct TriangleVertex {
	float x, y, z;
	float r, g, b;
	float u, v;
};

// basic vertex struct
struct PositionVertex {
	float x, y;
};

// resource for storing a light
struct LightData {
	int type;
	int ambient;
	float intensity;
	float lightFocus;
	XMVECTOR position;
	XMVECTOR direction;
	XMVECTOR colour;
	XMMATRIX viewProjection;
	XMMATRIX rotatedViewProjection[5];
};

struct WorldSpace {
	float rotation_x;
	float rotation_y;
	float rotation_z;
	float offset_x;
	float offset_y;
	float offset_z;
	float scale_x;
	float scale_y;
	float scale_z;
};

struct ReflectionAmount
{
	float a_r, a_g, a_b;
	float d_r, d_g, d_b;
	float s_r, s_g, s_b, s_p;
	float padding1, padding2; //Needed for Graphical Debuging, need to be x16byteWidth
};


/////////////////////
// Variables       //
/////////////////////
/*
// rendering options
extern ULONG renderOpt;
extern UINT renderMode;

// viewport
extern D3D11_VIEWPORT* vp;
extern D3D11_VIEWPORT svp[4];

// Most directX Objects are COM Interfaces
// https://es.wikipedia.org/wiki/Component_Object_Model
extern IDXGISwapChain* gSwapChain;

// Device and DeviceContext are the most common objects to
// instruct the API what to do. It is handy to have a reference
// to them available for simple applications.
extern ID3D11Device* gDevice;
extern ID3D11DeviceContext* gDeviceContext;

// sampling resource
extern ID3D11SamplerState* gSampling;

//blend resource
extern ID3D11BlendState* gBlendStateLight;

extern int gnrOfVert[OBJECTS]; //The number of vertices in each object
extern ID3D11Buffer*ppVertexBuffers[OBJECTS]; //Buffers for storing the objects
extern ID3D11Buffer *heightmapBuffer; //Buffer for storing the heightmap
extern int nrOfHMVert; //The number of vertices in the heightmap
extern int nrOfVertexBuffers; //A counter for how many vertexBuffers are being used at the moment


extern ID3D11Buffer* gDeferredQuadBuffer;

// input layouts
extern ID3D11InputLayout* gShadowVertexLayout;
extern ID3D11InputLayout* gVertexLayout;
extern ID3D11InputLayout* gLightVertexLayout;

// render targets
extern ID3D11RenderTargetView* gBackbufferRTV;
extern ID3D11Texture2D* gRenderTargetTextureArray[G_BUFFER];
extern ID3D11RenderTargetView* gRenderTargetViewArray[G_BUFFER];
extern ID3D11ShaderResourceView* gShaderResourceViewArray[G_BUFFER];

// resources for depth buffer image
extern ID3D11ShaderResourceView* gDepthShaderResourceView;
extern ID3D11DepthStencilView* gDepth;

// resources that represent shaders
extern ID3D11PixelShader* gWirePixelShader;
extern ID3D11VertexShader* gVertexShader;
extern ID3D11GeometryShader* gGeometryShader;
extern ID3D11PixelShader* gPixelShader;

extern RenderOptions* gRenderingOptionsData;
extern ID3D11Buffer* gRenderingOptionsBuffer;

extern AmbientSpecular* gAmbientSpecularData;
extern ID3D11Buffer* gAmbientSpecularBuffer;

extern CameraMatrix* gCameraMatrix;
extern ID3D11Buffer* gCameraMatrixBuffer;

extern CameraWVP* gWorldMatrix;
extern ID3D11Buffer* gWorldMatrixBuffer;

extern ObjectW* gObjectMatrix;
extern ID3D11Buffer* gObjectMatrixBuffer;

//World/View/Projection
extern XMMATRIX World;
extern XMMATRIX View;
extern XMMATRIX ViewRotated[5];
extern XMMATRIX Projection;

extern WorldSpace worldObjects[5];

//lock button presses
extern bool key_down;
extern bool key_cd;

//clear pointers
extern ID3D11ShaderResourceView* nullSRV[1];
extern ID3D11Buffer* nullCB;

extern ID3D11ShaderResourceView* gTextureSRV[OBJECTS]; //SRVs for each object
extern ID3D11Resource* gTexture2D[OBJECTS]; //Resources for each object

extern ReflectionAmount* gReflection;
extern ID3D11Buffer* reflectionBuffers[OBJECTS];

extern ID3D11ShaderResourceView* gMapTexturesSRV[4]; //SRVs for blendmapping
extern ID3D11Resource* gMapTextureResource[4]; //Resources for each object

extern ID3D11UnorderedAccessView* nullUAV; //null UAV for clearing

//Blur
extern ID3D11Texture2D* gBlurTextureDraw; //Texture2D to draw blur to
extern ID3D11Texture2D* gBlurTextureRead; //Texture2D to read from
extern ID3D11ShaderResourceView* gBlurShaderResource; //SRV for blurring
extern bool blurFilter; //Turn on and of the blurfilter with G and H
extern ID3D11Texture2D* gBlurTextureEmpty; //null texture2D for clearing


extern ID3D11UnorderedAccessView* blurUAV; //UAV for blurring
*/

///////////////////////
// Garbage Collector //
///////////////////////

void DestroyGlobals();