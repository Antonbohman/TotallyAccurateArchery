#include "elements/Ground.h"

Ground::Ground() : PhysicalElement() {
	back = nullptr;
	front = nullptr;
}

Ground::Ground(Graphic* _graphic, Camera* _camera, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr) : PhysicalElement(_graphic, _camera, posToSet, sizeToSet, harbor, nullptr) {
	float xLeft = 0;
	float yTop = 0;

	switch (anchor) {
	case Middle:
		xLeft = posToSet.x - (sizeToSet.x / 2);
		yTop = posToSet.y + (sizeToSet.y / 2);
		break;
	case TopLeft:
		xLeft = posToSet.x;
		yTop = posToSet.y;
		break;
	case TopRight:
		xLeft = posToSet.x - sizeToSet.x;
		yTop = posToSet.y;
		break;
	case BottomLeft:
		xLeft = posToSet.x;
		yTop = posToSet.y + sizeToSet.y;
		break;
	case BottomRight:
		xLeft = posToSet.x - sizeToSet.x;
		yTop = posToSet.y + sizeToSet.y;
		break;
	}

	float newSizeY = (sizeToSet.y / 0.9f);
	float newTopY = yTop + (newSizeY - sizeToSet.y);

	back = new Layer(_graphic, { xLeft, newTopY, 0.80f }, { W_WIDTH, newSizeY }, texturePtr, 0.0f);
	front = new Layer(_graphic, { xLeft, yTop, 0.60f }, { W_WIDTH, sizeToSet.y }, texturePtr, 0.1f);
}

Ground::~Ground() {
	delete back;
	delete front;
}

void Ground::moveWorldToView() {
	float offset = camera->getOffset().y;

	back->moveLayerInAxisY(offset);
	front->moveLayerInAxisY(offset);
}

void Ground::renderElement() {
	back->renderElement();
	front->renderElement();
}