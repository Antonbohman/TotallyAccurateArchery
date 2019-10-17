#include "elements/Ground.h"

Ground::Ground() : PhysicalElement() {
	back[0] = nullptr;
	back[1] = nullptr;
	back[2] = nullptr;
	front[0] = nullptr;
	front[1] = nullptr;
	front[2] = nullptr;
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

	back[0] = new Layer(_graphic, { xLeft, newTopY, 0.80f }, { W_WIDTH, newSizeY }, texturePtr, 0.0f);
	back[1] = new Layer(_graphic, { xLeft - W_WIDTH, newTopY, 0.80f }, { W_WIDTH, newSizeY }, texturePtr, 0.0f);
	back[2] = new Layer(_graphic, { xLeft + W_WIDTH, newTopY, 0.80f }, { W_WIDTH, newSizeY }, texturePtr, 0.0f);

	front[0] = new Layer(_graphic, { xLeft, yTop, 0.50f }, { W_WIDTH, sizeToSet.y }, texturePtr, 0.1f);
	front[1] = new Layer(_graphic, { xLeft - W_WIDTH, yTop, 0.50f }, { W_WIDTH, sizeToSet.y }, texturePtr, 0.1f);
	front[2] = new Layer(_graphic, { xLeft + W_WIDTH, yTop, 0.50f }, { W_WIDTH, sizeToSet.y }, texturePtr, 0.1f);
}

Ground::~Ground() {
	delete back[0];
	delete back[1];
	delete back[2];
	delete front[0];
	delete front[1];
	delete front[2];
}

void Ground::moveWorldToView() {
	XMFLOAT2 camPos = camera->getOffset();

	float offsetY = camPos.y;
	float offsetX = -fmod(camPos.x, W_WIDTH);

	back[0]->updateElement(offsetX, offsetY);
	back[1]->updateElement(offsetX - W_WIDTH, offsetY);
	back[2]->updateElement(offsetX + W_WIDTH, offsetY);

	front[0]->updateElement(offsetX, offsetY);
	front[1]->updateElement(offsetX - W_WIDTH, offsetY);
	front[2]->updateElement(offsetX + W_WIDTH, offsetY);
}

void Ground::renderElement() {
	back[0]->renderElement();
	back[1]->renderElement();
	back[2]->renderElement();
	front[0]->renderElement();
	front[1]->renderElement();
	front[2]->renderElement();
}