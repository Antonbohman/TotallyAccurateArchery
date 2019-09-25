#pragma once
#include <windows.h> 
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#include "global.h"

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")

using namespace DirectX;

class Graphic {
private:
	HWND wndHandle;
	IDXGISwapChain* swapChain;

	ID3D11ShaderResourceView* depthShaderResourceView;
	ID3D11DepthStencilView* depth;

	ID3D11RenderTargetView* backbufferRTV;

	ID3D11RasterizerState* normalState;
	ID3D11RasterizerState* wireframeState;
	
	ID3D11SamplerState* sampling;

	ID3D11VertexShader* vertexShader;
	ID3D11GeometryShader* geometryShader;
	ID3D11PixelShader* pixelShader;

	ID3D11InputLayout* vertexLayout;

	D3D11_VIEWPORT* vp;

	bool initialized;
	bool first;

	HRESULT createDirect3DContext();
	HRESULT createDepthAndStencilBuffer();
	HRESULT createRenderTarget();
	HRESULT createRasterizerState();
	HRESULT createSampling();
	HRESULT createShadersAndLayout();
	void createViewport();

public:
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;

	Graphic(HWND wndHandle);
	~Graphic();

	bool Ready();
	void Update();
	void Process();

	/*
		setVertexBuffer
		setResourceView [textures]
		setConstantBuffers
	*/
};


/*
void setVertexBuffer(ID3D11Buffer* buffer, UINT32 size, UINT32 offset) {
	// specify which vertex buffer to use next.
	gDeviceContext->IASetVertexBuffers(0, 1, &buffer, &size, &offset);
}
*/
