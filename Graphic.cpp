#include "Graphic.h"

Graphic::Graphic(HWND _wndHandle) {
	wndHandle = _wndHandle;
}

Graphic::~Graphic() {

}

void Graphic::Update() {

}

void Graphic::Process() {

}

/*
void CreateDeferredQuad() {
	PositionVertex triangleVertices[6] =
	{
		-1, -1,	//v0 pos
		-1, 1,	//v1 pos
		1, -1,    //v2 pos

				  //----//

				  1, 1, 	//v3 pos
				  1, -1,	//v4 pos
				  -1, 1,    //v5 pos
	};

	// Describe the Vertex Buffer
	D3D11_BUFFER_DESC bufferDesc;
	memset(&bufferDesc, 0, sizeof(bufferDesc));
	// what type of buffer will this be?
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	// what type of usage (press F1, read the docs)
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	// how big in bytes each element in the buffer is.
	bufferDesc.ByteWidth = sizeof(PositionVertex) * 6;

	// this struct is created just to set a pointer to the
	// data containing the vertices.
	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = triangleVertices;

	// create a Vertex Buffer
	gDevice->CreateBuffer(&bufferDesc, &data, &gDeferredQuadBuffer);
}

HRESULT CreateSampling() {
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
	return gDevice->CreateSamplerState(&samplingDesc, &gSampling);
}

void createBlendState() {
	D3D11_BLEND_DESC blendStateDesc;
	ZeroMemory(&blendStateDesc, sizeof(D3D11_BLEND_DESC));
	blendStateDesc.AlphaToCoverageEnable = false;
	blendStateDesc.IndependentBlendEnable = false;
	blendStateDesc.RenderTarget[0].BlendEnable = TRUE;
	blendStateDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	blendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blendStateDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	blendStateDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_MAX;
	blendStateDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendStateDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendStateDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	HRESULT res = gDevice->CreateBlendState(&blendStateDesc, &gBlendStateLight);
}

void createViewport() {
	vp = new D3D11_VIEWPORT;
	vp->Width = (float)W_WIDTH;
	vp->Height = (float)W_HEIGHT;
	vp->MinDepth = 0.0f;
	vp->MaxDepth = 1.0f;
	vp->TopLeftX = 0;
	vp->TopLeftY = 0;
}

void SetViewport(bool forceSingle) {
	if (renderOpt & RENDER_MULTI_VIEWPORT && !forceSingle) {
		gDeviceContext->RSSetViewports(4, svp);
	} else {
		gDeviceContext->RSSetViewports(1, vp);
	}
}

void RenderBuffers(int *RenderCopies, int amount, bool *drawAllCopies) {
	// clear the back buffer to a deep blue
	//float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float clearColor[] = { 0.45f, 0.95f, 1.0f, 1.0f };
	//float clearColor[] = { 0.3f, 0.3f, 0.3f, 0.0f };

	updateCameraValues();
	setCameraViewProjectionSpace();

	// Clear the render target buffers.
	for (int i = 0; i < G_BUFFER; i++) {
		gDeviceContext->ClearRenderTargetView(gRenderTargetViewArray[i], clearColor);
	}

	float blurClear[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	gDeviceContext->ClearRenderTargetView(gRenderTargetViewArray[4], blurClear);

	// make sure our depth buffer is cleared to black each time we render
	gDeviceContext->ClearDepthStencilView(gDepth, D3D11_CLEAR_DEPTH, 1.0f, 0);

	// Set the sampler state in the pixel shader.
	gDeviceContext->PSSetSamplers(0, 1, &gSampling);

	//bind our constant buffers to coresponding shader
	gDeviceContext->VSSetConstantBuffers(0, 1, &gWorldMatrixBuffer);
	gDeviceContext->GSSetConstantBuffers(0, 1, &gRenderingOptionsBuffer);
	gDeviceContext->GSSetConstantBuffers(1, 1, &gCameraMatrixBuffer);
	gDeviceContext->PSSetConstantBuffers(0, 1, &gAmbientSpecularBuffer);

	//Set heightmap shader options
	SetBlendShaders();

	//load map textures
	for (int i = 0; i < 4; i++) {
		gDeviceContext->PSSetShaderResources(i, 1, &gMapTexturesSRV[i]);
	}

	//set world space for height map and update wvp matrix
	//set specular for height map
	setWorldSpace({ 0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f });
	updateCameraWorldViewProjection();
	updateSpecularValues(XMVectorSet(1, 1, 1, 1), XMVectorSet(1, 1, 1, 0.01), XMVectorSet(0.1, 0.1, 0.1, 0.00000010f));

	//Render heightmap
	setVertexBuffer(heightmapBuffer, sizeof(TriangleVertex), 0);
	gDeviceContext->Draw(nrOfHMVert, 0);

	//Release
	for (int i = 0; i < 4; i++) {
		gDeviceContext->PSSetShaderResources(i, 1, &nullSRV[0]);
	}

	//Set object shader options
	SetDeferredShaders();

	WorldSpace copy = { 0.0f, 0.0f, 0.0f, 0.0f, 40.0f, 10.0f, 3.0f, 3.0f, 3.0f };

	//Render objects!
	for (int i = 0; i < nrOfVertexBuffers; i++) {
		//set object texture
		gDeviceContext->PSSetShaderResources(0, 1, &gTextureSRV[i]);

		//set world space for object and update wvp matrix
		//set specular for object
		setWorldSpace(worldObjects[i]);
		updateCameraWorldViewProjection();
		updateSpecularValues(XMVectorSet(gReflection[i].a_r, gReflection[i].a_g, gReflection[i].a_b, 1), XMVectorSet(gReflection[i].d_r, gReflection[i].d_g, gReflection[i].d_b, 1), XMVectorSet(gReflection[i].s_r, gReflection[i].s_g, gReflection[i].s_b, gReflection[i].s_p * 100));

		//Render objects
		setVertexBuffer(ppVertexBuffers[i], sizeof(TriangleVertex), 0);

		gDeviceContext->Draw(gnrOfVert[i], 0);

		if (!i) {
			//Set copy
			setWorldSpace(copy);
			updateCameraWorldViewProjection();

			//Render objects
			gDeviceContext->Draw(gnrOfVert[i], 0);
		}
	}

	//Release
	//for (int i = 0; i < nrOfVertexBuffers; i++)
	//{
	gDeviceContext->PSSetShaderResources(0, 1, &nullSRV[0]);
	//}

	gDeviceContext->VSSetConstantBuffers(0, 1, &nullCB);
	gDeviceContext->GSSetConstantBuffers(0, 1, &nullCB);
	gDeviceContext->GSSetConstantBuffers(1, 1, &nullCB);
	gDeviceContext->PSSetConstantBuffers(0, 1, &nullCB);


	//Compute Gaussian Filter

	if (blurFilter == true) {
		SetComputeShaders();

		gDeviceContext->CSSetShaderResources(0, 1, &gShaderResourceViewArray[4]);
		gDeviceContext->CSSetUnorderedAccessViews(0, 1, &blurUAV, 0);

		gDeviceContext->Dispatch(45, 45, 1);

		//Release

		gDeviceContext->CSSetShaderResources(0, 1, &nullSRV[0]);
		gDeviceContext->CSSetUnorderedAccessViews(0, 1, &nullUAV, 0);

		//Copy resources
		gDeviceContext->CopyResource(gBlurTextureRead, gBlurTextureDraw);
	} else {
		gDeviceContext->CopyResource(gBlurTextureRead, gBlurTextureEmpty);
	}
}



HRESULT CreateDepthBuffer(ID3D11Texture2D** pDepthTexture) {
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
	//for now it's a blank texture to be used later as depth buffer
	HRESULT hr = gDevice->CreateTexture2D(&depthDesc, NULL, pDepthTexture);
	if (FAILED(hr)) {
		return S_FALSE;
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC ShaderResourceViewDesc;
	ZeroMemory(&ShaderResourceViewDesc, sizeof(ShaderResourceViewDesc));
	ShaderResourceViewDesc.Format = DXGI_FORMAT_R32_FLOAT;
	ShaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	ShaderResourceViewDesc.Texture2D.MipLevels = depthDesc.MipLevels;
	ShaderResourceViewDesc.Texture2D.MostDetailedMip = 0;

	hr = gDevice->CreateShaderResourceView(*pDepthTexture, &ShaderResourceViewDesc, &gDepthShaderResourceView);
	if (FAILED(hr)) {
		return S_FALSE;
	}

	return S_OK;
}

HRESULT CreateDepthStencilView(ID3D11Texture2D** pDepthTexture) {
	//describe how the resource should be rendered in view 
	D3D11_DEPTH_STENCIL_VIEW_DESC depthViewDesc;
	ZeroMemory(&depthViewDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	depthViewDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D32_FLOAT;
	depthViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthViewDesc.Flags = 0;

	//apply the view description on texture to our global variable
	return gDevice->CreateDepthStencilView(*pDepthTexture, &depthViewDesc, &gDepth);
}

HRESULT CreateRenderTargets() {
	// get the address of the back buffer
	ID3D11Texture2D* pBackBuffer = nullptr;
	gSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	// use the back buffer address to create the render target
	gDevice->CreateRenderTargetView(pBackBuffer, NULL, &gBackbufferRTV);

	pBackBuffer->Release();

	for (int i = 0; i < G_BUFFER; i++) {
		gRenderTargetTextureArray[i] = nullptr;
		gRenderTargetViewArray[i] = nullptr;
		gShaderResourceViewArray[i] = nullptr;
	}

	D3D11_TEXTURE2D_DESC textureDesc;
	D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;

	// Initialize the render target texture description.
	ZeroMemory(&textureDesc, sizeof(textureDesc));

	// Setup the render target texture description.
	textureDesc.Width = W_WIDTH;
	textureDesc.Height = W_HEIGHT;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	// Create the render target textures.
	for (int i = 0; i < G_BUFFER; i++) {
		if (FAILED(gDevice->CreateTexture2D(&textureDesc, NULL, &gRenderTargetTextureArray[i]))) {
			return S_FALSE;
		}
	}

	ZeroMemory(&renderTargetViewDesc, sizeof(renderTargetViewDesc));

	// Setup the description of the render target view.
	renderTargetViewDesc.Format = textureDesc.Format;
	renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	renderTargetViewDesc.Texture2D.MipSlice = 0;

	// Create the render target views.
	for (int j = 0; j < G_BUFFER; j++) {
		if (FAILED(gDevice->CreateRenderTargetView(gRenderTargetTextureArray[j], &renderTargetViewDesc, &gRenderTargetViewArray[j]))) {
			return S_FALSE;
		}
	}

	ZeroMemory(&shaderResourceViewDesc, sizeof(shaderResourceViewDesc));

	// Setup the description of the shader resource view.
	shaderResourceViewDesc.Format = textureDesc.Format;
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;

	// Create the shader resource views.
	for (int k = 0; k < G_BUFFER; k++) {
		if (FAILED(gDevice->CreateShaderResourceView(gRenderTargetTextureArray[k], &shaderResourceViewDesc, &gShaderResourceViewArray[k]))) {
			return S_FALSE;
		}
	}

	//Blur

	//Texture to draw on
	textureDesc.BindFlags = D3D11_BIND_UNORDERED_ACCESS;
	gDevice->CreateTexture2D(&textureDesc, NULL, &gBlurTextureDraw);

	//Unordered access view to write on
	D3D11_UNORDERED_ACCESS_VIEW_DESC blurUAVdesc;
	blurUAVdesc.Texture2D.MipSlice = 0;
	blurUAVdesc.Format = textureDesc.Format;
	blurUAVdesc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;

	HRESULT error = gDevice->CreateUnorderedAccessView(gBlurTextureDraw, &blurUAVdesc, &blurUAV);
	if (error != S_OK) {
		return DXGI_ERROR_ACCESS_DENIED;
	}

	//Texture to read from
	textureDesc.Usage = D3D11_USAGE_DYNAMIC;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	gDevice->CreateTexture2D(&textureDesc, 0, &gBlurTextureRead);

	error = gDevice->CreateShaderResourceView(gBlurTextureRead, &shaderResourceViewDesc, &gBlurShaderResource);
	if (error != S_OK) {
		return DXGI_ERROR_ACCESS_DENIED;
	}

	gDevice->CreateTexture2D(&textureDesc, NULL, &gBlurTextureEmpty);

	return S_OK;
}

HRESULT CreateDirect3DContext(HWND wndHandle) {
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
	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		D3D11_CREATE_DEVICE_DEBUG,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&gSwapChain,
		&gDevice,
		NULL,
		&gDeviceContext
	);

	if (SUCCEEDED(hr)) {
		//pointer to texture data in memory
		ID3D11Texture2D* pDepthTexture = nullptr;

		hr = CreateDepthBuffer(&pDepthTexture);

		if (SUCCEEDED(hr)) {
			hr = CreateDepthStencilView(&pDepthTexture);

			if (SUCCEEDED(hr)) {
				CreateRenderTargets();
			}
		}

		pDepthTexture->Release();

		hr = SetRasterizerState();
	}

	return hr;
}

HRESULT SetRasterizerState() {
	HRESULT hr;

	if (renderOpt & RENDER_WIREFRAME) {
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

		ID3D11RasterizerState* gRasterizerState;

		hr = gDevice->CreateRasterizerState(
			&rastDesc,
			&gRasterizerState
		);

		gDeviceContext->RSSetState(gRasterizerState);
	} else {
		D3D11_RASTERIZER_DESC rastDesc;
		ZeroMemory(&rastDesc, sizeof(D3D11_RASTERIZER_DESC));

		rastDesc.FillMode = D3D11_FILL_SOLID;
		rastDesc.CullMode = D3D11_CULL_NONE;
		rastDesc.FrontCounterClockwise = false;
		rastDesc.DepthBias = 0;
		rastDesc.DepthBiasClamp = 0.0f;
		rastDesc.SlopeScaledDepthBias = 0.0f;
		rastDesc.DepthClipEnable = true;
		rastDesc.ScissorEnable = false;
		rastDesc.MultisampleEnable = false;
		rastDesc.AntialiasedLineEnable = false;

		ID3D11RasterizerState* gRasterizerState;

		hr = gDevice->CreateRasterizerState(
			&rastDesc,
			&gRasterizerState
		);

		gDeviceContext->RSSetState(gRasterizerState);
	}

	return hr;
}*/