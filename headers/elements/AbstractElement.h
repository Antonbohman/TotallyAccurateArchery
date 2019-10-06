#pragma once
#include "elements/BaseElement.h"

class AbstractElement : public BaseElement {
public:
	AbstractElement();
	AbstractElement(Graphic* _graphic, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr);
	virtual ~AbstractElement();

	virtual void updateElement();
};

