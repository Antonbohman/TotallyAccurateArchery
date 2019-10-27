/*
* abstractelement.h/abstractelement.cpp
* Child class of base element, add some functionality towards elements that are always static
* towards the camera and has no real involvment in the physical game world.
* Basicly none, but to mainly distinguise between physical and abstract elements that does not need
* more then necesary functionality.
*
* Written and all rights reserved by: Filip Unger & Anton Bohman
*/

#pragma once
#include "elements/BaseElement.h"

class AbstractElement : public BaseElement {
public:
	AbstractElement();
	AbstractElement(Graphic* _graphic, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr);
	virtual ~AbstractElement();

	virtual void updateElement();
};

