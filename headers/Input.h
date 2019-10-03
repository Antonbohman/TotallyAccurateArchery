#pragma once
#include <windows.h>
#include <Mouse.h>
#include <Keyboard.h>

#define REPEAT_OFF 0
#define REPEAT_ON 1

enum Key {
	_None = 0,
	_Back = 0x8,
	_Tab = 0x9,
	_Enter = 0xd,
	_Escape = 0x1b,
	_Space = 0x20,
	_PageUp = 0x21,
	_PageDown = 0x22,
	_End = 0x23,
	_Home = 0x24,
	_Left = 0x25,
	_Up = 0x26,
	_Right = 0x27,
	_Down = 0x28,
	_PrintScreen = 0x2c,
	_Insert = 0x2d,
	_Delete = 0x2e,

	D0 = 0x30,
	D1 = 0x31,
	D2 = 0x32,
	D3 = 0x33,
	D4 = 0x34,
	D5 = 0x35,
	D6 = 0x36,
	D7 = 0x37,
	D8 = 0x38,
	D9 = 0x39,

	A = 0x41,
	B = 0x42,
	C = 0x43,
	D = 0x44,
	E = 0x45,
	F = 0x46,
	G = 0x47,
	H = 0x48,
	I = 0x49,
	J = 0x4a,
	K = 0x4b,
	L = 0x4c,
	M = 0x4d,
	N = 0x4e,
	O = 0x4f,
	P = 0x50,
	Q = 0x51,
	R = 0x52,
	S = 0x53,
	T = 0x54,
	U = 0x55,
	V = 0x56,
	W = 0x57,
	X = 0x58,
	Y = 0x59,
	Z = 0x5a,

	_LeftWindows = 0x5b,
	_RightWindows = 0x5c,

	NP0 = 0x60,
	NP1 = 0x61,
	NP2 = 0x62,
	NP3 = 0x63,
	NP4 = 0x64,
	NP5 = 0x65,
	NP6 = 0x66,
	NP7 = 0x67,
	NP8 = 0x68,
	NP9 = 0x69,

	F1 = 0x70,
	F2 = 0x71,
	F3 = 0x72,
	F4 = 0x73,
	F5 = 0x74,
	F6 = 0x75,
	F7 = 0x76,
	F8 = 0x77,
	F9 = 0x78,
	F10 = 0x79,
	F11 = 0x7a,
	F12 = 0x7b,

	_LeftShift = 0xa0,
	_RightShift = 0xa1,
	_LeftControl = 0xa2,
	_RightControl = 0xa3,
	_LeftAlt = 0xa4,
	_RightAlt = 0xa5,

	_LeftClick = 0xf0,
	_RightClick = 0xf1,
	_MiddleClick = 0xf2,
};

struct KeyInfo {
	UINT Key = 0;
	bool Repeat = false;
	bool Active = false;
	bool Reset = true;
};

struct MouseInfo {
	float X = 0;
	float Y = 0;
	float DX = 0;
	float DY = 0;
	KeyInfo Left;
	KeyInfo Right;
	KeyInfo Middle;
	int Scroll = 0;
};

class Input {
private:
	UINT nrOfKeys;
	UINT maxKeys;
	KeyInfo* keyList;
	MouseInfo mouse;

	MouseInfo _M;

	std::unique_ptr<DirectX::Mouse>mouseInput;
	std::unique_ptr<DirectX::Keyboard>keyboardInput;

	void initKey(UINT keyID, bool Repeat);
	void updateKey(int index, bool state);
public:
	Input(HWND _wndHandle);
	~Input();

	void Update();
	KeyInfo Key(UINT KeyCode);
	MouseInfo Mouse();
	void setRepeatMode(UINT KeyCode, UINT Mode);
};
