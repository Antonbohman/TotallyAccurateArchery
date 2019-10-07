#pragma once
#include "elements/BaseElement.h"
#include "elements/Camera.h"

class Camera;

class PhysicalElement : public BaseElement {
private:
	Camera* camera;

protected:
	XMFLOAT3 worldPosition;

	void setAsCameraFocus();

public:
	PhysicalElement();
	PhysicalElement(Graphic* _graphic, Camera* _camera, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr);
	virtual ~PhysicalElement();

	XMFLOAT2 getWorldPos();
	void moveWorldToView();
	bool isColliding(PhysicalElement otherObject);

	virtual void updateElement();
};

