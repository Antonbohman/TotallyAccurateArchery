#pragma once
#include "Graphic.h"


class BaseElement {
private:
	void renderElement(); //loads elemnt and texture into pipeline
	void createVertices(); //creates vertices from dimensions and positions

protected:
	typedef enum Anchor {
		Middle = 0x02,
		TopLeft = 0x04,
		TopRight = 0x08,
		BottomLeft = 0x16,
		BottomRight = 0x32,
	};

	XMFLOAT3 position;
	XMFLOAT2 size;
	Anchor anchor;

	ID3D11Resource* texture2D;
	ID3D11ShaderResourceView* shaderResourceView;

public:
	BaseElement();
	BaseElement(XMFLOAT3 sosToSet, XMFLOAT2 sizeToSet, Anchor harbor, ID3D11Device* device, const wchar_t* textureName);
	virtual ~BaseElement();
};

