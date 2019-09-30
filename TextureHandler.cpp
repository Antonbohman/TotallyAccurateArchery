#include "TextureHandler.h"

TextureHandler::TextureHandler() {
	maxTextures = 30;
	nrOfTextures = 0;
	textureBank = new TextureObj*[nrOfTextures];
}

TextureHandler::~TextureHandler() {
	for (int i = 0; i < nrOfTextures; i++) {
		if (textureBank[i]) {
			textureBank[i]->texture2D->Release();
			textureBank[i]->ShaderResourceView->Release();
			delete textureBank[i];
		}
	}

	delete[] textureBank;
}

const TextureObj* TextureHandler::GetTexture(int index) const {
	if (index < nrOfTextures)
		return textureBank[index];
	return nullptr;
}

int TextureHandler::SetTexture(ID3D11Device* device, const std::wstring _fileName) {
	textureBank[nrOfTextures] = new TextureObj;
	textureBank[nrOfTextures]->fileName = _fileName;

	CreateDDSTextureFromFile(
		device, 
		textureBank[nrOfTextures]->fileName.c_str(),
		&textureBank[nrOfTextures]->texture2D,
		&textureBank[nrOfTextures]->ShaderResourceView
	);

	nrOfTextures++;
	
	return nrOfTextures - 1;
}
