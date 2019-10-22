#include "Input.h"

Input::Input(HWND _wndHandle) {
	keyboardInput = std::make_unique<DirectX::Keyboard>();
	mouseInput = std::make_unique<DirectX::Mouse>();
	mouseInput->SetWindow(_wndHandle);

	nrOfKeys = 0;
	maxKeys = 16;
	keyList = new KeyInfo[maxKeys];

	initKey(Key::F9, REPEAT_OFF);
	initKey(Key::F5, REPEAT_OFF);
	initKey(Key::F2, REPEAT_OFF);
	initKey(Key::F1, REPEAT_OFF);
	initKey(Key::D5, REPEAT_OFF);
	initKey(Key::D4, REPEAT_OFF);
	initKey(Key::D3, REPEAT_OFF);
	initKey(Key::D2, REPEAT_OFF);
	initKey(Key::D1, REPEAT_OFF);
	initKey(Key::_Space, REPEAT_ON);
	initKey(Key::_Enter, REPEAT_ON);
	initKey(Key::_Escape, REPEAT_OFF);
	initKey(Key::_Up, REPEAT_ON);
	initKey(Key::_Down, REPEAT_ON);
	initKey(Key::_Left, REPEAT_ON);
	initKey(Key::_Right, REPEAT_ON);

	mouse.Left.Key = Key::_LeftClick;
	mouse.Right.Key = Key::_RightClick;
	mouse.Middle.Key = Key::_MiddleClick;
}

Input::~Input() {
	delete[] keyList;
}

void Input::initKey(UINT keyID, bool repeat) {
	if (nrOfKeys < maxKeys) {
		keyList[nrOfKeys].Key = keyID;
		keyList[nrOfKeys].Repeat = repeat;

		nrOfKeys++;
	}
}

void Input::Update() {
	auto kb = keyboardInput->GetState();

	for (int i = 0; i < nrOfKeys; i++) {
		if (keyList[i].Key) {
			if (keyList[i].Key < 0x30 || (keyList[i].Key > 0x5a && keyList[i].Key < 0x60) || keyList[i].Key > 0x80) {
				switch (keyList[i].Key) {

					//Navigation Keys
				case Key::_Left:
					updateKey(i, kb.Left);
					break;
				case Key::_Up:
					updateKey(i, kb.Up);
					break;
				case Key::_Right:
					updateKey(i, kb.Right);
					break;
				case Key::_Down:
					updateKey(i, kb.Down);
					break;

					//Command Keys
				case Key::_Back:
					updateKey(i, kb.Back);
					break;
				case Key::_Tab:
					updateKey(i, kb.Tab);
					break;
				case Key::_Enter:
					updateKey(i, kb.Enter);
					break;
				case Key::_Escape:
					updateKey(i, kb.Escape);
					break;
				case Key::_Space:
					updateKey(i, kb.Space);
					break;
				case Key::_LeftWindows:
					updateKey(i, kb.LeftWindows);
					break;
				case Key::_RightWindows:
					updateKey(i, kb.RightWindows);
					break;
				case Key::_LeftShift:
					updateKey(i, kb.LeftShift);
					break;
				case Key::_RightShift:
					updateKey(i, kb.RightShift);
					break;
				case Key::_LeftControl:
					updateKey(i, kb.LeftControl);
					break;
				case Key::_RightControl:
					updateKey(i, kb.RightControl);
					break;
				case Key::_LeftAlt:
					updateKey(i, kb.LeftAlt);
					break;
				case Key::_RightAlt:
					updateKey(i, kb.RightAlt);
					break;
				case Key::_PageUp:
					updateKey(i, kb.PageUp);
					break;
				case Key::_PageDown:
					updateKey(i, kb.PageDown);
					break;
				case Key::_End:
					updateKey(i, kb.End);
					break;
				case Key::_Home:
					updateKey(i, kb.Home);
					break;
				case Key::_Insert:
					updateKey(i, kb.Insert);
					break;
				case Key::_Delete:
					updateKey(i, kb.Delete);
					break;
				}
			} else if (keyList[i].Key < 0x40) {
				switch (keyList[i].Key) {

					//Digits
				case Key::D0:
					updateKey(i, kb.D0);
					break;
				case Key::D1:
					updateKey(i, kb.D1);
					break;
				case Key::D2:
					updateKey(i, kb.D2);
					break;
				case Key::D3:
					updateKey(i, kb.D3);
					break;
				case Key::D4:
					updateKey(i, kb.D4);
					break;
				case Key::D5:
					updateKey(i, kb.D5);
					break;
				case Key::D6:
					updateKey(i, kb.D6);
					break;
				case Key::D7:
					updateKey(i, kb.D7);
					break;
				case Key::D8:
					updateKey(i, kb.D8);
					break;
				case Key::D9:
					updateKey(i, kb.D9);
					break;
				}
			} else if (keyList[i].Key < 0x5b) {
				switch (keyList[i].Key) {

					//Alpha
				case Key::A:
					updateKey(i, kb.A);
					break;
				case Key::B:
					updateKey(i, kb.B);
					break;
				case Key::C:
					updateKey(i, kb.C);
					break;
				case Key::D:
					updateKey(i, kb.D);
					break;
				case Key::E:
					updateKey(i, kb.E);
					break;
				case Key::F:
					updateKey(i, kb.F);
					break;
				case Key::G:
					updateKey(i, kb.G);
					break;
				case Key::H:
					updateKey(i, kb.H);
					break;
				case Key::I:
					updateKey(i, kb.I);
					break;
				case Key::J:
					updateKey(i, kb.J);
					break;
				case Key::K:
					updateKey(i, kb.K);
					break;
				case Key::L:
					updateKey(i, kb.L);
					break;
				case Key::M:
					updateKey(i, kb.M);
					break;
				case Key::N:
					updateKey(i, kb.N);
					break;
				case Key::O:
					updateKey(i, kb.O);
					break;
				case Key::P:
					updateKey(i, kb.P);
					break;
				case Key::Q:
					updateKey(i, kb.Q);
					break;
				case Key::R:
					updateKey(i, kb.R);
					break;
				case Key::S:
					updateKey(i, kb.S);
					break;
				case Key::T:
					updateKey(i, kb.T);
					break;
				case Key::U:
					updateKey(i, kb.U);
					break;
				case Key::V:
					updateKey(i, kb.V);
					break;
				case Key::W:
					updateKey(i, kb.W);
					break;
				case Key::X:
					updateKey(i, kb.X);
					break;
				case Key::Y:
					updateKey(i, kb.Y);
					break;
				case Key::Z:
					updateKey(i, kb.Z);
					break;
				}
			} else if (keyList[i].Key < 0x70) {
				switch (keyList[i].Key) {

					//Numpad
				case Key::NP0:
					updateKey(i, kb.NumPad0);
					break;
				case Key::NP1:
					updateKey(i, kb.NumPad1);
					break;
				case Key::NP2:
					updateKey(i, kb.NumPad2);
					break;
				case Key::NP3:
					updateKey(i, kb.NumPad3);
					break;
				case Key::NP4:
					updateKey(i, kb.NumPad4);
					break;
				case Key::NP5:
					updateKey(i, kb.NumPad5);
					break;
				case Key::NP6:
					updateKey(i, kb.NumPad6);
					break;
				case Key::NP7:
					updateKey(i, kb.NumPad7);
					break;
				case Key::NP8:
					updateKey(i, kb.NumPad8);
					break;
				case Key::NP9:
					updateKey(i, kb.NumPad9);
					break;
				}
			} else {
				switch (keyList[i].Key) {

					//F-Keys
				case Key::F1:
					updateKey(i, kb.F1);
					break;
				case Key::F2:
					updateKey(i, kb.F2);
					break;
				case Key::F3:
					updateKey(i, kb.F3);
					break;
				case Key::F4:
					updateKey(i, kb.F4);
					break;
				case Key::F5:
					updateKey(i, kb.F5);
					break;
				case Key::F6:
					updateKey(i, kb.F6);
					break;
				case Key::F7:
					updateKey(i, kb.F7);
					break;
				case Key::F8:
					updateKey(i, kb.F8);
					break;
				case Key::F9:
					updateKey(i, kb.F9);
					break;
				case Key::F10:
					updateKey(i, kb.F10);
					break;
				case Key::F11:
					updateKey(i, kb.F11);
					break;
				case Key::F12:
					updateKey(i, kb.F12);
					break;
				}
			}
		}
	}

	//update mouse stuff
	auto m = mouseInput->GetState();

	mouse.Scroll = m.scrollWheelValue;
	mouse.DX = mouse.X - m.x;
	mouse.DY = mouse.Y - m.y;
	mouse.X = m.x;
	mouse.Y = m.y;

	if (m.leftButton) {
		if (mouse.Left.Repeat) {
			mouse.Left.Active = true;
		} else {
			if (mouse.Left.Reset) {
				mouse.Left.Active = true;
				mouse.Left.Reset = false;
			} else {
				mouse.Left.Active = false;
			}
		}
	} else {
		mouse.Left.Active = false;
		mouse.Left.Reset = true;
	}

	if (m.rightButton) {
		if (mouse.Right.Repeat) {
			mouse.Right.Active = true;
		} else {
			if (mouse.Right.Reset) {
				mouse.Right.Active = true;
				mouse.Right.Reset = false;
			} else {
				mouse.Right.Active = false;
			}
		}
	} else {
		mouse.Right.Active = false;
		mouse.Right.Reset = true;
	}

	if (m.leftButton) {
		if (mouse.Middle.Repeat) {
			mouse.Middle.Active = true;
		} else {
			if (mouse.Middle.Reset) {
				mouse.Middle.Active = true;
				mouse.Middle.Reset = false;
			} else {
				mouse.Middle.Active = false;
			}
		}
	} else {
		mouse.Middle.Active = false;
		mouse.Middle.Reset = true;
	}
}

void Input::updateKey(int index, bool state) {
	if (state) {
		if (keyList[index].Repeat) {
			keyList[index].Active = true;
		} else {
			if (keyList[index].Reset) {
				keyList[index].Active = true;
				keyList[index].Reset = false;
			} else {
				keyList[index].Active = false;
			}
		}
	} else {
		keyList[index].Active = false;
		keyList[index].Reset = true;
	}
}

KeyInfo Input::Key(UINT KeyCode) {
	KeyInfo key;

	if (KeyCode == Key::_LeftClick) {
		key = mouse.Left;
	} else if (KeyCode == Key::_RightClick) {
		key = mouse.Right;
	} else if (KeyCode == Key::_MiddleClick) {
		key = mouse.Middle;
	} else {
		for (int i = 0; i < nrOfKeys; i++) {
			if (keyList[i].Key == KeyCode) {
				key = keyList[i];
				break;
			}
		}
	}

	return key;
}

MouseInfo Input::Mouse() {
	return mouse;
}

void Input::setRepeatMode(UINT KeyCode, UINT Mode) {
	if (KeyCode == Key::_LeftClick) {
		mouse.Left.Repeat = Mode;
	} else if (KeyCode == Key::_RightClick) {
		mouse.Right.Repeat = Mode;
	} else if (KeyCode == Key::_MiddleClick) {
		mouse.Middle.Repeat = Mode;
	} else {
		for (int i = 0; i < nrOfKeys; i++) {
			if (keyList[i].Key == KeyCode) {
				keyList[i].Repeat = (bool)Mode;
			}
		}
	}
}