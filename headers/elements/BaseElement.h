#pragma once
#include "Graphic.h"
#include "Input.h"

using namespace DirectX;

class BaseElement {
private:
	struct TriangleVertex {
		float x, y, z;
		float r, g, b, a;
		float u, v;
	};

	Graphic* graphic;
	ID3D11Buffer* quadBuffer;
	ID3D11ShaderResourceView* shaderResourceView;

	XMFLOAT2 rotatePoint(float x, float y); //moves point to origo and rotates it around its anchor and moves it back correspondly
	void createVertexBuffer();
	void createQuad();	//calculates new quad for element

protected:
	enum Anchor {
		Middle = 0x02,
		TopLeft = 0x04,
		TopRight = 0x08,
		BottomLeft = 0x16,
		BottomRight = 0x32,
	};

	struct UV {
		float X0 = 0;
		float X1 = 1;
		float Y0 = 0;
		float Y1 = 1;
	};

	 struct Sprite {
		bool spritesheet = false;
		int currentFrame = 0;
		int columns = 0;			//keep it even divided with 1 for correct UV cords
		int rows = 0;				//keep it even divided with 1 for correct UV cords
	};

	XMFLOAT4 colour;
	XMFLOAT3 position;
	XMFLOAT2 size;
	Anchor anchor;
	float rotation;
	UV uv;
	Sprite spriteInfo;

public:
	BaseElement();
	BaseElement(Graphic* _graphic, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr);
	virtual ~BaseElement();

	void renderElement();
};

