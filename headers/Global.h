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
#define VERSION_PATCH 6

// refresh rates
#define CPS 30
#define FPS 30

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
	RENDER_DEFAULT	 =	0x00000000UL,
	RENDER_GAME		 =	0x00000001UL,
	RENDER_WIREFRAME =	0x00000010UL,
};

// anchor points for screen elements
enum Anchor {
	Middle		= 0x02,
	TopLeft		= 0x04,
	TopRight	= 0x08,
	BottomLeft	= 0x16,
	BottomRight = 0x32,
};


///////////////////
// Structs       //
///////////////////


/////////////////////
// Variables       //
/////////////////////

// rendering options
extern ULONG renderOpt;
//extern UINT renderMode;


///////////////////////
// Garbage Collector //
///////////////////////

void DestroyGlobals();