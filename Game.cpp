#include "Game.h"

Game::Game(Graphic* _graphic, Input* _input) {
	graphic = _graphic;
	input = _input;

	testObj = nullptr;
	camera = nullptr;

	//make sure to preload all necesary textures here in right order as described in Texture enum
	textures.SetTexture(graphic->device, T0_Background, L"resources/Fishy.dds");
}

Game::~Game() {
	delete camera;
	delete testObj;
}

void Game::NewGame() {
	delete camera;
	delete testObj;

	//create camera element to be used to move view
	camera = new Camera(
		graphic,
		{ 0, 0, 1.0f }
	);

	//create new objects and set init variables for a new game
	testObj = new PhysicalElement(
		graphic,
		camera,
		{ W_WIDTH / 2, W_HEIGHT / 2, 0.5f }, // z value [0.0-0.1, 0.9-1.0] reserved for foreground/background elements  
		{ 400, 200 },
		Middle,
		textures.GetTexture(T0_Background)->ShaderResourceView
	);
}

void Game::Run(double delta) {
	//call on calculation function for all objects in game
	//e.g update movement, values and check collisons

	//update elements movements and such
	testObj->updateElement();

	//update camera with focus or fixed position if needed
	camera->updateFocus();

	//set all elements in view regarding its world position in relation to camera position
	testObj->moveWorldToView();
}

void Game::Draw() {
	//call draw function for all objects
	testObj->renderElement();
}
