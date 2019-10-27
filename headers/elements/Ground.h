/*
* ground.h/ground.cpp
* A physical element class for drawing our ground element
* the ground consist of several layers that move in unison to
* create the feeling of continously movement, it also has a seperate hitbox
* and two layer arrows can fall between to simulate arrows getting stuck in ground
* it also stores different key values for different kinds of planets and ground types
*
* Written and all rights reserved by: Filip Unger & Anton Bohman
*/

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
	float fluidDensity;

public:
	Ground();
	Ground(Graphic* _graphic, Camera* _camera, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr);
	~Ground();

	void moveWorldToView();
	void renderElement();

	void setColour(XMFLOAT4 newColour);

	void setGravity(UINT gravityType);
	void setDensity(float newDensity);
	float getGravity();
	float getDensity();
};
