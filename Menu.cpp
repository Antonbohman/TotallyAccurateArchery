#include "Menu.h"

Menu::Menu(Graphic* _graphic, Input* _input, Game* _game) {
	graphic = _graphic;
	input = _input;
	game = _game;

	stage = MAIN;

	textures.SetTexture(graphic->device, T0_Background, L"resources/bg.dds");
	textures.SetTexture(graphic->device, T1_PLAY, L"resources/play.dds");
	textures.SetTexture(graphic->device, T2_BACK, L"resources/back.dds");
	textures.SetTexture(graphic->device, T3_QUIT, L"resources/quit.dds");
	textures.SetTexture(graphic->device, T4_CRED, L"resources/cred.dds");
	textures.SetTexture(graphic->device, T5_HELP, L"resources/help.dds");
	textures.SetTexture(graphic->device, T6_FONT, L"resources/font.dds");

	background = new AbstractElement(
		graphic,
		{ W_WIDTH / 2, W_HEIGHT / 2, 0.9f },  
		{ W_WIDTH, W_HEIGHT },
		Middle,
		textures.GetTexture(T0_Background)->ShaderResourceView
	);

	quit = new Button(
		graphic,
		{ W_WIDTH-200, 100, 0.8f },
		{ 300, 100 },
		BottomRight,
		textures.GetTexture(T3_QUIT)->ShaderResourceView
	);
	play = new Button(
		graphic,
		{ 200, W_HEIGHT-300, 0.7f },
		{ 300, 100 },
		TopLeft,
		textures.GetTexture(T1_PLAY)->ShaderResourceView
	);
	cred = new Button(
		graphic,
		{ 200, 100, 0.6f },
		{ 300, 100 },
		BottomLeft,
		textures.GetTexture(T4_CRED)->ShaderResourceView
	);
	help = new Button(
		graphic,
		{ W_WIDTH-200, W_HEIGHT-300, 0.5f },
		{ 300, 100 },
		TopRight,
		textures.GetTexture(T5_HELP)->ShaderResourceView
	);

	back = new Button(
		graphic,
		{ W_WIDTH / 2, 100, 0.7f },
		{ 300, 100 },
		Middle,
		textures.GetTexture(T2_BACK)->ShaderResourceView
	);

	for (int i = 0; i < TEXT_ROWS; i++) {
		text[i] = new Print(
			graphic,
			{ 220, 230.0f + (60 * ((TEXT_ROWS-1)-i)), 0.6f },
			{ 840, 40 },
			nullptr,
			textures.GetTexture(T6_FONT)->ShaderResourceView,
			WRITE_RIGHT,
			50
		);
	}
}

Menu::~Menu() {
	delete background;
	delete quit;
	delete play;
	delete cred;
	delete help;
	delete back;
}

bool Menu::Run(double delta) {
	MouseInfo mouse = input->Mouse();
	mouse.Y = W_HEIGHT - mouse.Y;

	switch (stage) {
	case CRED:
		text[0]->setString(" This demo program is to showcase the projectile ", 50);
		text[1]->setString("   paths for arrows in wind with real physics.   ", 50);
		text[2]->setString("               It has been created by:           ", 50);
		text[3]->setString("                   Filip Unger                   ", 50);
		text[4]->setString("                   Anton Bohman                  ", 50);

		if (back->isPressed(&mouse) || input->Key(Key::_Escape).Active) {
			stage = MAIN;
		}
		break;
	case HELP:
		text[0]->setString("Arrows - Move Camera       F1 - Set Camera Archer", 50);
		text[1]->setString(" Space - Draw new arrow    F2 - Set Camera Arrow ", 50);
		text[2]->setString(" Enter - Stop fired arrow  F5 - Delete all arrows", 50);
		text[3]->setString("Escape - Quit to menu      F9 - Render wireframe ", 50);
		text[4]->setString("                                                 ", 50);

		if (back->isPressed(&mouse) || input->Key(Key::_Escape).Active) {
			stage = MAIN;
		}
		break;
	case MAIN:
	default:
		if (play->isPressed(&mouse)) {
			game->NewGame();
			renderOpt |= RENDER_GAME;
		} else if (cred->isPressed(&mouse)) {
			stage = CRED;
		} else if (help->isPressed(&mouse)) {
			stage = HELP;
		} else if (quit->isPressed(&mouse) || input->Key(Key::_Escape).Active) {
			return false;
		}
		break;
	};
	
	return true;
}

void Menu::Draw() {
	background->renderElement();
	switch (stage) {
	case CRED:
		for (int i = 0; i < TEXT_ROWS; i++) {
			text[i]->renderElement();
		}
		back->renderElement();
		break;
	case HELP:
		for (int i = 0; i < TEXT_ROWS; i++) {
			text[i]->renderElement();
		}
		back->renderElement();
		break;
	case MAIN:
	default:
		play->renderElement();
		help->renderElement();
		cred->renderElement();
		quit->renderElement();
		break;
	};
}