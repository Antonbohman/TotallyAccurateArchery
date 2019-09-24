#pragma once
#include <windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")

using namespace DirectX;

bool keyReleased = true;

class Graphic {
private:
	HWND wndHandle;

	//HRESULT CreateDirect3DContext(HWND wndHandle);
	//HRESULT SetRasterizerState();
	//updateRenderingOptions();
	
	//CreateDirect3DContext(wndHandle);
	//CreateSampling();
	//CreateDeferredQuad();
	//CreateMenuContext();

public:
	ID3D11Device* gDevice = nullptr;
	ID3D11DeviceContext* gDeviceContext = nullptr;

	Graphic(HWND wndHandle);
	virtual ~Graphic();

	void Update();
	void Process();
};





