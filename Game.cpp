#include "Game.h"

Game::Game(Graphic* _graphic, Input* _input) {
	graphic = _graphic;
	input = _input;
}

Game::~Game() {
}

void Game::NewGame() {
	//create new objects and set init variables for a new game
}

void Game::Run(double delta) {
	//make calculation for all objects in game
}

void Game::Draw() {
	//call draw call for all objects
}
