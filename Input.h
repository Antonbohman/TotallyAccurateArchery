#pragma once
#include "KeyInput.h"
#include <Mouse.h>
#include <Keyboard.h>

//std::unique_ptr<DirectX::Mouse>mouseInput;
//std::unique_ptr<DirectX::Keyboard>keyboardInput;

class Input {
private:

public:
	Input();
	~Input();

	void Update();
};


/*time_point<high_resolution_clock>key_start = high_resolution_clock::now();
time_point<high_resolution_clock>key_end = high_resolution_clock::now();
duration<double, std::ratio<1, 2>> key_delta;*/


//Mouse and keyboard ini (ONLY MOUSE)
/*keyboardInput = std::make_unique<Keyboard>();
mouseInput = std::make_unique<Mouse>();
mouseInput->SetWindow(wndHandle);*/
