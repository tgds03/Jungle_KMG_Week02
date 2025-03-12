#pragma once
#include "CGraphics.h"
#include "CMesh.h"
#include "CBuffer.h"
#include "CShader.h"
#include "CState.h"
#include "CInputLayout.h"
#include "CMesh.h"
#include "TName.h"
#include "ISingleton.h"

class CRenderer: public ISingleton<CRenderer> {
private:
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
	CRasterzierState* _states = nullptr;

public:
	static void Init(HWND hWnd);
	static void Release();
	static CGraphics* GetGraphics();
	template<typename T>
	static void AddMesh(FString, CMesh<T>*);
	static void AddVertexShader(FString name, FWString path, FString entrypoint);
	static void AddPixelShader(FString name, FWString path, FString entrypoint);
};

template<typename T>
inline void CRenderer::AddMesh(FString s, CMesh<T>* m) {
	_instance->_meshes[TName(s)] = m;
}
