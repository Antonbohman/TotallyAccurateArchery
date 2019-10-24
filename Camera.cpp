#include "elements/Camera.h"

Camera::Camera() : AbstractElement() {
	focus = nullptr;
	focusPos = { 0.0f, 0.0f };
	acceleration = 0;
	maxVelocity = 0;
	velocity = 0;
}

Camera::Camera(Graphic* _graphic, XMFLOAT3 posToSet) : AbstractElement(_graphic, posToSet, { 0.0f, 0.0f }, BottomLeft, nullptr) {
	focus = nullptr;
	focusPos = { 0.0f, 0.0f };
	acceleration = 0;
	maxVelocity = 0;
	velocity = 0;
}

Camera::~Camera() {

}

void Camera::setFocus(PhysicalElement* target) {
	velocity = 0;
	focus = target;
	focusPos = { 0.0f, 0.0f };
}

void Camera::setFocus(XMFLOAT2 newPos) {
	velocity = 0;
	focus = nullptr;

	focusPos.x = newPos.x - (W_WIDTH / 2);
	focusPos.y = newPos.y - (W_HEIGHT / 2);
}

void Camera::clearFocus() {
	velocity = 0;
	focus = nullptr;
	focusPos = { 0.0f, 0.0f };
}

void Camera::updateFocus(double delta) {
	if (delay > 0) {
		delay -= delta;
		delta = -delay;
	}

	if (delta > 0) {
		if (focus) {
			focusPos = focus->getWorldPos();

			focusPos.x = focusPos.x - (W_WIDTH / 2);
			focusPos.y = focusPos.y - (W_HEIGHT / 2);
		}

		if (maxVelocity == 0 || acceleration == 0) {
			viewPosition.x = focusPos.x;
			viewPosition.y = focusPos.y;

		} else {
			Vector2 currentPos(viewPosition.x, viewPosition.y);
			Vector2 targetPos(focusPos.x, focusPos.y);

			Vector2 direction = (targetPos - currentPos);
			float remainingDistance = direction.Length();

			if (remainingDistance != 0) {
				if (velocity >= maxVelocity || velocity + acceleration >= maxVelocity)
					velocity = maxVelocity;
				else
					velocity += acceleration * delta;

				direction.Normalize();

				if (velocity > remainingDistance)
					velocity = remainingDistance;

				direction *= velocity;

				viewPosition.x += direction.x;
				viewPosition.y += direction.y;
			}
		}
	}
}

XMFLOAT2 Camera::getOffset() {
	return XMFLOAT2(viewPosition.x, viewPosition.y);
}

XMFLOAT2 Camera::getOffsetMeter() {
	return XMFLOAT2(convertPixelToMeter(&viewPosition.x), convertPixelToMeter(&viewPosition.y));
}

XMFLOAT2 Camera::getPos() {
	return XMFLOAT2(viewPosition.x + (W_WIDTH / 2), viewPosition.y + (W_HEIGHT / 2));
}

void Camera::setAnimation(float _acceleration, float _maxVelocity) {
	acceleration = _acceleration;
	maxVelocity = _maxVelocity;
}

void Camera::clearAnimation() {
	acceleration = 0;
	maxVelocity = 0;
}

void Camera::setDelay(double _delay) {
	delay = _delay;
}
