#include "stdafx.h"
#include "CMesh.h"
#include "CBuffer.h"
#include "CShader.h"
#include "CState.h"
#include "CRenderer.h"

CRenderer* CRenderer::_instance = nullptr;

CRenderer::CRenderer() {}

void CRenderer::Init(HWND hWnd) {
    _instance = new CRenderer();
    _instance->_graphics = new CGraphics(hWnd);

    _instance->_inputLayout = new CInputLayout(_instance->_graphics->GetDevice());

    _instance->_states = new CRasterizerState(_instance->_graphics->GetDevice());
    _instance->_states->Create();
    _instance->_graphics->GetDeviceContext()->RSSetState(_instance->_states->Get());

    _instance->_depthStencilState = new CDepthStencilState(_instance->_graphics->GetDevice());
    _instance->_depthStencilState->Create();
    _instance->_graphics->GetDeviceContext()->OMSetDepthStencilState(_instance->_depthStencilState->Get(), 1);

    _instance->_constantBuffer = new CConstantBuffer<FMatrix>(_instance->_graphics->GetDevice(), _instance->_graphics->GetDeviceContext());
    _instance->_constantBuffer->Create();
    _instance->_graphics->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void CRenderer::Release() {
    for (auto& it : _instance->_meshes) {
        delete it.second;
    }
    for (auto& it : _instance->_pixelShader) {
        delete it.second;
    }
    for (auto& it : _instance->_vertexShader) {
        delete it.second;
    }

    _instance->_meshes.clear();
    _instance->_pixelShader.clear();
    _instance->_vertexShader.clear();

    delete _instance->_states;
    delete _instance->_depthStencilState;
    delete _instance->_constantBuffer;
    delete _instance->_inputLayout;
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

void CRenderer::SetMesh(FString name) {
    SetMesh(TName(name));
}

void CRenderer::SetMesh(TName name) {
    if ( _instance->_meshes[name] ) {
        if ( _instance->_nowMesh == name )
            return;
        _instance->_nowMesh = name;

        CMesh<FVertexColor>* mesh = _instance->_meshes[name];
        ID3D11DeviceContext* ctx = _instance->GetGraphics()->GetDeviceContext();
        uint32 stride = mesh->GetVerticesStride();
        uint32 offset = mesh->GetVerticesOffset();
        ID3D11Buffer* vertices = mesh->GetVerticesBuffer();

        ctx->IASetVertexBuffers(0, 1, &vertices, &stride, &offset);

        ID3D11Buffer* indices = mesh->GetIndicesBuffer();
        ctx->IASetIndexBuffer(indices, DXGI_FORMAT_R32_UINT, 0);

        ctx->IASetPrimitiveTopology(mesh->GetPrimitiveMode());

    } else {
        OutputDebugString(L"Try to access none resource (SetMesh)");
        _instance->_nowMesh = TName("");
    }
}

void CRenderer::SetVertexShader(FString name) {
    TName tname = TName(name);
    if ( _instance->_vertexShader[tname] ) {
        if ( _instance->_nowVertexShader == tname )
            return;
        _instance->_nowVertexShader = tname;

        CVertexShader* vs = _instance->_vertexShader[tname];
        _instance->_inputLayout->Create(FVertexColor::descs, vs->GetBlob());
        
        ID3D11DeviceContext* ctx = _instance->GetGraphics()->GetDeviceContext();
        ctx->IASetInputLayout(_instance->_inputLayout->Get());
        ctx->VSSetShader(vs->Get(), nullptr, 0);
    }
    else {
        OutputDebugString(L"Try to access none resource (SetVertexShader)");
        _instance->_nowVertexShader = TName("");
    }
}

void CRenderer::SetPixelShader(FString name) {
    TName tname = TName(name);
    if ( _instance->_pixelShader[tname] ) {
        if ( _instance->_nowPixelShader == tname )
            return;
        _instance->_nowPixelShader = tname;

        CPixelShader* ps = _instance->_pixelShader[tname];
        ID3D11DeviceContext* ctx = _instance->GetGraphics()->GetDeviceContext();
        ctx->PSSetShader(ps->Get(), nullptr, 0);
    }
    else {
        OutputDebugString(L"Try to access none resource (SetPixelShader)");
        _instance->_nowPixelShader = TName("");
    }
}

void CRenderer::SetMainCamera(UCameraComponent* camera) {
    _instance->_mainCamera = camera;
}

void CRenderer::Render() {
    ID3D11DeviceContext* ctx = _instance->GetGraphics()->GetDeviceContext();
    uint32 count = _instance->_meshes[_instance->_nowMesh]->GetIndicesCount();
    ctx->DrawIndexed(count, 0, 0);
}

void CRenderer::SetTansformToConstantBuffer(FMatrix matrix) {

    FMatrix view = _instance->_mainCamera->Transformation().Inverse();
    //FMatrix view = _instance->_mainCamera->View();
    FMatrix projection = _instance->_mainCamera->Projection();
#ifdef _ROW_MAJOR_SYSTEM
    matrix = matrix * view * projection;
    //matrix = projection * view * matrix;
#else
    matrix = projection * view * matrix;
#endif
    _instance->_constantBuffer->CopyData(matrix);
    ID3D11Buffer* constantBuffer = _instance->_constantBuffer->Get();
    _instance->_graphics->GetDeviceContext()->VSSetConstantBuffers(0, 1, &constantBuffer);
}
