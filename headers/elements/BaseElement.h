#pragma once
#include "Graphic.h"
#include "Input.h"

class BaseElement {
private:
	typedef struct TriangleVertex {
		float x, y, z;
		float r, g, b, a;
		float u, v;
	};

	ID3D11Buffer* quadBuffer;
	ID3D11Device* device;
	ID3D11ShaderResourceView* shaderResourceView;

	void createQuad(); //calculates new quad for element

protected:
	typedef enum Anchor {
		Middle = 0x02,
		TopLeft = 0x04,
		TopRight = 0x08,
		BottomLeft = 0x16,
		BottomRight = 0x32,
	};

	typedef struct UV {
		int X0 = 0;
		int X1 = 1;
		int Y0 = 0;
		int Y1 = 1;
	};

	typedef struct Sprite {
		bool spritesheet = false;
		int currentFrame = 0;
		int columns = 0;			//keep it even divided with 1 for correct UV cords
		int rows = 0;				//keep it even divided with 1 for correct UV cords
	};

	XMFLOAT4 colour;
	XMFLOAT3 position;
	XMFLOAT2 size;
	Anchor anchor;
	UV uv;
	Sprite spriteInfo;

public:
	BaseElement();
	BaseElement(XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, Anchor harbor, ID3D11Device* _device, ID3D11ShaderResourceView* texturePtr);
	BaseElement(XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, Anchor harbor, ID3D11Device* _device, ID3D11ShaderResourceView* texturePtr, int columns, int rows);
	virtual ~BaseElement();

	void renderElement(Graphic* graphic);
};

