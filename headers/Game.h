#pragma once
#include "Graphic.h"
#include "Input.h"
#include "TextureHandler.h"

#include "elements/BaseElement.h"

class Game {
private:
	enum Texture { Background, Arrow };

	Graphic* graphic;
	Input* input;

	TextureHandler textures;
	BaseElement* testObj;

public:
	Game(Graphic* _graphic, Input* _input);
	~Game();

	void NewGame();

	void Run(double delta);
	void Draw();
};

