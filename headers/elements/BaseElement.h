#pragma once
#include "Graphic.h"
#include "TextureHandler.h"
#include "Input.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

enum Anchor {
	Middle = 0x02,
	TopLeft = 0x04,
	TopRight = 0x08,
	BottomLeft = 0x16,
	BottomRight = 0x32,
};

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

	TriangleVertex* vertices;

	void createVertexBuffer();
	void createQuad();	//calculates new quad for element

protected:
	struct UV {
		float X0 = 0;
		float X1 = 1;
		float Y0 = 0;
		float Y1 = 1;
	};

	 struct Sprite {
		bool spritesheet = false;
		int maxColumns = 0;				//keep it even divided with 1 for correct UV cords
		int maxRows = 0;				//keep it even divided with 1 for correct UV cords
		int column = 0;
		int row = 0;
		int frame = 0;
	};

	XMFLOAT4 colour;
	XMFLOAT3 viewPosition;
	XMFLOAT2 size;
	Anchor anchor;
	float rotation;
	UV uv;
	Sprite spriteInfo;

	double convertPixelToMeter(const float* pixels);
	float convertMeterToPixel(const double* meters);

	void getQuadBoundriesView(float* pos_X0, float* pos_X1, float* pos_Y0, float* pos_Y1); //sets x and y positon for elements boundries
	XMFLOAT2 rotatePoint(float x, float y); //transforms points to origo and rotates it around its anchor point and transforms it back correspondly

public:
	BaseElement();
	BaseElement(Graphic* _graphic, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr);
	virtual ~BaseElement();

	void setTexture(ID3D11ShaderResourceView* texture);
	void setSize(XMFLOAT2 newSize);
	virtual void setColour(XMFLOAT4 newColour);

	virtual void renderElement();
	virtual void updateElement() = 0;
};

