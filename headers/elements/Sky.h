#pragma once
#include "elements\AbstractElement.h"

class Sky : public AbstractElement {
private:

public:
	Sky();
	Sky(Graphic* _graphic, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr);
	~Sky();
};

