#pragma once
#include "elements\PhysicalElement.h"
#include "math.h"

class Sky : public PhysicalElement {
private:
	class Side : public AbstractElement {
	public:
		Side() : AbstractElement() {};
		Side(Graphic* graphic, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr) : AbstractElement(graphic, posToSet, sizeToSet, harbor, texturePtr) {};
		~Side() {};

		void updateElement(float X, float Y) {
			viewPosition.x = X;
			viewPosition.y = Y;
		};
	};

	Side * side[3];
public:
	Sky();
	Sky(Graphic* _graphic, Camera* _camera, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr);
	~Sky();

	void setColour(XMFLOAT4 newColour);

	void updateElement();
	void renderElement();
};

