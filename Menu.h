#pragma once
#include "Global.h"
#include "Graphic.h"
#include "Input.h"

class Menu {
private:
	Graphic* graphic;
	Input* input;

public:
	Menu(Graphic* _graphic, Input* _input);
	~Menu();

	void Run(double delta);
	void Draw();
};

