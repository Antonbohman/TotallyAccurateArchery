/*
* game.h/game.cpp
* Main point for handeling all the elements involved when a new game is started.
* Updates all necesary elements and make sure abstract objects as camera and hud elements is updated along with the
* game movements and calculations. Make sure right elements are updated depending on what stage of the game is in at
* the moment and that only right buttons are active at right moments.
*
* Make sure all game related elements are rendered into the graphical object for each iteration of draw.
*
* Written and all rights reserved by: Filip Unger & Anton Bohman
*/

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

#define MAX_PRINTS 23

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
		T7_Wind,
		T8_HalfArrow
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
	int arrowsHit;
	float playerAccuracy;

public:
	Game(Graphic* _graphic, Input* _input);
	~Game();

	void NewGame();

	void Run(double delta);
	void Draw();
};

