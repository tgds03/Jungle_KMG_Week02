#pragma once
#include "ISingleton.h"
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
//#include "Framework/Core/UCoordArrowComponent.h"

// https://blog.nullbus.net/24
// https://hwan-shell.tistory.com/227

class Input: public ISingleton<Input> {
private:

public:
	bool Init(HINSTANCE hInstance, HWND hWnd, int screenWidth, int screenHeight);
	void Shutdown();
	void ResizeScreen(int sWidth, int sHeight);
	bool Frame();

	bool IsKeyDown(char keycode);
	bool IsKeyPressed(char keycode);
	bool IsKeyReleased(char keycode);
	bool IsMouseButtonDown(char button);
	bool IsMouseButtonPressed(char button);
	bool IsMouseButtonReleased(char button);
	void GetMouseLocation(int& mouse_x, int& mouse_y);
	void GetMouseWheel(int& mouse_w);
	void GetMouseDelta(int& mouse_x, int& mouse_y);
	void GetMouseRay(FVector& rayOrigin, FVector& rayDirection, const FMatrix& viewMatrix, const FMatrix& projectionMatrix);

private:
	bool ReadKeyboard();
	bool ReadMouse();
	void ProcessInput();

	IDirectInput8* m_directInput = nullptr;
	IDirectInputDevice8* m_keyboard = nullptr;
	IDirectInputDevice8* m_mouse = nullptr;

	unsigned char m_keyboardState[256];
	unsigned char m_keyboardStatePrevious[256];
	DIMOUSESTATE m_mouseState;
	DIMOUSESTATE m_mouseStatePrevious;

	int m_screenWidth, m_screenHeight;
	//int m_mouseX, m_mouseY;
	HWND m_hWnd;
};
