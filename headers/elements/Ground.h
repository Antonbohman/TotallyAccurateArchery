#pragma once
#include "elements/PhysicalElement.h"

enum GravityType {
	Earth,
	Lunar,
	Mars,
	Sun,
	NoGravity
};

class Ground : public PhysicalElement {
private:
	class Layer : public AbstractElement {
	private:
		float yStart;
	public:
		Layer() : AbstractElement() { yStart = 0; };
		Layer(Graphic* graphic, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, ID3D11ShaderResourceView* texturePtr, float vStart) : AbstractElement(graphic, posToSet, sizeToSet, TopLeft, texturePtr) {
			yStart = posToSet.y;
			uv.Y0 = vStart;
		};
		~Layer() {};

		void updateElement(float position, float offset) {
			viewPosition.x = position;
			viewPosition.y = yStart - offset;
		};
	};

	Layer* back[3];
	Layer* front[3];

	float gravity;

public:
	Ground();
	Ground(Graphic* _graphic, Camera* _camera, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr);
	~Ground();

	void moveWorldToView();
	void renderElement();

	void setGravity(UINT gravityType);
	float getGravity();
};
