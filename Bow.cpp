#include "elements\Bow.h"

Bow::Bow() : PhysicalElement() {
}

Bow::Bow(Graphic* _graphic, Camera* _camera, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr) : PhysicalElement(_graphic, _camera, posToSet, sizeToSet, harbor, texturePtr) {

}

Bow::~Bow() {

}
