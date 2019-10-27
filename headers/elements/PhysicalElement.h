/*
* physicalelement.h/physicalelement.cpp
* Child class of base element, add some functionality towards elements that are physical towards the game world.
* Adds functionality for objects that need a world position and might need to collide with other objects in the world.
*
* Written and all rights reserved by: Filip Unger & Anton Bohman
*/

#pragma once
#include "elements/BaseElement.h"
#include "elements/Camera.h"

class Camera;

class PhysicalElement : public BaseElement {
protected:
	Camera * camera;
	Vector3 worldPosition;

	void setAsCameraFocus();
	void getQuadBoundriesWorld(float* pos_X0, float* pos_X1, float* pos_Y0, float* pos_Y1);

public:
	PhysicalElement();
	PhysicalElement(Graphic* _graphic, Camera* _camera, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr);
	virtual ~PhysicalElement();

	void setWorldPos(float x, float y);
	XMFLOAT2 getWorldPos();
	virtual void moveWorldToView();
	virtual bool isColliding(PhysicalElement* otherObject);

	virtual void updateElement();
};

