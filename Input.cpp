#include "Input.h"

Input::Input(HWND _wndHandle) {
	keyboardInput = std::make_unique<DirectX::Keyboard>();
	mouseInput = std::make_unique<DirectX::Mouse>();
	mouseInput->SetWindow(_wndHandle);
}

Input::~Input() {

}

void Input::Update() {

}

KeyInfo Input::Key(UINT KeyCode) {
	return W;
}

MouseInfo Input::Mouse() {
	return _M;
}