#pragma once
#include "Graphic.h"
#include "Input.h"
#include "TextureHandler.h"

#include "elements/Camera.h"
#include "elements/Print.h"
#include "elements/Arrow.h"
#include "elements/Human.h"
#include "elements/Bow.h"
#include "elements/Target.h"
#include "elements/Ground.h"
#include "elements/Sky.h"
#include "elements/Wind.h"

#define MAX_TARGET 10
#define MAX_ARROW 50

#define MAX_PRINTS 4

class Game {
private:
	enum Texture { 
		T0_Background,
		T1_Arrow,
		T2_Bow,
		T3_Human,
		T4_Target,
		T5_Ground,
		T6_Font,
		T7_Wind
	};

	Graphic* graphic;
	Input* input;

	TextureHandler textures;

	Camera* camera;

	Print** prints;

	Sky* sky;
	Ground* ground;
	Human* human;
	Bow* bow;
	Arrow* activeArrow;
	Arrow** arrows;
	Target** targets;
	
	Wind* wind;

	int nrOfArrows;
	float bowForce;

public:
	Game(Graphic* _graphic, Input* _input);
	~Game();

	void NewGame();

	void Run(double delta);
	void Draw();
};

