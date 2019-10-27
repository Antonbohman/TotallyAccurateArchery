/*
* human.h/human.cpp
* A physical element class for drawing our archer element
*
* Written and all rights reserved by: Filip Unger & Anton Bohman
*/

#include "elements\Human.h"

Human::Human() : PhysicalElement() {

}

Human::Human(Graphic* _graphic, Camera* _camera, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr) : PhysicalElement(_graphic, _camera, posToSet, sizeToSet, harbor, texturePtr) {

}

Human::~Human() {

}
