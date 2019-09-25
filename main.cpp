#pragma once
#include <windows.h>
#include <chrono>
#include <string>

#include "Global.h"
#include "Graphic.h"
#include "Input.h"
#include "Menu.h"
#include "Game.h"

using namespace std::chrono;

HWND InitWindow(HINSTANCE hInstance);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//create two timestamps variables and a delta between them to adjust update frequency
	time_point<high_resolution_clock>startRun = high_resolution_clock::now();
	time_point<high_resolution_clock>startDraw = high_resolution_clock::now();
	time_point<high_resolution_clock>end = high_resolution_clock::now();
	duration<double, std::ratio<1, CPS>> delta_run;
	duration<double, std::ratio<1, FPS>> delta_draw;

	MSG msg = { 0 };
	HWND wndHandle = InitWindow(hInstance);

	if (wndHandle) {
		//create graphical and input interface
		Graphic graphic(wndHandle);
		Input input(wndHandle);

		if (graphic.Ready()) {
			//create game and meny object
			Game game(&graphic, &input);
			Menu menu(&graphic, &input, &game);

			if (renderOpt & RENDER_GAME)
				game.NewGame();

			ShowWindow(wndHandle, nCmdShow);

			while (WM_QUIT != msg.message) {
				if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				} else {
					//Upate graphical flags
					graphic.Update();

					//update inputs
					input.Update();

					//set timestamps and calculate delta between start end end time
					end = high_resolution_clock::now();
					delta_run = end - startRun;
					delta_draw = end - startDraw;

					if (renderOpt & RENDER_GAME) {
						startRun = high_resolution_clock::now();
						game.Run(delta_run.count());
						if (delta_draw.count() > 1.0f) {
							startDraw = high_resolution_clock::now();
							game.Draw();
							graphic.Process();
						}
					} else {
						startRun = high_resolution_clock::now();
						menu.Run(delta_run.count());
						if (delta_draw.count() > 1.0f) {
							startDraw = high_resolution_clock::now();
							menu.Draw();
							graphic.Process();
						}
					}
				}
			}
		}
		
		//Desctruction
		DestroyGlobals();
		DestroyWindow(wndHandle);
	}

	return (int)msg.wParam;
}

HWND InitWindow(HINSTANCE hInstance) {
	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.hInstance = hInstance;
	wcex.lpszClassName = L"BTH_D3D_DEMO";
	if (!RegisterClassEx(&wcex))
		return false;

	RECT rc = { 0, 0, W_WIDTH, W_HEIGHT };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	std::wstring version = L"Totally Accurate Archery - " + std::to_wstring(VERSION_MAJOR) + L"." + std::to_wstring(VERSION_MINOR) + L"." + std::to_wstring(VERSION_PATCH);

	HWND handle = CreateWindow(
		L"BTH_D3D_DEMO",
		(LPCWSTR)version.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rc.right - rc.left,
		rc.bottom - rc.top,
		nullptr,
		nullptr,
		hInstance,
		nullptr);

	return handle;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
		
	case WM_ACTIVATEAPP:
		//Keyboard::ProcessMessage(message, wParam, lParam);
		//Mouse::ProcessMessage(message, wParam, lParam);
		break;

	case WM_INPUT:
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEWHEEL:
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
	case WM_MOUSEHOVER:
		//Mouse::ProcessMessage(message, wParam, lParam);
		break;

	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		//Keyboard::ProcessMessage(message, wParam, lParam);
		break;
	}


	return DefWindowProc(hWnd, message, wParam, lParam);
}
