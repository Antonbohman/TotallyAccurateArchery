#include "elements/Print.h"


Print::Print() : AbstractElement() {
	symbols = nullptr;
	writeMode = 0;
	maxPrints = 0;
}

Print::Print(Graphic* _graphic, XMFLOAT3 posToSet, XMFLOAT2 sizeToSet, ID3D11ShaderResourceView* texturePtr, ID3D11ShaderResourceView* fonrPtr, UINT _writeMode, UINT _maxPrints) : AbstractElement(_graphic, posToSet, sizeToSet, TopLeft, texturePtr) {
	writeMode = _writeMode;
	maxPrints = _maxPrints;

	symbols = new Symbol*[maxPrints];

	if (writeMode == WRITE_RIGHT || writeMode == WRITE_LEFT) {
		float sizeX = (sizeToSet.x / (float)maxPrints);
		for (int i = 0; i < maxPrints; i++) {
			symbols[i] = new Symbol(_graphic, { posToSet.x + (sizeX*i) , posToSet.y, posToSet.z - 0.0001f }, { sizeX , sizeToSet.y }, TopLeft, fonrPtr);
		}
	} else {
		float sizeY = (sizeToSet.y / (float)maxPrints);
		for (int i = 0; i < maxPrints; i++) {
			symbols[i] = new Symbol(_graphic, { posToSet.x , posToSet.y - (sizeY*i), posToSet.z - 0.0001f }, { sizeToSet.x , sizeY }, TopLeft, fonrPtr);
		}
	}
}

Print::~Print() {
	for (int i = 0; i < maxPrints; i++) {
		delete symbols[i];
	}

	delete[] symbols;
}

void Print::setString(const char* text, UINT length) {
	XMFLOAT2* spriteCord = new XMFLOAT2[maxPrints];
	int index = 0;

	for (index; index < length && index < maxPrints; index++) {

		spriteCord[index] = transformSymbolToSprite(text[(length - 1) - index]);
	}


	SetSymbols(spriteCord, index);

	delete[] spriteCord;
}

void Print::setValue(int value) {
	XMFLOAT2* spriteCord = new XMFLOAT2[maxPrints];
	int index = 0;
	int number = 0;

	if (value < 0) {
		value *= -1;

		do {
			number = value % 10;
			spriteCord[index] = transformSymbolToSprite(transformIntToChar(number));
			value -= number;
			value /= 10;
			index++;
		} while (value && index < maxPrints-1);

		spriteCord[index] = transformSymbolToSprite((char)45);
		index++;
	} else {
		do {
			number = value % 10;
			spriteCord[index] = transformSymbolToSprite(transformIntToChar(number));
			value -= number;
			value /= 10;
			index++;
		} while (value && index < maxPrints);
	}


	SetSymbols(spriteCord,index);

	delete[] spriteCord;
}

void Print::setValue(float value, UINT precision) {
	XMFLOAT2* spriteCord = new XMFLOAT2[maxPrints];
	int index = 0;
	int number = 0;

	precision < 1 ? precision = 1 : precision > (maxPrints - 2) ? precision = (maxPrints - 2) : NULL;

	int integer = floor(value);
	int decimals = floor((value - integer)*pow(10,precision));

	for (index; index < precision && index < maxPrints-2; index++) {
		number = decimals % 10;
		spriteCord[index] = transformSymbolToSprite(transformIntToChar(number));
		decimals -= number;
		decimals /= 10;
	}

	spriteCord[index] = transformSymbolToSprite((char)44);
	index++;

	do {
		number = integer % 10;
		spriteCord[index] = transformSymbolToSprite(transformIntToChar(number));
		integer -= number;
		integer /= 10;
		index++;
	} while (integer && index < maxPrints);

	SetSymbols(spriteCord, index);

	delete[] spriteCord;
}

void Print::renderElement() {
	AbstractElement::renderElement();

	for (int i = 0; i < maxPrints; i++) {
		symbols[i]->renderElement();
	}
}

void Print::SetSymbols(XMFLOAT2* spriteCord, UINT index) {
	clearSymbols();

	if (writeMode == WRITE_RIGHT || writeMode == WRITE_DOWN) {
		for (int i = 0; i < index; i++) {
			symbols[i]->setSprite(spriteCord[(index - 1) - i].x, spriteCord[(index - 1) - i].y);
		}
	} else {
		for (int i = 0; i < index; i++) {
			symbols[(maxPrints-1)-i]->setSprite(spriteCord[i].x, spriteCord[i].y);
		}
	}
}

void Print::clearSymbols() {
	for (int i = 0; i < maxPrints; i++) {
		symbols[i]->setSprite(0,0);
	}
}

char Print::transformIntToChar(int key) {
	return (char)key + 48;
}

XMFLOAT2 Print::transformSymbolToSprite(char c) {
	XMFLOAT2 spriteCord(0, 0);

	if ((int)c < 47) {
		spriteCord = { ((int)c - 32.0f), 0 };
	} else if ((int)c < 62) {
		spriteCord = { ((int)c - 47.0f), 1 };
	} else if ((int)c < 77) {
		spriteCord = { ((int)c - 62.0f), 2 };
	} else if ((int)c < 92) {
		spriteCord = { ((int)c - 77.0f), 3 };
	} else if ((int)c < 107) {
		spriteCord = { ((int)c - 92.0f), 4 };
	} else if ((int)c < 122) {
		spriteCord = { ((int)c - 107.0f), 5 };
	} else if ((int)c < 127) {
		spriteCord = { ((int)c - 122.0f), 6 };
	}

	return spriteCord;
}
