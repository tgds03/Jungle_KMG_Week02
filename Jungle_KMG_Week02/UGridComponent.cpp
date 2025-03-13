#include "stdafx.h"
#include "UGridComponent.h"

UGridComponent::UGridComponent() {
	static CBatchLineMesh* _mesh = new CBatchLineMesh();
	if ( _mesh->IsEmpty() ) {
		for ( int i = -1000; i <= 1000; i++ ) {
			float fz = static_cast<float>(i);
			_mesh->AddLine(TPair<FVertexColor, FVertexColor>(
				{ -100.f, 0.f, fz,		1.0f, 1.0f, 1.0f, 0.1f },
				{ 100.f, 0.f, fz,		1.0f, 1.0f, 1.0f, 0.1f }
			));
			_mesh->AddLine(TPair<FVertexColor, FVertexColor>(
				{ fz, 0.f, -100.f,		1.0f, 1.0f, 1.0f, 0.1f },
				{ fz, 0.f, 100.f,		1.0f, 1.0f, 1.0f, 0.1f }
			));
		}
	}
	_mesh->Set();
	CRenderer::AddMesh("WorldGrid", _mesh);
}

void UGridComponent::Render() {
	CRenderer::SetMesh("WorldGrid");
	CRenderer::Render();
}

void UGridComponent::Start() {}

void UGridComponent::Update() {

}

void UGridComponent::Remove() {}
