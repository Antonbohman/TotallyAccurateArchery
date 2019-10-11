#include "Game.h"

Game::Game(Graphic* _graphic, Input* _input) {
	graphic = _graphic;
	input = _input;

	camera = nullptr;

	ground = nullptr;
	human = nullptr;
	bow = nullptr;
	activeArrow = nullptr;

	targets = new Target*[MAX_TARGET];
	arrows = new Arrow*[MAX_ARROW];

	for (int i = 0; i < MAX_TARGET; i++) {
		targets[i] = nullptr;
	}

	for (int i = 0; i < MAX_ARROW; i++) {
		arrows[i] = nullptr;
	}

	//make sure to preload all necesary textures here in right order as described in Texture enum
	textures.SetTexture(graphic->device, T0_Background, L"resources/Fishy.dds");
	textures.SetTexture(graphic->device, T1_Arrow, L"resources/giftpil.dds");
	textures.SetTexture(graphic->device, T2_Bow, L"resources/bow.dds");
	textures.SetTexture(graphic->device, T3_Human, L"resources/human.dds");
	textures.SetTexture(graphic->device, T4_Target, L"resources/Fishy.dds");
	textures.SetTexture(graphic->device, T5_Ground, L"resources/ground.dds");
}

Game::~Game() {
	delete camera;

	delete ground;
	delete human;
	delete bow;
	delete activeArrow;

	for (int i = 0; i < MAX_TARGET; i++) {
		delete targets[i];
	}
	delete[] targets;

	for (int i = 0; i < MAX_ARROW; i++) {
		delete arrows[i];
	}
	delete[] arrows;
}

void Game::NewGame() {
	delete camera;

	delete ground;
	delete human;
	delete bow;
	delete activeArrow;

	for (int i = 0; i < MAX_TARGET; i++) {
		delete targets[i];
		targets[i] = nullptr;
	}

	for (int i = 0; i < MAX_ARROW; i++) {
		delete arrows[i];
		arrows[i] = nullptr;
	}

	//create camera element to be used to move view
	camera = new Camera(
		graphic,
		{ 0, 0, 1.0f }
	);

	ground = new Ground(
		graphic,
		camera,
		{ 0, 150, 0.0f }, // z value for back "ground" is 0.8 and fore "ground" is 0.6  
		{ 80000, 900 },
		TopLeft,
		textures.GetTexture(T5_Ground)->ShaderResourceView
	); 
	
	human = new Human(
		graphic,
		camera,
		{ W_WIDTH / 2, 225, 0.55f }, // z value [0.0-0.1, 0.9-1.0] reserved for foreground/background elements  
		{ 100, 180 },
		Middle,
		textures.GetTexture(T3_Human)->ShaderResourceView
	); 

	bow = new Bow(
		graphic,
		camera,
		{ W_WIDTH / 2, 225, 0.52f }, // z value [0.0-0.1, 0.9-1.0] reserved for foreground/background elements  
		{ 100, 180 },
		Middle,
		textures.GetTexture(T2_Bow)->ShaderResourceView,
		Vector3(1, 1, 0),
		float(0.9),
		float(1),
		float(0.05)
	); 

	targets[0] = new Target(
		graphic,
		camera,
		{ W_WIDTH * 2, (W_HEIGHT / 2) + 100, 0.40f }, 
		{ 100, 100 },
		Middle,
		textures.GetTexture(T4_Target)->ShaderResourceView
	);

	activeArrow = nullptr;
}

void Game::Run(double delta) {
	if (activeArrow) {
		//if active is set we update it flightpath unitll colision is made and we unset active arrow	
		activeArrow->updateElement(delta);

		//when collision is done, move pointer to arrows array and set activeArrow to nullptr
		if(activeArrow->isColliding(static_cast<PhysicalElement*>(ground)) || activeArrow->isColliding(targets[0]))
		{
			int i = 0;
			while (arrows[i]) { i++; }
			if (i < MAX_ARROW) {
				arrows[i] = activeArrow;
				activeArrow = nullptr;
			}

			camera->clearFocus();
			camera->setPos({ W_WIDTH / 2, W_HEIGHT / 2 });
		}


		//some temporary keybinds to alter current state, manualy sets arrow as collided and resets camera back to human
		if (input->Key(Key::_Space).Active) {
			camera->clearFocus();
			camera->setPos({ W_WIDTH / 2, W_HEIGHT / 2 });
		}

		if (input->Key(Key::_Space).Active) {
			int i = 0;
			while (arrows[i]) { i++; }
			if (i < MAX_ARROW) {
				arrows[i] = activeArrow;
				activeArrow = nullptr;
			}
		}
		
	} else {
		//when no arrow is currently flying we do calculation for firing a new arrow
		human->updateElement();
		bow->updateElement();

		//quick way to release a custom valued arrow on demand
		if (input->Key(Key::_Space).Active) {
			nrOfArrows++;
			activeArrow = new Arrow(
				//set arrow values for new arrow to be throwned away
				graphic,
				camera,
				{ W_WIDTH / 2, W_HEIGHT / 2, 0.80f-(nrOfArrows*0.001f) }, // z value [0.0-0.1, 0.9-1.0] reserved for foreground/background elements  
				{ 90, 14 },
				Middle,
				textures.GetTexture(T1_Arrow)->ShaderResourceView,
				//Vector3(0, 0, 0),
				bow->fireArrow(0.06f),
				//Vector3(20, 14, 0),
				//Vector3(0, 0, 0),
				0.0001f,
				0.06f/*,
				1.225f*/
			);
		}

		//should be set to new arrow instead as focus point when added, or keep it as is to see the arrow land from targets viewpoint
		if (input->Key(Key::_Space).Active) camera->setFocus(activeArrow);
	}

	//update camera with focus or fixed position if needed
	camera->updateFocus();

	//set all elements in view regarding its world position in relation to camera position
	ground->moveWorldToView();
	human->moveWorldToView();
	bow->moveWorldToView();

	if (activeArrow) activeArrow->moveWorldToView();

	for (int i = 0; i < MAX_TARGET; i++) {
		if (targets[i]) targets[i]->moveWorldToView();
	}

	for (int i = 0; i < MAX_ARROW; i++) {
		if (arrows[i]) arrows[i]->moveWorldToView();
	}
}

void Game::Draw() {
	//call draw function for all objects
	ground->renderElement();
	human->renderElement();
	bow->renderElement();

	if (activeArrow) activeArrow->renderElement();

	for (int i = 0; i < MAX_TARGET; i++) {
		if (targets[i]) targets[i]->renderElement();
	}

	for (int i = 0; i < MAX_ARROW; i++) {
		if (arrows[i]) arrows[i]->renderElement();
		else i = MAX_ARROW;
	}
}


/*
	Anton's Jazzlists
	*dragable line
	*moving background with triple object pushing on sides 

	*counter incl. font with sprites (alternative check with printing to console or something...)
	*texture for arrow, targets, world

	*smooth camera movement
	*option object for stuff like kind of bows, planets and wind forces (moving obstacles?)
*/