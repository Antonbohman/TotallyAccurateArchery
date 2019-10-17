#pragma once
#include "elements/AbstractElement.h"

#define WRITE_RIGHT 0
#define WRITE_LEFT 1
#define WRITE_DOWN 2
#define WRITE_UP 3

#define MAX_COL 15
#define MAX_ROW 8

class Print : public AbstractElement {
private:
	class Symbol : public AbstractElement {
	private:

	public:
		Symbol() : AbstractElement() {};
		Symbol(Graphic* graphic, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, UINT harbor, ID3D11ShaderResourceView* texturePtr) : AbstractElement(graphic, posToSet, sizeToSet, harbor, texturePtr) {
			spriteInfo.spritesheet = true;
			spriteInfo.maxColumns = MAX_COL;
			spriteInfo.maxRows = MAX_ROW;
			spriteInfo.column = 0;
			spriteInfo.row = 0;
		};
		~Symbol() {};

		void setSprite(UINT col, UINT row) {
			spriteInfo.column = col;
			spriteInfo.row = row;
		};
	};

	Symbol** symbols;
	UINT writeMode;
	UINT maxPrints;

	void SetSymbols(XMFLOAT2* spriteCord, UINT index);
	void clearSymbols();

	char transformIntToChar(int key);
	XMFLOAT2 transformSymbolToSprite(char c);

public:
	Print();
	Print(Graphic* _graphic, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, ID3D11ShaderResourceView* texturePtr, ID3D11ShaderResourceView* fonrPtr, UINT _writeMode, UINT _maxPrints);
	~Print();

	void setString(const char* text, UINT length);
	void setValue(int value);
	void setValue(float value, UINT decimals);

	void renderElement();
};