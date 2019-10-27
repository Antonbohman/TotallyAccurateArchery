/*
* texturehandler.h/texturehandler.cpp
* Creates texture objects and holds references to each one
* to be accessible and reusable for elements in program.
*
* Written and all rights reserved by: Filip Unger & Anton Bohman
*/

#include "TextureHandler.h"

TextureHandler::TextureHandler() {
	maxTextures = 30;
	textureBank = new TextureObj*[maxTextures];

	for (int i = 0; i < maxTextures; i++) {
		textureBank[i] = nullptr;
	}
}

TextureHandler::~TextureHandler() {
	for (int i = 0; i < maxTextures; i++) {
		if (textureBank[i]) {
			textureBank[i]->texture2D->Release();
			textureBank[i]->ShaderResourceView->Release();
			delete textureBank[i];
		}
	}

	delete[] textureBank;
}

TextureObj* TextureHandler::GetTexture(int index) const {
	if (index < maxTextures)
		return textureBank[index];
	return nullptr;
}

HRESULT TextureHandler::SetTexture(ID3D11Device* device, UINT index, const std::wstring _fileName) {
	if (textureBank[index]) {
		return E_FAIL;
	}

	textureBank[index] = new TextureObj;
	textureBank[index]->fileName = _fileName;

	return CreateDDSTextureFromFile(
		device,
		textureBank[index]->fileName.c_str(),
		&textureBank[index]->texture2D,
		&textureBank[index]->ShaderResourceView
	);
}

HRESULT TextureHandler::ReleaseTexture(UINT index) {
	HRESULT hr = E_FAIL;

	if (textureBank[index]) {
		textureBank[index]->texture2D->Release();
		textureBank[index]->ShaderResourceView->Release();
		delete textureBank[index];

		textureBank[index] = nullptr;

		hr = S_OK;
	}

	return hr;
}
