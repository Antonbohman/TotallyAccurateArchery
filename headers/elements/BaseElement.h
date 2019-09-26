#pragma once
#include "Graphic.h"


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

	XMFLOAT3 Position;
	XMFLOAT2 Size;
	Anchor anchor;

	ID3D11Resource* texture2D;
	ID3D11ShaderResourceView* ShaderResourceView;

public:
	BaseElement();
	BaseElement(XMFLOAT3 PosToSet, XMFLOAT2 SizeToSet, Anchor Harbor, ID3D11Device* _device, const wchar_t* textureName);
	virtual ~BaseElement();
};

