#pragma once
#include "Graphic.h"
#include "Input.h"

class BaseElement {
private:
	typedef struct TriangleVertex {
		float x, y, z;
		float r, g, b;
		float u, v;
	};

	ID3D11Buffer* quadBuffer;
	ID3D11Device* device;

	void createQuad(); //calculates new quad for element
	void renderElement(); //loads element and texture into pipeline
	void createVertices(); //creates vertices from dimensions and positions

protected:
	typedef enum Anchor {
		Middle = 0x02,
		TopLeft = 0x04,
		TopRight = 0x08,
		BottomLeft = 0x16,
		BottomRight = 0x32,
	};

	typedef struct Sprite {
		bool spritesheet = false;
		int currentFrame = 0;
		int columns = 0;			//keep it even divided with 1 for correct UV cords
		int rows = 0;				//keep it even divided with 1 for correct UV cords
	};

	XMFLOAT3 position;
	XMFLOAT2 size;
	Anchor anchor;

	Sprite spriteInfo;

	ID3D11ShaderResourceView* shaderResourceView;

public:
	BaseElement();
	BaseElement(XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, Anchor harbor, ID3D11Device* _device, ID3D11ShaderResourceView* texturePtr);
	BaseElement(XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, Anchor harbor, ID3D11Device* _device, ID3D11ShaderResourceView* texturePtr, int columns, int rows);
	virtual ~BaseElement();
};

