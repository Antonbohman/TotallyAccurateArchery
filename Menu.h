#pragma once
#include "Global.h"
#include "Graphic.h"
#include "Input.h"
#include "Game.h"

class Menu {
private:
	Graphic* graphic;
	Input* input;
	Game* game;

public:
	Menu(Graphic* _graphic, Input* _input, Game* _game);
	~Menu();

	void Run(double delta);
	void Draw();
};

