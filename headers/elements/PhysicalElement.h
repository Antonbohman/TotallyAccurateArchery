#pragma once
#include "elements/BaseElement.h"
#include "elements/Camera.h"

class Camera;

class PhysicalElement : public BaseElement {
protected:
	Camera * camera;

	Vector3 worldPosition;

	void setAsCameraFocus();

	double convertPixelToMeter(const float* pixels);
	float convertMeterToPixel(const double* meters); 
	void getQuadBoundriesWorld(float* pos_X0, float* pos_X1, float* pos_Y0, float* pos_Y1);

public:
	PhysicalElement();
	PhysicalElement(Graphic* _graphic, Camera* _camera, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr);
	virtual ~PhysicalElement();

	XMFLOAT2 getWorldPos();
	virtual void moveWorldToView();
	bool isColliding(PhysicalElement* otherObject);

	virtual void updateElement();
};

