#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include "DDSTextureLoader.h"
#include "SimpleMath.h"
#include "Global.h"

using namespace DirectX;
using namespace SimpleMath;

void createVertexBuffer(int nrOfVertices, TriangleVertex ArrOfVert[]);

void loadTextures();