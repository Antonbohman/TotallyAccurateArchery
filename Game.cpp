#include "Game.h"

Game::Game(Graphic* _graphic, Input* _input) {
	graphic = _graphic;
	input = _input;

	camera = nullptr;
	
	prints = new Print*[MAX_PRINTS];

	for (int i = 0; i < MAX_PRINTS; i++) {
		prints[i] = nullptr;
	}

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

	wind = nullptr;

	//make sure to preload all necesary textures here in right order as described in Texture enum
	textures.SetTexture(graphic->device, T0_Background, L"resources/sky.dds");
	textures.SetTexture(graphic->device, T1_Arrow, L"resources/giftpil.dds");
	textures.SetTexture(graphic->device, T2_Bow, L"resources/bow.dds");
	textures.SetTexture(graphic->device, T3_Human, L"resources/human.dds");
	textures.SetTexture(graphic->device, T4_Target, L"resources/target.dds");
	textures.SetTexture(graphic->device, T5_Ground, L"resources/ground.dds");
	textures.SetTexture(graphic->device, T6_Font, L"resources/font.dds");
	textures.SetTexture(graphic->device, T7_Wind, L"resources/wind.dds");
	textures.SetTexture(graphic->device, T8_HalfArrow, L"resources/halvgiftpil.dds");
}

Game::~Game() {
	delete camera;

	for (int i = 0; i < MAX_PRINTS; i++) {
		delete prints[i];
	}
	delete[] prints;

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

	delete wind;
}

void Game::NewGame() {
	delete camera;

	for (int i = 0; i < MAX_PRINTS; i++) {
		delete prints[i];
		prints[i] = nullptr;
	}

	delete ground;
	delete human;
	delete bow;
	delete activeArrow;

	delete wind;

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
	 
	//arrow speed print
	prints[0] = new Print(
		graphic,
		{ W_WIDTH-390, W_HEIGHT-35, 0.05f },
		{ 320, 40 },
		nullptr,
		textures.GetTexture(T6_Font)->ShaderResourceView,
		WRITE_LEFT,
		8
	);

	prints[1] = new Print(
		graphic,
		{ W_WIDTH - 70, W_HEIGHT-44, 0.05f },
		{ 60, 30 },
		nullptr,
		textures.GetTexture(T6_Font)->ShaderResourceView,
		WRITE_LEFT,
		3
	);

	prints[10] = new Print(
		graphic,
		{ W_WIDTH - 330, W_HEIGHT - 9, 0.05f },
		{ 330, 30 },
		nullptr,
		textures.GetTexture(T6_Font)->ShaderResourceView,
		WRITE_LEFT,
		11
	);

	prints[0]->setValue(0.0f, 4);
	prints[1]->setString("M/S", 3);
	prints[10]->setString("Arrow speed", 11);

	//wind speed print
	prints[2] = new Print(
		graphic,
		{ 10, W_HEIGHT-120, 0.05f },
		{ 80, 20 },
		nullptr,
		textures.GetTexture(T6_Font)->ShaderResourceView,
		WRITE_LEFT,
		6
	);

	prints[3] = new Print(
		graphic,
		{ 95, W_HEIGHT-124, 0.05f },
		{ 32, 16 },
		nullptr,
		textures.GetTexture(T6_Font)->ShaderResourceView,
		WRITE_LEFT,
		3
	);

	prints[2]->setValue(0.0f, 3);
	prints[3]->setString("M/S", 3);

	//gravity type print
	prints[4] = new Print(
		graphic,
		{ 10, 40, 0.05f },
		{ 600, 30 },
		nullptr,
		textures.GetTexture(T6_Font)->ShaderResourceView,
		WRITE_RIGHT,
		20
	);

	prints[4]->setString("Gravity: Earth", 20);

	//bow force print
	prints[5] = new Print(
		graphic,
		{ W_WIDTH - 330, 50, 0.05f },
		{ 320, 40 },
		nullptr,
		textures.GetTexture(T6_Font)->ShaderResourceView,
		WRITE_LEFT,
		10
	);

	prints[11] = new Print(
		graphic,
		{ W_WIDTH - 300, 85, 0.05f },
		{ 300, 30 },
		nullptr,
		textures.GetTexture(T6_Font)->ShaderResourceView,
		WRITE_LEFT,
		9
	);

	prints[5]->setValue(0.0f, 3);
	prints[11]->setString("Bow Force", 9);

	//camera position print
	prints[6] = new Print(
		graphic,
		{ 140, W_HEIGHT-10, 0.05f },
		{ 60, 30 },
		nullptr,
		textures.GetTexture(T6_Font)->ShaderResourceView,
		WRITE_LEFT,
		2
	);

	prints[7] = new Print(
		graphic,
		{ 200, W_HEIGHT-10, 0.05f },
		{ 150, 30 },
		nullptr,
		textures.GetTexture(T6_Font)->ShaderResourceView,
		WRITE_RIGHT,
		5
	);

	prints[8] = new Print(
		graphic,
		{ 140, W_HEIGHT - 50, 0.05f },
		{ 60, 30 },
		nullptr,
		textures.GetTexture(T6_Font)->ShaderResourceView,
		WRITE_LEFT,
		2
	);

	prints[9] = new Print(
		graphic,
		{ 200, W_HEIGHT - 50, 0.05f },
		{ 150, 30 },
		nullptr,
		textures.GetTexture(T6_Font)->ShaderResourceView,
		WRITE_RIGHT,
		5
	);

	prints[6]->setString("X:", 2);
	prints[7]->setValue(0);
	prints[8]->setString("Y:", 2);
	prints[9]->setValue(0);

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

	ground->setColour(XMFLOAT4(0.4f, 1.0f, 0.4f, 1.0f));
	ground->setGravity(GravityType::Earth);
	ground->setDensity(1.225f);
	sky->setColour(XMFLOAT4(0.4f, 0.6f, 1.0f, 1.0f));
	
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
		Vector3(1, 1, 0)
	); 

	bow->setBowType(BowType::LongBow);

	targets[0] = new Target(
		graphic,
		camera,
		{ W_WIDTH * 2, (W_HEIGHT / 2) + 100, 0.70f }, 
		{ 58, 96 },
		Middle,
		textures.GetTexture(T4_Target)->ShaderResourceView
	);

	targets[1] = new Target(
		graphic,
		camera,
		{ W_WIDTH * 0.75f, (W_HEIGHT / 2) - 100, 0.70f },
		{ 58, 96 },
		Middle,
		textures.GetTexture(T4_Target)->ShaderResourceView
	);

	wind = new Wind(
		graphic,
		{ 60, W_HEIGHT-60, 0.09f },
		{ 100, 100 },
		Middle,
		textures.GetTexture(T7_Wind)->ShaderResourceView
	);

	wind->randomizeWind();

	activeArrow = nullptr;
}

void Game::Run(double delta) {
	bool collide = false;

	//delta = delta * 0.25;

	if (activeArrow) {
		//if active is set we update it flightpath unitll colision is made and we unset active arrow	
		activeArrow->updateElement(delta, wind);

		prints[0]->setValue(activeArrow->getVelocity(), 4);

		//see if arrow is colliding with ground
		if(activeArrow->isColliding(static_cast<PhysicalElement*>(ground)))
			collide = true;

		//see if arrow is colliding with any of the targets
		for (int i = 0; i < MAX_TARGET; i++) {
			if (targets[i]) 
				if (activeArrow->isColliding(targets[i]->hitbox)) 
				{
					collide = true;
					activeArrow->arrowSnap(textures.GetTexture(T8_HalfArrow));
				}
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

			prints[0]->setValue(0.0f, 4);

			camera->setDelay(3.0f);
			camera->setAnimation(1.0f, 10.0f);
			camera->setFocus({ W_WIDTH / 2, W_HEIGHT / 2 });

			wind->randomizeWind();  

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

		if (input->Key(Key::D1).Active) {
			ground->setGravity(GravityType::Earth);
			ground->setTexture(textures.GetTexture(T5_Ground)->ShaderResourceView);
			ground->setColour(XMFLOAT4(0.4f, 1.0f, 0.4f, 1.0f));
			sky->setColour(XMFLOAT4(0.4f, 0.6f, 1.0f, 1.0f));
			prints[4]->setString("Gravity: Earth     ", 20);
			ground->setDensity(1.225f);
		}

		if (input->Key(Key::D2).Active) {
			ground->setGravity(GravityType::Lunar);
			ground->setTexture(textures.GetTexture(T5_Ground)->ShaderResourceView);
			ground->setColour(XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f));
			sky->setColour(XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f));
			prints[4]->setString("Gravity: Lunar     ", 20);
			ground->setDensity(0.0f);
		}

		if (input->Key(Key::D3).Active) {
			ground->setGravity(GravityType::Mars);
			ground->setTexture(textures.GetTexture(T5_Ground)->ShaderResourceView);
			ground->setColour(XMFLOAT4(1.0f, 0.7f, 0.0f, 1.0f));
			sky->setColour(XMFLOAT4(1.0f, 0.9f, 0.0f, 1.0f));
			prints[4]->setString("Gravity: Mars      ", 20);
			ground->setDensity(0.02f);
		}

		if (input->Key(Key::D4).Active) {
			ground->setGravity(GravityType::Sun);
			ground->setTexture(textures.GetTexture(T5_Ground)->ShaderResourceView);
			ground->setColour(XMFLOAT4(1.0f, 0.9f, 0.0f, 1.0f));
			sky->setColour(XMFLOAT4(1.0f, 1.0f, 0.6f, 1.0f));
			prints[4]->setString("Gravity: Sun       ", 20);
			ground->setDensity(0.0002f); //sun convective zone
		}

		if (input->Key(Key::D5).Active) {
			ground->setGravity(GravityType::NoGravity);
			ground->setTexture(textures.GetTexture(T5_Ground)->ShaderResourceView);
			ground->setColour(XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f));
			sky->setColour(XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f));
			prints[4]->setString("Gravity: No Gravity", 20);
			ground->setDensity(0.0f);
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

		//draw bowstring when space is pressed
		if (input->Key(Key::_Space).Active) {
			bow->drawArrow(delta);
		}
		
		if (bow->arrowReady() && !input->Key(Key::_Space).Active) {
			nrOfArrows++;
			activeArrow = new Arrow(
				//set arrow values for new arrow to be throwned away
				graphic,
				camera,
				{ W_WIDTH / 2, 225, 0.70f - (nrOfArrows*0.001f) }, // z value [0.0-0.1, 0.9-1.0] reserved for foreground/background elements  
				{ 90, 14 },
				Middle,
				textures.GetTexture(T1_Arrow)->ShaderResourceView,
				bow->fireArrow(0.06f),
				0.0001f,
				0.06f,
				ground->getDensity(),
				ground->getGravity()
			);

			//set camera focus to current arrow
			camera->setDelay(0.0f);
			camera->clearAnimation();
			camera->setFocus(activeArrow);
		}

		prints[5]->setValue(bow->currentDrawForce(), 3);
	}

	prints[2]->setValue(wind->getWindDirectionAndSpeed().z, 3);

	//update camera with focus or fixed position if needed
	camera->updateFocus(delta);
	prints[7]->setValue(camera->getOffset().x);
	prints[9]->setValue(camera->getOffset().y);

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

	wind->updateElement(delta);
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

	for (int i = 0; i < MAX_PRINTS; i++) {
		if (prints[i]) prints[i]->renderElement();
	}

	wind->renderElement();
}


/*
	Anton's Jazzlists
	*option object for stuff like kind of bows, planets and wind forces (moving obstacles?)
	*Nat King Cole
*/