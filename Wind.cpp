#include "elements\Wind.h"

Wind::Wind() {

}

Wind::Wind(Graphic* graphic, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr) : AbstractElement(graphic, posToSet, sizeToSet, harbor, texturePtr) {

}

Wind::~Wind() {
}
