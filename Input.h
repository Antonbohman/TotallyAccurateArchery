#pragma once
#include "KeyInput.h"
#include <Mouse.h>
#include <Keyboard.h>

#define INPUT_W 0
#define INPUT_A 1
#define INPUT_S 2
#define INPUT_D 3

struct KeyInfo {
	UINT Key;
	bool Active;
};

struct MouseInfo {
	float X;
	float Y;
	bool LeftClick;
	bool RightClick;
};

class Input {
private:
	KeyInfo W;
	KeyInfo A;
	KeyInfo S;
	KeyInfo D;

	MouseInfo _M;

	std::unique_ptr<DirectX::Mouse>mouseInput;
	std::unique_ptr<DirectX::Keyboard>keyboardInput;
public:
	Input(HWND _wndHandle);
	~Input();

	void Update();
	KeyInfo Key(UINT KeyCode);
	MouseInfo Mouse();
};

//updateKeyAndMouseInput(&freeFlight, &culling, &showCullingObjects, &wireFrame, &forceSingle, &onlyQuadCulling, &camFrustum, &renderOnce, delta);

/*time_point<high_resolution_clock>key_start = high_resolution_clock::now();
time_point<high_resolution_clock>key_end = high_resolution_clock::now();
duration<double, std::ratio<1, 2>> key_delta;*/



