#pragma once
#include "elements\PhysicalElement.h"

enum BowType {
	Flight,
	Hybrid,
	War,
	Targetbow

};

class Bow : public PhysicalElement {
private:
	int rotationDirection = -1;

	Vector3 direction;
	float efficiencyFactor; //"e"
	float mass;
	float drawDistance; //"x"
	float drawTime;
	float maxDrawTime;
	float drawForce; //"F"
	float scalingFactor; //"k"

	float constA, constB;

public:
	Bow();
	Bow(Graphic* _graphic, Camera* _camera, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr, Vector3 _direction);
	~Bow();

	void setBowType(UINT bowType);

	void drawArrow(double delta);
	bool arrowReady();
	Vector3 fireArrow(float arrowMass);

	float currentDrawForce();

	void updateElement(MouseInfo mouse);
};

