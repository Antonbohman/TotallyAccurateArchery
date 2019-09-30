#pragma once
#include "Graphic.h"
#include "Input.h"
#include "TextureHandler.h"

class Game {
private:
	enum Texture { Background, Arrow };

	Graphic* graphic;
	Input* input;

	TextureHandler textures;

public:
	Game(Graphic* _graphic, Input* _input);
	~Game();

	void NewGame();

	void Run(double delta);
	void Draw();
};

