#include "stdafx.h"
#include "ULineComponent.h"

void ULineComponent::SetStartVector(FVector s) {
	start = s;
}

void ULineComponent::SetEndVector(FVector e) {
	end = e;
}

void ULineComponent::SetMesh() {
	CBatchLineMesh* _mesh = new CBatchLineMesh();
	if (_mesh->IsEmpty()) {
		_mesh->SetVertices({
			{ start.x, start.y, start.z, 1.0f, 0.0f, 0.0f, 1.0f },
			{ end.x, end.y, end.z, 1.0f, 0.0f, 0.0f, 1.0f }
		})->SetIndices({ 0, 1 });
	}
	name = TName("Line" + std::to_string(GetUUID()));
	CRenderer::AddMesh(name, _mesh);
}

void ULineComponent::Start() {}

void ULineComponent::Update() {}

void ULineComponent::Render() {
	CRenderer::SetMesh(name);
	CRenderer::SetTansformToConstantBuffer(Transformation());
	CRenderer::Render();
}

void ULineComponent::Remove() {}
