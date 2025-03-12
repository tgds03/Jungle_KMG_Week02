#include "stdafx.h"
#include "CRenderer.h"

CRenderer* CRenderer::_instance = nullptr;

void CRenderer::Init(HWND hWnd) {
    _instance = new CRenderer();
    _instance->_graphics = new CGraphics(hWnd);
    _instance->_states = new CRasterzierState(_instance->_graphics->GetDevice());
}

void CRenderer::Release() {
    delete _instance->_graphics;
}

CGraphics* CRenderer::GetGraphics() {
    return _instance->_graphics;
}

void CRenderer::AddVertexShader(FString name, FWString path, FString entrypoint) {
    CVertexShader* shader = new CVertexShader(_instance->_graphics->GetDevice());
    shader->Create(path, entrypoint, "vs_5_0");
    _instance->_vertexShader[TName(name)] = shader;
}

void CRenderer::AddPixelShader(FString name, FWString path, FString entrypoint) {
    CPixelShader* shader = new CPixelShader(_instance->_graphics->GetDevice());
    shader->Create(path, entrypoint, "ps_5_0");
    _instance->_pixelShader[TName(name)] = shader;
}
