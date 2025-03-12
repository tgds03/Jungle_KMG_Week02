#include "stdafx.h"
#include "CRenderer.h"
#include "CGraphics.h"
#include "UWorld.h"
#include "UCameraComponent.h"
#include "UCubeComponent.h"
#include "Input.h"
#include "Time.h"
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
	Input::Instance().Init(hInstance, hWnd, SCR_WIDTH, SCR_HEIGHT);
	Time::Instance().Init();
	CRenderer::Init(hWnd);
	CRenderer::AddVertexShader("VertexShader", L"Shader.hlsl", "VS");
	CRenderer::AddPixelShader("PixelShader", L"Shader.hlsl", "PS");
	CRenderer::SetVertexShader("VertexShader");
	CRenderer::SetPixelShader("PixelShader");

	UCubeComponent* comp = new UCubeComponent();
	comp->SetRelativeLocation(FVector(0, 0, 5));

	UCameraComponent* cam = new UCameraComponent();
	cam->SetRelativeLocation(FVector(0, 0, 0));
	CRenderer::SetMainCamera(cam);

	AActor* actor = new AActor();
	actor->RegisterComponent(comp);
	actor->RegisterComponent(cam);

	UWorld* world = new UWorld();
	world->AddActor(actor);

	MSG msg = {};
	
	while ( msg.message != WM_QUIT ) {
		Time::Instance()._query_frame_update_time();
		if ( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) ) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		Input::Instance().Frame();
		CRenderer::GetGraphics()->RenderBegin();
		world->Update();
		world->Render();
		CRenderer::GetGraphics()->RenderEnd();
		Time::Instance()._query_frame_end_time();
	}
	CRenderer::Release();
	return 0;
}