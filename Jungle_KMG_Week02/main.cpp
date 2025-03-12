#include "stdafx.h"
#include "CRenderer.h"

int SCR_WIDTH = 800;
int SCR_HEIGHT = 600;

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch ( message ) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WCHAR winClassName[] = L"WindowClass";
	WCHAR winTitleName[] = L"Title";

	WNDCLASS winClass = {};
	winClass.hInstance = hInstance;
	winClass.lpszClassName = winClassName;
	winClass.lpfnWndProc = WinProc;
	RegisterClass(&winClass);

	HWND hWnd = CreateWindow(winClassName, winTitleName,
		WS_POPUP | WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, SCR_WIDTH, SCR_HEIGHT,
		nullptr, nullptr, hInstance, nullptr
	);

	CRenderer::Init(hWnd);
	MSG msg = {};
	while ( msg.message != WM_QUIT ) {
		if ( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) ) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		CRenderer::GetGraphics()->RenderBegin();

		CRenderer::GetGraphics()->RenderEnd();
	}
	CRenderer::Release();
	return 0;
}