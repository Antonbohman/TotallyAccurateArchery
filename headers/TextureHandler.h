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
	int nrOfTextures;
	TextureObj** textureBank;

public:
	TextureHandler();
	~TextureHandler();

	const TextureObj* GetTexture(int index) const;
	int SetTexture(ID3D11Device* device, const std::wstring _fileName);
};

