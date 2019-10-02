#pragma once
#include <windows.h> 
#include "global.h"

using namespace DirectX;

class Graphic {
private:
	struct Loaded {
		int nrOfVertices = 0;
		bool textureLoaded = false;
	};

	struct Buffer {
		bool wireframe = false;
		bool texture = false;
		float padding1, padding2, padding3;
	};

	Loaded load;
	Buffer* cb;

	HWND wndHandle;
	IDXGISwapChain* swapChain;

	//clear pointers
	ID3D11ShaderResourceView* nullSRV[1] = { nullptr };
	ID3D11Buffer* nullBuff = nullptr;

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

	ID3D11Buffer* constantData;

	D3D11_VIEWPORT* vp;

	bool initialized;
	bool first;

	HRESULT createDirect3DContext();
	HRESULT createDepthAndStencilBuffer();
	HRESULT createRenderTarget();
	HRESULT createRasterizerState();
	HRESULT createSampling();
	HRESULT createShadersAndLayout();
	HRESULT createConstantBuffer();
	void createViewport();

	void setConstantBuffer();

public:
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;

	Graphic(HWND wndHandle);
	~Graphic();

	bool Ready();
	void Update();
	void Clear();
	void Process();
	void Finalize();

	void setVertexBuffer(ID3D11Buffer* buffer, UINT32 amount, UINT32 size, UINT32 offset);
	void setTextureResource(ID3D11ShaderResourceView* resource);
	
};
