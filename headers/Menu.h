#pragma once
#include "Global.h"
#include "Graphic.h"
#include "Input.h"
#include "Game.h"

#include "elements/AbstractElement.h"
#include "elements/Button.h"

class Menu {
private:
	enum Texture {
		T0_Background,
		T1_PLAY,
		T2_BACK,
		T3_QUIT,
		T4_CRED,
		T5_HELP
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

