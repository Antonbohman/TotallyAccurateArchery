#include "Graphic.h"

Graphic::Graphic(HWND _wndHandle) {
	wndHandle = _wndHandle;

	initialized = false;
	first = true;

	device = nullptr;
	deviceContext = nullptr;
	swapChain = nullptr;

	depthShaderResourceView = nullptr;
	depth = nullptr;

	backbufferRTV = nullptr;

	normalState = nullptr;
	wireframeState = nullptr;

	sampling = nullptr;

	vertexShader = nullptr;
	geometryShader = nullptr;
	pixelShader = nullptr;

	vertexLayout = nullptr;

	constantData = nullptr;

	cb = nullptr;
	vp = nullptr;

	createViewport();

	if (SUCCEEDED(createDirect3DContext()))
		if (SUCCEEDED(createDepthAndStencilBuffer()))
			if (SUCCEEDED(createRenderTarget()))
				if (SUCCEEDED(createRasterizerState()))
					if (SUCCEEDED(createSampling()))
						if (SUCCEEDED(createShadersAndLayout()))
							if (SUCCEEDED(createConstantBuffer()))
								initialized = true;
}

Graphic::~Graphic() {
	if (device) device->Release();
	if (deviceContext) deviceContext->Release();
	if (swapChain) swapChain->Release();

	if (depthShaderResourceView) depthShaderResourceView->Release();
	if (depth) depth->Release();

	if (backbufferRTV) backbufferRTV->Release();

	if (normalState) normalState->Release();
	if (wireframeState) wireframeState->Release();

	if (sampling) sampling->Release();

	if (vertexShader) vertexShader->Release();
	if (geometryShader) geometryShader->Release();
	if (pixelShader) pixelShader->Release();

	if (vertexLayout) vertexLayout->Release();

	if (constantData) constantData->Release();

	_aligned_free(cb);
	delete vp;
}

HRESULT Graphic::createDirect3DContext() {
	// create a struct to hold information about the swap chain
	DXGI_SWAP_CHAIN_DESC scd;

	// clear out the struct for use
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	// fill the swap chain description struct
	scd.BufferCount = 1;                                    // one back buffer
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
	scd.OutputWindow = wndHandle;                           // the window to be used
	scd.SampleDesc.Count = 1;                               // how many multisamples
	scd.Windowed = TRUE;                                    // windowed/full-screen mode

	// create a device, device context and swap chain using the information in the scd struct
	return D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		D3D11_CREATE_DEVICE_DEBUG,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&swapChain,
		&device,
		NULL,
		&deviceContext
	);
}

HRESULT Graphic::createDepthAndStencilBuffer() {
	//pointer to texture data in memory
	ID3D11Texture2D* depthTexture = nullptr;

	HRESULT hr = E_FAIL;

	//describe how the texture should be handled
	D3D11_TEXTURE2D_DESC depthDesc;
	depthDesc.ArraySize = 1;
	depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	depthDesc.CPUAccessFlags = 0;
	depthDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R32_TYPELESS;
	depthDesc.Height = W_HEIGHT;
	depthDesc.Width = W_WIDTH;
	depthDesc.MipLevels = 1;
	depthDesc.MiscFlags = 0;
	depthDesc.SampleDesc.Count = 1;
	depthDesc.SampleDesc.Quality = 0;
	depthDesc.Usage = D3D11_USAGE_DEFAULT;

	//load texture data into the texture object, 
	if (SUCCEEDED(device->CreateTexture2D(&depthDesc, NULL, &depthTexture))) {
		D3D11_SHADER_RESOURCE_VIEW_DESC ShaderResourceViewDesc;
		ZeroMemory(&ShaderResourceViewDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
		ShaderResourceViewDesc.Format = DXGI_FORMAT_R32_FLOAT;
		ShaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		ShaderResourceViewDesc.Texture2D.MipLevels = depthDesc.MipLevels;
		ShaderResourceViewDesc.Texture2D.MostDetailedMip = 0;

		if (SUCCEEDED(device->CreateShaderResourceView(depthTexture, &ShaderResourceViewDesc, &depthShaderResourceView))) {
			//describe how the resource should be rendered in view 
			D3D11_DEPTH_STENCIL_VIEW_DESC depthViewDesc;
			ZeroMemory(&depthViewDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
			depthViewDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D32_FLOAT;
			depthViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
			depthViewDesc.Flags = 0;

			//apply the view description on texture to our global variable
			if (SUCCEEDED(device->CreateDepthStencilView(depthTexture, &depthViewDesc, &depth))) {
				hr = S_OK;
			}
		}
	}
	
	if(depthTexture)
		depthTexture->Release();

	return hr;
}

HRESULT Graphic::createRenderTarget() {
	HRESULT hr = E_FAIL;

	// texture to hold render content
	ID3D11Texture2D* backBuffer = nullptr;

	// get the address of the back buffer
	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);

	// use the back buffer address to create the render target
	if (SUCCEEDED(device->CreateRenderTargetView(backBuffer, NULL, &backbufferRTV))) {
		hr = S_OK;
	}

	backBuffer->Release();

	return hr;
}

HRESULT Graphic::createRasterizerState() {
	HRESULT hr = E_FAIL;

	D3D11_RASTERIZER_DESC rastDesc;
	ZeroMemory(&rastDesc, sizeof(D3D11_RASTERIZER_DESC));

	rastDesc.FillMode = D3D11_FILL_WIREFRAME;
	rastDesc.CullMode = D3D11_CULL_NONE;
	rastDesc.FrontCounterClockwise = false;
	rastDesc.DepthBias = 0;
	rastDesc.DepthBiasClamp = 0.0f;
	rastDesc.SlopeScaledDepthBias = 0.0f;
	rastDesc.DepthClipEnable = true;
	rastDesc.ScissorEnable = false;
	rastDesc.MultisampleEnable = false;
	rastDesc.AntialiasedLineEnable = false;

	if (SUCCEEDED(device->CreateRasterizerState(&rastDesc, &wireframeState))) {
		rastDesc.FillMode = D3D11_FILL_SOLID;
		if (SUCCEEDED(device->CreateRasterizerState(&rastDesc, &normalState))) {
			hr = S_OK;
		}
	}

	return hr;
}

HRESULT Graphic::createSampling() {
	D3D11_SAMPLER_DESC samplingDesc;
	// Create a texture sampler state description.
	samplingDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	samplingDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplingDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplingDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplingDesc.MipLODBias = 0.0f;
	samplingDesc.MaxAnisotropy = 1;
	samplingDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplingDesc.BorderColor[0] = 0;
	samplingDesc.BorderColor[1] = 0;
	samplingDesc.BorderColor[2] = 0;
	samplingDesc.BorderColor[3] = 0;
	samplingDesc.MinLOD = 0;
	samplingDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// Create the texture sampler state.
	return device->CreateSamplerState(&samplingDesc, &sampling);
}

HRESULT Graphic::createShadersAndLayout() {
	ID3DBlob* errorBlob = nullptr;
	ID3DBlob* shader = nullptr;

	HRESULT hr = E_FAIL;

	D3D11_INPUT_ELEMENT_DESC inputDesc[] = {
		{
			"POSITION",					 // "semantic" name in shader
			0,							 // "semantic" index (not used)
			DXGI_FORMAT_R32G32B32_FLOAT, // size of ONE element (3 floats)
			0,							 // input slot
			0,							 // offset of first element
			D3D11_INPUT_PER_VERTEX_DATA, // specify data PER vertex
			0							 // used for INSTANCING (ignore)
		},
		{
			"COLOR",
			0,							 // same slot as previous (same vertexBuffer)
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,// offset of FIRST element (after POSITION)
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
		{
			"UV_POS",
			0,							// same slot as previous (same vertexBuffer)
			DXGI_FORMAT_R32G32_FLOAT,
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,// offset of FIRST element (after COLOR)
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
	};

	if (SUCCEEDED(D3DCompileFromFile(L"shaders/Vertex.hlsl", nullptr, nullptr, "VS_main", "vs_5_0", D3DCOMPILE_DEBUG, 0, &shader, &errorBlob))) {
		if (SUCCEEDED(device->CreateVertexShader(shader->GetBufferPointer(), shader->GetBufferSize(), nullptr, &vertexShader))) {
			if (SUCCEEDED(device->CreateInputLayout(inputDesc, ARRAYSIZE(inputDesc), shader->GetBufferPointer(), shader->GetBufferSize(), &vertexLayout))) {
				shader->Release();

				if (SUCCEEDED(D3DCompileFromFile(L"shaders/Geometry.hlsl", nullptr, nullptr, "GS_main", "gs_5_0", D3DCOMPILE_DEBUG, 0, &shader, &errorBlob))) {
					if (SUCCEEDED(device->CreateGeometryShader(shader->GetBufferPointer(), shader->GetBufferSize(), nullptr, &geometryShader))) {
						shader->Release();

						if (SUCCEEDED(D3DCompileFromFile(L"shaders/Fragment.hlsl", nullptr, nullptr, "PS_main", "ps_5_0", D3DCOMPILE_DEBUG, 0, &shader, &errorBlob))) {
							if (SUCCEEDED(device->CreatePixelShader(shader->GetBufferPointer(), shader->GetBufferSize(), nullptr, &pixelShader))) {
								hr = S_OK;
							}
						}
					}
				}
			}
		}
	}

	if (errorBlob) {
		OutputDebugStringA((char*)errorBlob->GetBufferPointer());
		errorBlob->Release();
	}

	if (shader)
		shader->Release();

	return hr;
}

HRESULT Graphic::createConstantBuffer() {
	//allocate space in memory aligned to a multitude of 16
	cb = (Buffer*)_aligned_malloc(sizeof(Buffer), 16);
	cb->texture = false;
	cb->wireframe = false;

	//create a description objekt defining how the buffer should be handled
	D3D11_BUFFER_DESC optDesc;
	ZeroMemory(&optDesc, sizeof(optDesc));
	optDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	optDesc.ByteWidth = sizeof(Buffer);
	optDesc.Usage = D3D11_USAGE_DYNAMIC;
	optDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	//bind data to subresource
	D3D11_SUBRESOURCE_DATA optData;
	ZeroMemory(&optData, sizeof(optData));
	optData.pSysMem = cb;
	optData.SysMemPitch = 0;
	optData.SysMemSlicePitch = 0;

	//create buffer
	return device->CreateBuffer(&optDesc, &optData, &constantData);
}

void Graphic::createViewport() {
	vp = new D3D11_VIEWPORT;
	vp->Width = (float)W_WIDTH;
	vp->Height = (float)W_HEIGHT;
	vp->MinDepth = 0.0f;
	vp->MaxDepth = 1.0f;
	vp->TopLeftX = 0;
	vp->TopLeftY = 0;
}

bool Graphic::Ready() {
	return initialized;
}

void Graphic::Update() {
	if (!initialized) return;

	if (first) {
		deviceContext->RSSetViewports(1, vp);
		
		//set shaders
		deviceContext->OMSetRenderTargets(1, &backbufferRTV, depth);

		deviceContext->VSSetShader(vertexShader, nullptr, 0);
		deviceContext->HSSetShader(nullptr, nullptr, 0);
		deviceContext->DSSetShader(nullptr, nullptr, 0);
		deviceContext->GSSetShader(nullptr, nullptr, 0);
		deviceContext->PSSetShader(pixelShader, nullptr, 0);
		deviceContext->CSSetShader(nullptr, nullptr, 0);

		// specify the topology to use when drawing
		deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// specify the IA Layout (how is data passed)
		deviceContext->IASetInputLayout(vertexLayout);

		first = false;
	}

	if (renderOpt & RENDER_WIREFRAME) {
		deviceContext->RSSetState(wireframeState);
	} else {
		deviceContext->RSSetState(normalState);
	}
}

void Graphic::Clear() {
	if (!initialized) return;

	// clear the back buffer to a black
	float clearColor[] = { 0.0f, 0.0f, 0.0f, 0.0f };

	deviceContext->ClearRenderTargetView(backbufferRTV, clearColor);

	// make sure our depth buffer is cleared to black each time we render
	deviceContext->ClearDepthStencilView(depth, D3D11_CLEAR_DEPTH, 1.0f, 0);

	if (renderOpt & RENDER_WIREFRAME)
		cb->wireframe = true;
}

void Graphic::Process() {
	if (!initialized) return;

	deviceContext->PSSetSamplers(0, 1, &sampling);

	if(load.textureLoaded)
		cb->texture = true;

	setConstantBuffer();

	deviceContext->PSSetConstantBuffers(0, 1, &constantData);

	deviceContext->Draw(load.nrOfVertices, 0);

	//clear loaded parameters and load object
	load.nrOfVertices = 0;
	load.textureLoaded = false;

	cb->texture = false;
	cb->wireframe = false;

	deviceContext->PSSetShaderResources(0, 1, &nullSRV[0]);
	deviceContext->PSSetConstantBuffers(0, 1, &nullBuff);
}

void Graphic::Finalize() {
	if (!initialized) return;
	
	swapChain->Present(0, 0);
}

void Graphic::setConstantBuffer() {
	//create a subresource to hold our data while we copy between cpu and gpu memory
	D3D11_MAPPED_SUBRESOURCE mappedMemory;

	//copy and map our cpu memory to our gpu buffert
	deviceContext->Map(constantData, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedMemory);
	memcpy(mappedMemory.pData, &cb, sizeof(Buffer));
	deviceContext->Unmap(constantData, 0);
}

void Graphic::setVertexBuffer(ID3D11Buffer* buffer, UINT32 amount, UINT32 size, UINT32 offset) {
	// specify which vertex buffer to use next.
	load.nrOfVertices = amount;
	deviceContext->IASetVertexBuffers(0, 1, &buffer, &size, &offset);
}

void Graphic::setTextureResource(ID3D11ShaderResourceView* resource) {
	deviceContext->PSSetShaderResources(0, 1, &resource);
	load.textureLoaded = true;
}