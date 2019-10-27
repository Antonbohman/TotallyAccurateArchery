/*
* menu.h/menu.cpp
* Handles elements and configurations that are avaible when user is menu stage of game.
* Validates mouseclicks and if certain buttons are triggered and changes menus accordingly
* or starts the process of starting a new game. Or puts program in QUIT mode.
*
* Written and all rights reserved by: Filip Unger & Anton Bohman
*/

#pragma once
#include "Global.h"
#include "Graphic.h"
#include "Input.h"
#include "Game.h"

#include "elements/AbstractElement.h"
#include "elements/Button.h"
#include "elements/Print.h"

#define TEXT_ROWS 5

class Menu {
private:
	enum Texture {
		T0_Background,
		T1_PLAY,
		T2_BACK,
		T3_QUIT,
		T4_CRED,
		T5_HELP,
		T6_FONT
	};

	enum MenuStage {
		MAIN,
		CRED,
		HELP
	};

	Graphic* graphic;
	Input* input;
	Game* game;

	TextureHandler textures;
	
	Print* text[TEXT_ROWS];

	AbstractElement* background;
	Button* quit;
	Button* play;
	Button* cred;
	Button* help;
	Button* back;

	MenuStage stage;

public:
	Menu(Graphic* _graphic, Input* _input, Game* _game);
	~Menu();

	bool Run(double delta);
	void Draw();
};

