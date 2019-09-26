#pragma once
#include "Global.h"
#include "Graphic.h"
#include "Input.h"

class Game {
private:
	Graphic* graphic;
	Input* input;
	

public:
	Game(Graphic* _graphic, Input* _input);
	~Game();

	void NewGame();

	void Run(double delta);
	void Draw();
};

