#pragma once
#include "elements/AbstractElement.h"

#define WRITE_RIGHT 0
#define WRITE_LEFT 1

class Print : public AbstractElement {
private:
	class Symbol : public AbstractElement {
	private:

	public:
		Symbol() : AbstractElement() {};
		Symbol(Graphic* graphic, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr) : AbstractElement(graphic, posToSet, sizeToSet, harbor, texturePtr) {};
		virtual ~Symbol();
	};

	Symbol** symbols;

public:
	Print();
	Print(Graphic* _graphic, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr, UINT writeMode);
	virtual ~Print();

	void setString(const char* text);
	void setValue(int value);
	void setValue(float value);
	void setValue(double value);

};