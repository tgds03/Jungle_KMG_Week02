#pragma once
#include "CInputLayout.h"
#include "TName.h"
#include "CGraphics.h"
#include "ISingleton.h"
#include "UCameraComponent.h"

template <typename T> class CMesh;
template <typename T> class CVertexBuffer;
class CVertexShader;
class CPixelShader;
class CIndexBuffer;
class CGraphics;
class CRasterizerState;
class CDepthStencilState;
template <typename T> class CConstantBuffer;

class CRenderer: public ISingleton<CRenderer> {
private:
	CRenderer();
	~CRenderer() {
		SafeRelease(_graphics);
		SafeDelete(_graphics);
	};
	static CRenderer* _instance;

	TMap<TName, CMesh<FVertexColor>*> _meshes;
	TMap<TName, CVertexShader*> _vertexShader;
	TMap<TName, CPixelShader*> _pixelShader;

private:
	CGraphics* _graphics = nullptr;
	CRasterizerState* _states = nullptr;
	CInputLayout* _inputLayout = nullptr;
	CConstantBuffer<FMatrix>* _constantBuffer = nullptr;
	CDepthStencilState* _depthStencilState = nullptr;
	

	TName _nowMesh;
	TName _nowVertexShader;
	TName _nowPixelShader;

	UCameraComponent* _mainCamera;

public:
	static void Init(HWND hWnd);
	static void Release();
	static CGraphics* GetGraphics();
	template<typename T>
	static void AddMesh(FString, CMesh<T>*);
	template<typename T>
	static void AddMesh(TName, CMesh<T>*);
	static void AddVertexShader(FString name, FWString path, FString entrypoint);
	static void AddPixelShader(FString name, FWString path, FString entrypoint);
	static void SetMesh(FString name);
	static void SetMesh(TName name);
	static void SetVertexShader(FString name);
	static void SetPixelShader(FString name);
	static void SetMainCamera(UCameraComponent* camera);
	static void Render();
	static void SetTansformToConstantBuffer(FMatrix m);
};

template<typename T>
inline void CRenderer::AddMesh(FString s, CMesh<T>* m) {
	_instance->_meshes[TName(s)] = m;
}

template<typename T>
inline void CRenderer::AddMesh(TName s, CMesh<T>* m) {
	_instance->_meshes[s] = m;
}