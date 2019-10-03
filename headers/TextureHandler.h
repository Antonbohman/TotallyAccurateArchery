#pragma once
#include <string>
#include <DDSTextureLoader.h>
#include "Graphic.h"

struct TextureObj {
	std::wstring fileName = L"";
	ID3D11Resource* texture2D = nullptr;
	ID3D11ShaderResourceView* ShaderResourceView = nullptr;
};

class TextureHandler {
private:
	int maxTextures;
	TextureObj** textureBank;

public:
	TextureHandler();
	~TextureHandler();

	TextureObj* GetTexture(int index) const;
	HRESULT SetTexture(ID3D11Device* device, UINT index, const std::wstring _fileName);
	HRESULT ReleaseTexture(UINT index);
};

