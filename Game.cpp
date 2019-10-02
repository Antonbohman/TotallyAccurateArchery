#include "Game.h"

Game::Game(Graphic* _graphic, Input* _input) {
	graphic = _graphic;
	input = _input;

	//make sure to preload all necesary textures here in right order as described in Texture enum
	//textures.SetTexture(graphic->device, L"path/to/texture");
}

Game::~Game() {
}

void Game::NewGame() {
	//create new objects and set init variables for a new game
}

void Game::Run(double delta) {
	//call on calculation function for all objects in game
	//e.g update movement, values and check collisons
}

void Game::Draw() {
	//call draw function for all objects
}
