#pragma once
#include "Graphic.h"
#include "Input.h"
#include "TextureHandler.h"

#include "elements/Camera.h"
#include "elements/Arrow.h"
#include "elements/Human.h"
#include "elements/Bow.h"
#include "elements/Target.h"
#include "elements/Ground.h"

#define MAX_TARGET 10
#define MAX_ARROW 50

class Game {
private:
	enum Texture { 
		T0_Background,
		T1_Arrow,
		T2_Bow,
		T3_Human,
		T4_Target,
		T5_Ground
	};

	Graphic* graphic;
	Input* input;

	TextureHandler textures;

	Camera* camera;

	Ground* ground;
	Human* human;
	Bow* bow;
	Arrow* activeArrow;
	Arrow** arrows;
	Target** targets;

	int nrOfArrows = 0;

public:
	Game(Graphic* _graphic, Input* _input);
	~Game();

	void NewGame();

	void Run(double delta);
	void Draw();
};

