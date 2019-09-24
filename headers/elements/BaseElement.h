#pragma once


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

	int x;
	int y;
	int z;
	int height;
	int width;
	Anchor anchor;

public:
	BaseElement();
	virtual ~BaseElement();
};

