#include "Game.h"

Game::Game(Graphic* _graphic, Input* _input) {
	graphic = _graphic;
	input = _input;

	camera = nullptr;
	
	print = nullptr;

	sky = nullptr;
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

	nrOfArrows = 0;
	bowForce = 0;

	//make sure to preload all necesary textures here in right order as described in Texture enum
	textures.SetTexture(graphic->device, T0_Background, L"resources/sky.dds");
	textures.SetTexture(graphic->device, T1_Arrow, L"resources/giftpil.dds");
	textures.SetTexture(graphic->device, T2_Bow, L"resources/bow.dds");
	textures.SetTexture(graphic->device, T3_Human, L"resources/human.dds");
	textures.SetTexture(graphic->device, T4_Target, L"resources/target.dds");
	textures.SetTexture(graphic->device, T5_Ground, L"resources/ground.dds");
	textures.SetTexture(graphic->device, T6_Font, L"resources/font.dds");
}

Game::~Game() {
	delete camera;

	delete print;

	delete sky;
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

	delete print;

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

	print = new Print(
		graphic,
		{ W_WIDTH-480, W_HEIGHT, 0.05f },
		{ 480, 40 },
		nullptr,
		textures.GetTexture(T6_Font)->ShaderResourceView,
		WRITE_LEFT,
		12
	);

	sky = new Sky(
		graphic,
		camera,
		{ 0, 0, 0.89f },
		{ W_WIDTH, W_HEIGHT },
		BottomLeft,
		textures.GetTexture(T0_Background)->ShaderResourceView
	);

	ground = new Ground(
		graphic,
		camera,
		{ 0, 150, 0.0f }, // z value for back "ground" is 0.8 and fore "ground" is 0.5
		{ 8000000, 900 },
		TopLeft,
		textures.GetTexture(T5_Ground)->ShaderResourceView
	); 
	
	human = new Human(
		graphic,
		camera,
		{ W_WIDTH / 2, 225, 0.45f }, // z value [0.0-0.1, 0.9-1.0] reserved for foreground/background elements  
		{ 100, 180 },
		Middle,
		textures.GetTexture(T3_Human)->ShaderResourceView
	); 

	bow = new Bow(
		graphic,
		camera,
		{ W_WIDTH / 2, 225, 0.42f }, // z value [0.0-0.1, 0.9-1.0] reserved for foreground/background elements  
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
		{ W_WIDTH * 2, (W_HEIGHT / 2) + 100, 0.70f }, 
		{ 58, 96 },
		Middle,
		textures.GetTexture(T4_Target)->ShaderResourceView
	);

	activeArrow = nullptr;
}

void Game::Run(double delta) {
	bool collide = false;

	//delta = delta * 0.5;

	if (activeArrow) {
		//if active is set we update it flightpath unitll colision is made and we unset active arrow	
		activeArrow->updateElement(delta);

		//see if arrow is colliding with ground
		if(activeArrow->isColliding(static_cast<PhysicalElement*>(ground)))
			collide = true;

		//see if arrow is colliding with any of the targets
		for (int i = 0; i < MAX_TARGET; i++) {
			if (targets[i]) 
				if (activeArrow->isColliding(targets[i])) 
					collide = true;
		}

		//when collision is done, move pointer to arrows array and set activeArrow to nullptr
		if(collide || input->Key(Key::_Enter).Active ) {
			int i = 0;
			while (arrows[i]) { i++; }
			if (i < MAX_ARROW) {
				arrows[i] = activeArrow;
				activeArrow = nullptr;
			} else {
				delete activeArrow;
				activeArrow = nullptr;
			}

			camera->setDelay(3.0f);
			camera->setAnimation(1.0f, 10.0f);
			camera->setFocus({ W_WIDTH / 2, W_HEIGHT / 2 });
		}
		
	} else {
		//reset camera to archer
		if (input->Key(Key::F1).Active) {
			camera->setDelay(0.0f);
			camera->setAnimation(1.0f, 10.0f);
			camera->setFocus({ W_WIDTH / 2, W_HEIGHT / 2 });
		}

		//focus camera on last fired arrow
		if (input->Key(Key::F2).Active) {
			if (nrOfArrows > 0) {
				camera->setDelay(0.0f);
				camera->setAnimation(1.0f, 10.0f);
				camera->setFocus(arrows[nrOfArrows - 1]);
			}
		}

		//clear game field of old arrows
		if (input->Key(Key::F5).Active) {
			for (int i = 0; i < MAX_ARROW; i++) {
				delete arrows[i];
				arrows[i] = nullptr;
			}

			nrOfArrows = 0;
		}

		//move camera with arrow keys
		if (input->Key(Key::_Up).Active || 
			input->Key(Key::_Down).Active ||
			input->Key(Key::_Left).Active ||
			input->Key(Key::_Right).Active) {

			XMFLOAT2 cameraPos = camera->getPos();
			float pixelPerDelta = 1000;

			//move camera up
			if (input->Key(Key::_Up).Active) cameraPos.y += (pixelPerDelta * delta);

			//move camera down
			if (input->Key(Key::_Down).Active) cameraPos.y -= (pixelPerDelta * delta);

			//move camera left
			if (input->Key(Key::_Left).Active) cameraPos.x -= (pixelPerDelta * delta);

			//move camera right
			if (input->Key(Key::_Right).Active) cameraPos.x += (pixelPerDelta * delta);

			if (cameraPos.x < (W_WIDTH / 2)) cameraPos.x = (W_WIDTH / 2);
			if (cameraPos.y < (W_HEIGHT / 2)) cameraPos.y = (W_HEIGHT / 2);

			camera->setDelay(0.0f);
			camera->clearAnimation();
			camera->setFocus(cameraPos);
		}

		//when no arrow is currently flying we do calculation for firing a new arrow
		human->updateElement();
		bow->updateElement(input->Mouse());
		

		//quick way to release a custom valued arrow on demand
		if (input->Key(Key::_Space).Active) {
			bowForce += delta;
		}
		
		if (bowForce && !input->Key(Key::_Space).Active) {
			nrOfArrows++;
			activeArrow = new Arrow(
				//set arrow values for new arrow to be throwned away
				graphic,
				camera,
				{ W_WIDTH / 2, W_HEIGHT / 2, 0.70f - (nrOfArrows*0.001f) }, // z value [0.0-0.1, 0.9-1.0] reserved for foreground/background elements  
				{ 90, 14 },
				Middle,
				textures.GetTexture(T1_Arrow)->ShaderResourceView,
				//Vector3(0, 0, 0),
				bow->fireArrow(bowForce,0.06f),
				//Vector3(20, 14, 0),
				//Vector3(0, 0, 0),
				0.0001f,
				0.06f/*,
				1.225f*/
			);

			//zero our force ahead for next arrow
			bowForce = 0;

			//set camera focus to current arrow
			camera->setDelay(0.0f);
			camera->clearAnimation();
			camera->setFocus(activeArrow);
		}
	}

	//print->setValue((float)(delta),7);
	print->setString("Testar Lite!", 12);

	//update camera with focus or fixed position if needed
	camera->updateFocus(delta);

	//update sky position
	sky->updateElement();

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
	sky->renderElement();
	ground->renderElement();

	for (int i = 0; i < MAX_TARGET; i++) {
		if (targets[i]) targets[i]->renderElement();
	}

	for (int i = 0; i < MAX_ARROW; i++) {
		if (arrows[i]) arrows[i]->renderElement();
		else i = MAX_ARROW;
	}

	if (activeArrow) activeArrow->renderElement();

	human->renderElement();
	bow->renderElement();

	print->renderElement();
}


/*
	Anton's Jazzlists
	*option object for stuff like kind of bows, planets and wind forces (moving obstacles?)
*/