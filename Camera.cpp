#include "elements/Camera.h"

Camera::Camera() : AbstractElement() {
	focus = nullptr;
}

Camera::Camera(Graphic* _graphic, XMFLOAT3 posToSet) : AbstractElement(_graphic, posToSet, { 0.0f, 0.0f }, BottomLeft, nullptr) {
	focus = nullptr;
}

Camera::~Camera() {

}

void Camera::setFocus(PhysicalElement* target) {
	focus = target;
}

void Camera::clearFocus() {
	focus = nullptr;
}

void Camera::updateFocus() {
	if (focus) {
		XMFLOAT2 focusPos = focus->getWorldPos();

		viewPosition.x = focusPos.x - (W_WIDTH / 2);
		viewPosition.y = focusPos.y - (W_HEIGHT / 2);
	}	
}

void Camera::setPos(XMFLOAT2 newPos) {
	viewPosition.x = newPos.x - (W_WIDTH / 2);
	viewPosition.y = newPos.y - (W_HEIGHT / 2);
}

XMFLOAT2 Camera::getPos() {
	return XMFLOAT2(viewPosition.x, viewPosition.y);
}